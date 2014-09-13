/*************************************************************************
	> File Name: socket.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Thu 11 Sep 2014 10:19:21 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>
#include <string.h>
#include <netinet/in.h>

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
	
	client_fd=accept(fd,(struct sockaddr*)&peerAddr,&len);
	if(client_fd==-1){
		perror("accept");
		return -1;
	}
	else{
		printf("connect with ip:%s and port:%d\n",inet_ntoa(peerAddr.sin_addr),ntohs(peerAddr.sin_port));
		close(client_fd);
	}

	close(fd);
    return 0;
}
