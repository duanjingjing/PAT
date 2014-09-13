/*************************************************************************
	> File Name: splice.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 12 Sep 2014 07:19:24 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc,const char* argv[]){
	if(argc<3){
		printf("usage:%s ip_address port\n",argv[0]);
		return -1;
	}
    int fd,client_fd;
	fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1){
		perror("socket");
		return -1;
	}

	struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);

	int ret=bind(fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret==-1){
		perror("bind");
		return -1;
	}

	ret=listen(fd,5);
	assert(ret!=-1);

	struct sockaddr_in peerAddr;
	bzero(&peerAddr,sizeof(peerAddr));

	socklen_t len=sizeof(peerAddr);
	
	int connfd=accept(fd,(struct sockaddr*)&peerAddr,&len);
	if(connfd==-1){
		perror("accept");
		return -1;
	}
	else{
	   int pipefd[2];
	   assert(ret!=-1);

	   ret=pipe(pipefd);//创建管道
	   /*将connfd上流入的客户数据定向到管道中*/
	   ret=splice(connfd,NULL,pipefd[1],NULL,32768,SPLICE_F_MORE|SPLICE_F_MOVE);
	   assert(ret!=-1);

	   /*将管道的输出定向到connfd客户连接文件描述符*/
	   ret=splice(pipefd[0],NULL,connfd,NULL,32768,SPLICE_F_MORE|
			   SPLICE_F_MOVE);
	   assert(ret!=-1);
	   close(connfd);
	}

	close(fd);
    return 0;
}
