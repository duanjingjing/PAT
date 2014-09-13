/*************************************************************************
	> File Name: waitpid.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 07 Sep 2014 11:07:48 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define ERR_EXIT(m) \
	do{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

#define N 10
int main(int argc,const char* argv[]){
	pid_t pid;

	int i;
	for(i=0;i<N;i++){
		//父进程创建完子进程继续循环
		//子进程直接退出
		pid=fork();
		if(pid==-1){
			ERR_EXIT("fork");
		}

		else if(pid==0)
			exit(100+i);//子进程返回了状态码
	}

	int status;//接受子进程的状态
	while((pid=waitpid(-1,&status,0))>0){
		if(WIFEXITED(status))  //如果该进程正常退出
			printf("child %d terminaterd normally with code:%d\n",pid,WEXITSTATUS(status));
		else
			printf("child %d terminated abnormally!\n",pid);
	}

	/*
	 *异步回收子进程
	 *
	 *
	 */

	if(errno!=ECHILD)
		ERR_EXIT("waitpid");
	return 0;
}
