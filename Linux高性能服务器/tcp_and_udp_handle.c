/*************************************************************************
	> File Name: tcp_and_udp_handle.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 14 Sep 2014 06:38:56 AM PDT
 ************************************************************************/

/*同时处理TCP和UDP的请求*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <assert.h>

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFFER_SIZE 512
#define UDP_BUFFER_SIZE 1024

int setnonblocking(int fd){
	int old_option=fcntl(fd,F_GETFL);
	int new_option=old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;
}

void addfd(int epollfd,int fd){
	struct epoll_event event;
	event.data.fd=fd;
	event.events = EPOLLIN | EPOLLET;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnonblocking(fd);
}

int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip port\n",argv[0]);
		return -1;
	}


	const char* ip=argv[1];
	int port=atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int lisenfd;
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd>0);

	int ret=bind(listenfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	ret=listen(listenfd,5);
	assert(ret!=-1);

	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int udpfd=socket(AF_INET,SOCK_DGRAM,0);
	assert(udpfd>=0);

	ret=bind(udpfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	epoll_event events[MAX_EVENT_NUMBER];
	int epollfd=epoll_create(5);
	assert(epollfd!=-1);

	/*注册TCP socket和UDP socket上的可读事件*/
	addfd(epollfd,listenfd);
	addfd(epollfd,udpfd);

	while(1){
		int number=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
		if(number<0){
			printf("epoll failure\n");
			break;
		}

		for(int i=0;i<number;i++){
			int sockfd=events[i].data.fd;
			if(sockfd==listenfd){
				struct sockaddr_in client_address;
				socklen_t addrlen=sizeof(client_address);

				int connfd=accept(sockfd,(struct sockaddr*)&client_addrss,
						&addrlen);

				addfd(epollfd,connfd);
			}

			else if(sockfd==udpfd){
				char buf[UDP_BUFFER_SIZE];
                memset(buf,'\0',BUFFER_SIZE);
                struct sockaddr_in client_address;
				socklen_t addrlen=sizeof(client_address);

				ret=recvfrom(sockfd,buf,UDP_BUFFER_SIZE-1,0,(struct sockaddr*)&client_address,
						&addrlen);

				if(ret>0){
					sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&client_address,
							addrlen);
				}

			}

			else if(events[i].events & EPOLLIN){
				char buf[TCP_BUFFER_SIZE];
				while(1){
					memset(buf,'\0',TCP_BUFFER_SIZE);
					ret=recv(sockfd,buf,TCP_BUFFER_SIZE-1,0);
					if(ret<0){
						if((errno==EAGAIN)  && (errno==EWOULDBLOCK)){
							break;
						}

						close(sockfd);
						break;
					}
					else if(ret==0){
						close(sockfd);
					}

					else{
						send(sockfd,buf,ret,0);
					}
				}
			}
			else{
				printf("somethinf else happend\n");
			}
		}
	}

	close(listenfd);
	return 0;
}
