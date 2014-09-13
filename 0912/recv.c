/*************************************************************************
	> File Name: recv.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Thu 11 Sep 2014 10:55:46 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip_address port_number\n",argv[0]);
		return -1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address,sizeof(address));

	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int sock=socket(PF_INET,SOCK_STREAM,0);
	assert(sock!=-1);

	int ret=bind(sock,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	ret=listen(sock,5);
	assert(ret!=-1);

	struct sockaddr_in client;
	socklen_t addrlen=sizeof(client);

	int connfd=accept(sock,(struct sockaddr*)&client,&addrlen);
	if(connfd==-1){
		printf("errno is:%d\n",errno);
	}
	else{
		char buffer[BUF_SIZE];

		memset(buffer,'\0',BUF_SIZE);
		ret=recv(connfd,buffer,BUF_SIZE-1,0);
	    printf("receive data: %s\n",buffer);
	}

}
