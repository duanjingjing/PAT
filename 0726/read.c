/*************************************************************************
	> File Name: read.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 06:44:38 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
	int fd=open("myfifo.fifo",O_RDONLY);
	char szBuf[32]={0};
	if(read(fd,szBuf,sizeof(szBuf))>0)
		puts(szBuf);
	close(fd);
	return 0;
}
