/*************************************************************************
	> File Name: server.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 04:56:42 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char* argv[]){
	if(argc!=3){
		printf("USAGE:EXE IP PORT");
		exit(-1);
	}

	int fd_server;
	char buf[1024];
	fd_server=socket(AF_INET,SOCK_DGRAM,0);
	if(fd_server==-1){
		perror("socket");
		exit(-1);
	}

	struct sockaddr_in server_addr,client_addr;
	int addrlen=sizeof(client_addr);
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);

	if(-1==bind(fd_server,(struct sockaddr*)&server_addr,addrlen)){
		perror("bind");
		close(fd_server);
		exit(-1);
	}

	while(1){
		bzero(&client_addr,sizeof(client_addr));
		bzero(buf,1024);

		recvfrom(fd_server,buf,1024,0,(struct sockaddr*)&client_addr,&addrlen);
		printf("\t\tip:port :%s:%d\n\t%s\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),buf);
		sendto(fd_server,buf,strlen(buf),0,(struct sockaddr*)&client_addr,addrlen);
	}
	return 0;
}
