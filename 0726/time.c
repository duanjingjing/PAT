/*************************************************************************
	> File Name: time.c  
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 12:05:14 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<time.h>
#include<sys/time.h>

#define ERR_EXIT(m) \
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

int main(int argc,char *argv[]){
    time_t tt;
	time(&tt);

	printf("time=%ld\n",tt);

	struct tm* pt=gmtime(&tt);

	printf("%04d-%02d-%02d  %02d:%02d:%02d\n",(1990+pt->tm_year),
			(1+pt->tm_mon),pt->tm_mday,(8+pt->tm_hour),pt->tm_min,pt->tm_sec);
	return 0;
}
