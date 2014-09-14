/*************************************************************************
	> File Name: epoll_LT_ET.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 13 Sep 2014 04:07:27 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <strings.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

/*将文件描述符设置成非阻塞的*/
int setnonblocking(int fd){
	int old_option=fcntl(fd,F_GETFL);
	int new_option=old_option|O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return old_option;
}

/*将文件描述符fd的EPOLLIN注册到epollfd指示的epoll内核事件表中,参数enable_et指定是否对fd启用ET模式*/

void addfd(int epollfd,int fd,bool enable_et){
    epoll_event  event;
	event.data.fd=fd;
	event.events=EPOLLIN;

	if(enable_et){
		event.events|=EPOLLET;
	}

	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnonblocking(fd);
}

/*LT的模式的工作流程*/

void lt(epoll_event* events,int number,int epollfd,int listenfd){
	 char buf[BUFFER_SIZE];
	 int i;
	 for(i=0;i<number;i++){
		 int sockfd=events[i].data.fd;
		 if(sockfd==listenfd){
			 struct sockaddr_in peerAddr;
			 bzero(&peerAddr,sizeof(peerAddr));
			 socklen_t addrlen=sizeof(peerAddr);

			 int connfd=accept(sockfd,(struct sockaddr*)&peerAddr,&addrlen);
			 if(connfd<=0){
				 perror("accept");
		         break;
			 }
            addfd(epollfd,connfd,false);

		 }

		 else if(events[i].events & EPOLLIN){
			 /*只要socket读缓存中还有未读出的数据,这段代码就会触发*/
			 printf("event trigger once\n");
			 memset(buf,'\0'.BUFFER_SIZE);
			 int ret=recv(events[i].data.fd,buf,BUFFER_SIZE-1,0);
			 if(ret<=0){
				 close(sockfd);
			 }
     
			 printf("get %d bytes of content:%s\n",ret,buf);
		 }

		 else{
			 printf("something else happend\n");
		 }
	 }
}


/*ET模式的工作流程*/

void et(epoll_event* events,int number,int epollfd,int listenfd){
     char buf[BUFFER_SIZE];

	 int i;
	 for(i=0;i<number;i++){
		 int sockfd=events[i].data.fd;
		 if(sockfd==listenfd){
			 struct sockaddr_in peerAddr;
			 bzero(&peerAddr,sizeof(peerAddr));

			 socklen_t addrlen=sizeof(peerAddr);
			 int connfd=accept(sockfd,(struct sockaddr*)&peerAddr,&addrlen);
			 addfd(epollfd,connfd,true);
		 }

		 else if(events[i].events & EPOLLIN){
             printf("event trigger once\n");
			 while(1){
				 memset(buf,'\0',BUFFER_SIZE);
				 int ret=recv(sockfd,buf,BUFFER_SIZE,0);
				 if(ret<0){
					 /*对于非阻塞IO,下面的条件成立表示数据已全部读取完毕*/
					 if((errno==EAGAIN) ||(errno==EWOULDBLOCK)){
						 printf("read later\n");
						 break;
					 }
				 }

				 else if(ret==0){
					 close(sockfd);
				 }

				 else{
					 printf("get %d bytes of content:%s\n",ret,buf);
				 }
			 }
		 }

		 else{
			 printf("something else happened\n");
		 }
	 }
}


int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip_address port_number\n",argv[0]);
		exit(-1);
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	int ret=0;
	struct sockaddr_in address;
	bzero(&address,sizeof(address));

	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd!=-1);

	ret=bind(sockfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	ret=listen(sockfd,5);
	assert(ret!=-1);

	epoll_event events[MAX_EVENT_NUMBER];
	int epollfd=epoll_create(5);
	assert(epollfd!=-1);
	addfd(epollfd,sockfd,true);

	while(1){
		int ret=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
		if(ret<0){
			printf("epoll failure\n");
			break;
		}

		lt(events,ret,epollfd,sockfd);
	}

	close(sockfd);
	return 0;
}
