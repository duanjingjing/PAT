/*************************************************************************
	> File Name: getenv.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 12:50:49 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[]){
	printf("%s\n",getenv("SHELL"));
	return 0;
}
