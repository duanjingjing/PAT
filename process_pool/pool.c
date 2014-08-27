/*************************************************************************
	> File Name: pool.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 26 Aug 2014 06:04:55 AM PDT
 ************************************************************************/

#include "pool.h"

static void child_main();

static void handle_request(int fd,SA* addr,char* buf){
	sendto(fd,buf,strlen(buf),0,(struct sockaddr*)addr,sizeof(SA));
}

int make_child(pCHLD arr,int cnt){
	int index;
	int max_read=0x80000000;

	for(index=0;index<cnt;index++){
		pid_t pid;
		int fds1[2],fds2[2];
		pipe(fds1);//0 pr 1 cw
		pipe(fds2);//0 cr 1 pw

		pid=fork();
		if(pid==0){
			close(fds1[0]);
			close(fds2[1]);
           
			dup2(fds2[0],0);
			dup2(fds1[1],1);
			child_main();
            exit(0);
		}
		else{
			close(fds1[1]);
			close(fds2[0]);
			arr[index].s_pid=pid;
			arr[index].s_flag=S_IDLE;

			if(fds1[0]>max_read){
				max_read=fds1[0];
			}

			arr[index].s_write=fds2[1];
		}
	}
	return max_read;
}


void child_main(){

	SA client_addr;
	int fd_socket;
	char buf[1024];

	while(1){
		bzero(&client_addr,sizeof(SA));
		bzero(buf,1024);
		client_addr.sin_family=AF_INET;
		scanf("%d %d %s",&(client_addr.sin_port),&(client_addr.sin_addr.s_addr),buf);
		fd_socket=socket(AF_INET,SOCK_DGRAM,0);
		handle_request(fd_socket,&client_addr,buf);

		printf("1");
		fflush(stdout);
	}
}
