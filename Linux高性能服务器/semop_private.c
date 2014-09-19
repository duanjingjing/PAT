/*************************************************************************
	> File Name: semop_private.c
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 16 Sep 2014 09:02:39 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//
union semun{
	int val;//用于SETVAL命令
	struct semid_ds* buf;   //用于IPC_STAT和IPC_SET命令
	unsigned short int* array;  //用于GETALL和SETALL命令
	struct seminfo* _buf;
};

//op为-1时执行p操作,op为1时执行v操作
void pv(int sem_id,int op){
	struct sembuf sem_b;
	sem_b.sem_num=0;
	sem_b.sem_op=op;
	sem_b.sem_flg=SEM_UNDO;
	semop(sem_id,&sem_b,1);
}

int main(int argc,char* argv[]){
	int sem_id=semget(IPC_PRIVATE,1,0666);

	union semun sem_un;
	sem_un.val=1;
	semctl(sem_id,0,SETVAL,sem_un);

	pid_t pid=fork();
	if(pid<0){
		return -1;
	}

	else if(pid==0){
		printf("child try to get binary sem\n");
		//父子进程间共享IPC_PRIVATE的信号量关键就在于两者都可以操作该信号量的标示符

		pv(sem_id,-1);
        printf("child get the sem and would release it after 5 seconds\n");
		sleep(5);
		pv(sem_id,1);
		exit(0);
	}

	else{
		printf("parent try to get binary sem\n");
		pv(sem_id,-1);
		printf("parent get the sem and would release if after 5 seconds\n");
		sleep(5);
		pv(sem_id,1);
	}

	waitpid(pid,NULL,0);
	semctl(sem_id,0,IPC_RMID,sem_un);
	return 0;
}


