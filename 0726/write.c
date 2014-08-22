/*************************************************************************
	> File Name: write.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 06:43:34 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

int main(){
	int fd=open("myfifo.fifo",O_WRONLY);
	write(fd,"hello",6);
	close(fd);
	return 0;
}
