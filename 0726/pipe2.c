/*************************************************************************
	> File Name: pipe2.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 06:29:28 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

int main(){
	int fds[2];
    pipe(fds);

	char szBuf[32]={0};
	/*
	sigset_t sigSet;
	sigemptyset(&sigSet);
	sigaddset(&sigSet,SIGPIPE);
	sigprocmask(SIG_BLOCK,&sigSet,NULL);
*/
	if(fork()==0){
		close(fds[1]);
		sleep(2);
		if(read(fds[0],szBuf,32)>0)
			puts(szBuf);
		close(fds[0]);
	}else{
		close(fds[0]);
		write(fds[1],"hello",6);
		wait(NULL);
		write(fds[1],"hello",6);
		close(fds[1]);
	}
	return 0;
}
