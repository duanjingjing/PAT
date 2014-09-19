/*************************************************************************
	> File Name: SIGURG.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 15 Sep 2014 01:53:51 AM PDT
 ************************************************************************/

/*用SIGURG检测到带外数据是否到来*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <assert.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 1024

static int connfd;

/*SIGURG信号的处理函数*/
void sig_urg(int sig){
   int save_errno=errno;
   char buffer[BUF_SIZE];
   memset(buffer,'\0',BUF_SIZE);

   int ret=recv(connfd,buffer,BUF_SIZE-1,MSG_OOB);//接受带外数据
   printf("got %d bytes of oob data: %s\n",ret,buffer);
   errno=save_errno;
}

void addsig(int sig,void (*sig_handler)(int)){
    struct sigaction sa;
	sa.sa_handler=sig_handler;
	sa.sa_flags |=SA_RESTART;
	sigfillset(&sa.sa_mask);

	assert(sigaction(sig,&sa,NULL)!=-1);
}

int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip_address port_number\n",argv[0]);
		return -1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	int ret=0;
	struct sockaddr_in address;
	address.sin_family=AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port=htons(port);

	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd!=-1);

	ret=bind(sockfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	ret=listen(sockfd,5);
	assert(ret!=-1);

	struct sockaddr_in client;
	socklen_t len=sizeof(client);

	int connfd=accept(sockfd,(struct sockaddr*)&client,&len);
	if(connfd<0){
		printf("errno is:%d\n",errno);
	}

	else{
		addsig(SIGURG,sig_urg);
		/*使用SIGURG信号之前,我们必须设置socket的宿主进程或进程组*/
		fcntl(connfd,F_SETOWN,getpid());

		char buffer[BUF_SIZE];
		while(1){//循环接受普通数据
			memset(buffer,'\0',BUF_SIZE);
			ret=recv(connfd,buffer,BUF_SIZE-1,0);
            if(ret<=0){
				break;
			}

			printf("got %d bytes of normal data:%s\n",ret,buffer);
		}
		close(connfd);
	}
	close(sockfd);
	return 0;
}



