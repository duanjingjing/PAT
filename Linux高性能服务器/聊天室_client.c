/*************************************************************************
	> File Name: 聊天室_client.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 14 Sep 2014 12:27:13 AM PDT
 ************************************************************************/

#define _GNU_SOURCE  1
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip_address port_number\n",argv[0]);
		return -1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	struct sockaddr_in address;
	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd!=-1);

	if(connect(sockfd,(struct sockaddr*)&address,sizeof(address))<0){
		perror("connect");
		close(sockfd);
		exit(-1);
	}

	struct pollfd fds[2];

	fds[0].fd=STDIN_FILENO;
	fds[0].events=POLLIN;
	fds[1].fd=sockfd;
	fds[1].events=POLLIN | POLLRDHUP;

	char buf[BUFFER_SIZE];
	int pipefd[2];
	int ret=pipe(pipefd);
	assert(ret!=-1);

	while(1){
       ret=poll(fds,2,-1);

	   if(ret<0){
		   printf("poll error\n");
		   break;
	   }

	    if(fds[1].revents & POLLRDHUP){
		   printf("server close the connection\n");
		   break;
	   }

	   else if(fds[1].revents & POLLIN){
		   //接受服务器端数据
		   memset(buf,'\0',BUFFER_SIZE);
		   ret=recv(sockfd,buf,BUFFER_SIZE-1,0);
           printf("recv data:%s",buf);
	   }

	   if(fds[0].revents & POLLIN){
		   ret=splice(STDIN_FILENO,NULL,pipefd[1],NULL,32768,
				   SPLICE_F_MORE | SPLICE_F_MOVE);
		   assert(ret!=-1);

		   ret=splice(pipefd[0],NULL,sockfd,NULL,32768,SPLICE_F_MOVE |
				   SPLICE_F_MORE);
	   }
	}

	close(sockfd);
	return 0;
}

