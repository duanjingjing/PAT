/*************************************************************************
	> File Name: splicie.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 12 Sep 2014 07:16:15 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>


int main(int argc,const char* argv[]){
	if(argc<=2){
		printf("usage:%s ip_address port_number\n",argv[0]);
		return -1;
	}

	const char* ip=argv[1];
	int port=atoi(argv[2]);

	struct sockaddr_in address;

}
