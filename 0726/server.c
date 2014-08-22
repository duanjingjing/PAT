/*************************************************************************
	> File Name: server.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 06:50:53 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>
#include<ctype.h>
#include<sys/types.h>

typedef struct tagmsg{
	int client_id;
	char my_data[512];
}MSG;

int main(int argc,char *argv[]){
	int server_fd,client_fd;
	MSG my_msg;
	memset(&my_msg,0,sizeof(MSG));

	char szBuf[256];
	mkfifo("SERVER_FIFO_NAME",0666);

	server_fd=open("SERVER_FIFO_NAME",O_RDONLY);
	if(server_fd==-1){
		perror("open");
		exit(-1);
	}

	int iRet;
	while((iRet=read(server_fd,&my_msg,sizeof(MSG)))>0){
		printf("recv msg:%s\n",my_msg.my_data);
		char *pstr=my_msg.my_data;
		while(*pstr!='\0'){
			*pstr=toupper(*pstr);
			pstr++;
		}

		memset(szBuf,0,sizeof(szBuf));
		sprintf(szBuf,"CLIENT_FIFO_%d",my_msg.client_id);
		client_fd=open(szBuf,O_WRONLY);
		if(client_fd==-1){
			perror("open");
			exit(-1);
		}

		write(client_fd,&my_msg,sizeof(MSG));
		printf("After update:%s\n",my_msg.my_data);
		printf("OVER\n");
		close(client_fd);
	}
	return 0;
}
