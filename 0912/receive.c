/*************************************************************************
	> File Name: receive.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 12 Sep 2014 07:31:49 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip port\n",argv[0]);
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

	int ret=connect(sockfd,(struct sockaddr*)&address,sizeof(address));
	if(ret==-1){
		perror("connect");
		exit(-1);
	}

    char buf[1024];
	while(memset(buf,0,sizeof(buf)),fgets(buf,1024,stdin)!=NULL){
		buf[strlen(buf)-1]='\0';
		send(sockfd,buf,strlen(buf),0);
        memset(buf,0,sizeof(buf));
		recv(sockfd,buf,sizeof(buf),0);
		printf("receive data:%s\n",buf);
	}

	close(sockfd);
	return 0;
}
