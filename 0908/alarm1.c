/*************************************************************************
	> File Name: alarm1.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 07 Sep 2014 11:44:27 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

#define ERR_EXIT(m) \
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

//SIGALRM信号
void handler(int signum){
	static int beeps=0;
	printf("BEEP\n");
    
	if(++beeps<5)
		alarm(1);
	else{
		printf("BOOM\n");
		exit(EXIT_SUCCESS);
	}
}

int main(int argc,const char* argv[]){
	if(signal(SIGALRM,handler)==SIG_ERR)
		ERR_EXIT("signal");

	alarm(1);
	while(1);

	return 0;
}
