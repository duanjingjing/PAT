/*************************************************************************
	> File Name: Thread.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 05:08:00 AM PDT
 ************************************************************************/

#include "Thread.h"

void Thread::start(){
	pthread_create(&tid_,NULL,threadFunc,this);
}

void* Thread::threadFunc(void* arg){
	Thread*pt=static_cast<Thread*>(arg);
	pt->run();
	return NULL;
}

void Thread::join(){
	pthread_join(tid_,NULL);
}
