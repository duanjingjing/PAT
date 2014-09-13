/*************************************************************************
	> File Name: recv.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Thu 11 Sep 2014 10:35:59 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip_ port\n",argv[0]);
		return -1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));

	server_addr.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&server_addr.sin_addr);
	server_addr.sin_port=htons(port);

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd!=-1);

	if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		printf("connection failed!\n");
	}

	else{
		/*
		const char* oob_data="abc";
		const char* normal_data="123";
		send(sockfd,normal_data,strlen(normal_data),0);
		send(sockfd,oob_data,strlen(oob_data),MSG_OOB);
		send(sockfd,normal_data,strlen(normal_data),0);
		*/
		int ret=recv(sockfd,)
	}
	close(sockfd);
	return 0;
}
