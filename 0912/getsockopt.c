/*************************************************************************
	> File Name: getsockopt.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Thu 11 Sep 2014 11:17:11 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(){
	int sock=socket(PF_INET,SOCK_STREAM,0);
    assert(sock>=0);

	int reuse=1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));

}
