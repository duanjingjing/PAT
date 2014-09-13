/*************************************************************************
	> File Name: exec.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 07 Sep 2014 11:04:16 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc,const char* argv[]){
	printf("Enter main......\n");

	//使用command中的代码替换当前进程映像
	execlp("ls","ls","-l",NULL);

	printf("Leave main.......\n");
	return 0;
}
