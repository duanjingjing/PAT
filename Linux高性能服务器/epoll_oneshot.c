/*************************************************************************
	> File Name: epoll_oneshot.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 13 Sep 2014 06:18:03 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <errno.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024

struct fds{
    int epollfd;
	int sockfd;
};

int setnonblocking(int fd){
	int old_option=fcntl(fd,F_GETFL);
	int new_option=old_option|O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;
}

/*将fd上的EPOLLIN和EPOLLET事件注册到epollfd指示的epoll内核事件表中,参数oneshot指定是否注册fd上的EPOLLONESHOT事件*/

void addfd(int epollfd,int fd,bool oneshot){
	epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN;

	if(oneshot){
		event.events|=EPOLLONESHOT;
	}

	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnonblocking(fd);
}


/*重置fd上的事件,这样操作后,尽管fd上的EPOLLONESHOT事件被注册,但是操作系统仍然会触发fd上的EPOLLIN事件,且只触发一次*/
void reset_oneshot(int epollfd,int fd){
     epoll_event event;
	 event.data.fd=fd;
	 event.events=EPOLLIN | EPOLLET | EPOLLONESHOT;
	 epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event);
}

/*工作线程*/
void* worker(void* arg){
	int sockfd=((fds*)arg)->sockfd;
	int epollfd=((fds*)arg)->epollfd;
	printf("start new thread to receive data on fd:%d\n",sockfd);
	char buf[BUFFER_SIZE];
	memset(buf,'\0',BUFFER_SIZE);

	/*循环读取sockfd上的数据,直到遇到EAGAIN错误*/
	while(1){
		int ret=recv(sockfd,buf,BUFFER_SIZE-1,0);
		if(ret==0){
			close(sockfd);
			printf("foreign closed the connection\n");
			break;
		}

		else if(ret<0){
			if(errno==EAGAIN){
				reset_oneshot(epollfd,sockfd);
				printf("read later\n");
				break;
			}
		}

		else{
			printf("get content:%s \n",buf);
			/*休眠5s,模拟数据处理过程*/
			sleep(5);
		}
	}

	printf("end thread receiving data on fd:%d\n",sockfd);
}

int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip_address port_number \n",argv[0]);
		return -1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	int ret=0;
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd!=-1);

	ret=bind(sockfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	ret=listen(sockfd,5);
	assert(ret!=-1);

	/*
	struct sockaddr_in peerAddress;
	bzero(&peerAddress,sizeof(peerAddress));
	socklen_t addrlen=sizeof(peerAddress);

	int connfd=accept(sockfd,(struct sockaddr*)&peerAddress,&addrlen);
	assert(connfd>0);

	*/
	int epollfd=epoll_create(5);
    epoll_event events[MAX_EVENT_NUMBER];
	/*注意,监听scoket listenfd上不能注册到EPOLLONESHOT事件的,否则应用程序只能处理一个客户的连接!因为后续的客户连接请求不再触发listenfd上的EPOLLIN事件*/
	addfd(epollfd,sockfd,false);

	while(1){
		int ret=epoll_wait(epollfd,events,MAX_EVENT_NUMBER-1,-1);
		if(ret<0){
			printf("epoll failure\n");
			break;
		}

		for(int i=0;i<ret;i++){
			int fd=events[i].data.fd;
			if(fd==sockfd){
				struct sockaddr_in peerAddress;
				socklen_t len=sizeof(peerAddress);
				int connfd=accept(fd,(struct sockaddr*)&peerAddress,
						&len);
				/*对每个非监听文件描述符都注册EPOLLONESHOT事件*/
				addfd(epollfd,connfd,true);
			}

			else if(events[i].events & EPOLLIN){
				pthread_t tid;
				fds fds_for_new_worker;
				fds_for_new_worker.epollfd=epollfd;
				fds_for_new_worker.sockfd=fd;
				/*新启动一个工作线程为sockfd服务*/
				pthread_create(&tid,NULL,worker,(void*)&fds_for_new_worker);
			}

			else{
				printf("something else happened\n");
			}
		}
	}
    
	close(sockfd);
	return 0;
}
