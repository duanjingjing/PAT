/*************************************************************************
	> File Name: client.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 07:15:23 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

typedef struct tagmsg{
	int client_id;
	char my_data[512];
}MSG;


int main(int argc,char *argv[]){
	int server_fd,client_fd;
	MSG my_msg;
	memset(&my_msg,0,sizeof(MSG));

	char client_info[512];
	char szBuf[512];
	sprintf(client_info,"CLIENT_FIFO_%d",getpid());
    mkfifo(client_info,0666);

	my_msg.client_id=getpid();
    server_fd=open("SERVER_FIFO_NAME",O_WRONLY);
	if(server_fd==-1){
		perror("open");
		exit(-1);
	}


	int iRet;
	while((iRet=read(STDIN_FILENO,szBuf,sizeof(szBuf)))>0){
         szBuf[iRet]='\0';
		 strcpy(my_msg.my_data,szBuf);
		 write(server_fd,&my_msg,sizeof(MSG));

		 client_fd=open(client_info,O_RDONLY);
		 if(client_fd==-1){
			 perror("open");
			 exit(-1);
		 }

		 memset(&my_msg,0,sizeof(MSG));
		 iRet=read(client_fd,&my_msg,sizeof(MSG));
		 my_msg.my_data[iRet]='\0';
		 write(STDOUT_FILENO,my_msg.my_data,strlen(my_msg.my_data));
         close(client_fd);
	} 
	unlink(client_info);
}
