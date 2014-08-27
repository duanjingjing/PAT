/*************************************************************************
	> File Name: client.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 10:44:14 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char* argv[]){
	if(argc!=3){
		printf("USAGE:EXE IP PORT");
		exit(-1);
	}


	int fd=socket(AF_INET,SOCK_DGRAM,0);
	if(fd==-1){
		perror("socket");
		exit(-1);
	}

	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);

	char buf[1024];

	while(1){
		memset(buf,0,sizeof(buf));
		fgets(buf,1024,stdin);
		sendto(fd,buf,strlen(buf),0,(struct sockaddr*)&server_addr,sizeof(server_addr));

		memset(buf,0,1024);
		socklen_t addrlen=sizeof(server_addr);
		printf("starting receving.....\n");
		recvfrom(fd,buf,sizeof(buf),0,(struct sockaddr*)&server_addr,&addrlen);
		printf("%s\n",buf);
	}
}
