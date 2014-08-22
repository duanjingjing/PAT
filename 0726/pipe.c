/*************************************************************************
	> File Name: pipe.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sat 26 Jul 2014 01:06:22 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(){
	int fds[2];
	pipe(fds);

	char szBuf[32]={0};
	if(fork()==0){
		close(fds[1]);
		sleep(2);
		if(read(fds[0],szBuf,sizeof(szBuf))>0)
			puts(szBuf);
		close(fds[0]);
		exit(0);
	}else{
		close(fds[0]);
		write(fds[1],"hello",6);
		waitpid(-1,NULL,0);

		close(fds[1]);
		exit(0);
	}
	return 0;
}
