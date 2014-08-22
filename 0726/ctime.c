/*************************************************************************
	> File Name: ctime.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 12:12:12 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<errno.h>

#define ERR_EXIT(m) \
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)


int main(int argc,char *argv[]){
	time_t tt;
	time(&tt);

	printf("time=%s\n",ctime(&tt));
}
