/*************************************************************************
	> File Name: backlog.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Thu 11 Sep 2014 08:05:51 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static int stop=0;
/*SIGTEAM信号的处理函数,触发时结束主程序中的循环*/
static void handle_term(int sig){
	stop=1;
}

int main(int argc,const char* argv[]){
	signal(SIGTERM,handle_term);

	if(argc<=3){
		printf("usage:%s ip_address port backlog\n",
				basename(argv[0]));
		return 1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);
	int backlog=atoi(argv[3]);

	int sock=socket(PF_INET,SOCK_STREAM,0);
	assert(sock>=0);

	/* 创建一个IPV4 socket地址*/
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
    address.sin_family=AF_INET;
	address.sin_port=htons(port);
	address.sin_addr.s_addr=inet_addr(ip);

	int ret=bind(sock,(struct sockaddr*)&address,sizeof(address));
	assert(ret!=-1);

	ret=listen(sock,backlog);
	assert(ret!=-1);

	/*循环等待连接，直到有SIGTERM信号被它中断*/
	while(!stop){
		sleep(1);
	}

	close(sock);
	return 0;
}
