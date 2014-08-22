/*************************************************************************
	> File Name: 03alarm.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 12:16:59 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<errno.h>

#define ERR_EXIT(m) \
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)


void handler(int iSignum){
	printf("recv a alarm\n");
	alarm(1);
}

int main(int argc,char *argv[]){
	if(signal(SIGALRM,handler)==SIG_ERR)
		ERR_EXIT("signal");

	alarm(3);

	while(1);
}
