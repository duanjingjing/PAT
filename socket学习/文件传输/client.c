/*************************************************************************
	> File Name: client.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 03:26:58 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "msg.h"

int main(int argc,char* argv[]){
	if(argc!=3){
		printf("USAGE:EXE IP PORT");
		exit(-1);
	}

	MSG msg,rcv_msg;
	int fd_client,fd_file;

	if((fd_client=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
        exit(-1);
	}

	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(server_addr));

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);

	if(-1==connect(fd_client,(struct sockaddr*)&server_addr,sizeof(server_addr))){
		perror("connect");
		close(fd_client);
		exit(-1);
	}

	printf("input: ");
	scanf("%s",msg.s_buf);
	fd_file=open("2.xv",O_WRONLY|O_CREAT,0666);
	msg.s_len=strlen(msg.s_buf);
	send(fd_client,&msg,msg.s_len+MSG_LEN,0);
    int total=0;

	while(1){
		memset(&rcv_msg,0,sizeof(MSG));
		recv(fd_client,&rcv_msg,MSG_LEN,0);
		total+=rcv_msg.s_len;
        system("clear");
		printf("downloading...%.2f kb\n",(double)total/1024);

		if(rcv_msg.s_len>0){
            recv(fd_client,&rcv_msg.s_buf,rcv_msg.s_len,0);
			write(fd_file,rcv_msg.s_buf,rcv_msg.s_len);
		}
		else{
			break;
		}
	}

	close(fd_file);
	close(fd_client);
	return 0;
}
