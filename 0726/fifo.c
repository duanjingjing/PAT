/*************************************************************************
	> File Name: fifo.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 06:37:24 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int argc,char *argv[]){
	if(argc!=2){
		puts("Usage:Mkfifo.exe {filename}");
		exit(-1);
	}

	if(mkfifo(argv[1],0666)==-1){
		perror("mkfifo fail");
		return -1;
	}
	return 0;
}
