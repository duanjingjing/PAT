/*************************************************************************
	> File Name: env.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 12:47:39 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

extern char **environ;//这里使用了系统的一个全局变量

int main(int argc,char *argv[]){
	int i;
	for(i=0;environ[i]!=NULL;i++)
		printf("%s\n",environ[i]);

	return 0;
}

