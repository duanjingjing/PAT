/*************************************************************************
	> File Name: getopt.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 12:52:20 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ERR_EXIT(m) \
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)


int main(int argc,char *argv[]){
	int opt;
	while(1){
		opt=getopt(argc,argv,"nt:");
		if(opt=='?'){
			exit(EXIT_FAILURE);
		}
		if(opt==-1){
			break;
		}

		switch(opt){
			case 't':
				printf("-t\n");
				break;
			case 'n':
				printf("-n:%d\n",atoi(optarg));
                break;
			case ''
		}
	}
}
