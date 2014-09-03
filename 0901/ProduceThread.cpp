/*************************************************************************
	> File Name: ProduceThread.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 02 Sep 2014 11:59:07 PM PDT
 ************************************************************************/

#include "ProduceThread.h"
#include "Buffer.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;

ProduceThread::ProduceThread(Buffer &buffer):tid_(0),
	buffer_(buffer){
		::srand(2525);
}

void ProduceThread::start(){
    pthread_create(&tid_,NULL,threadFunc,this);
}

void* ProduceThread::threadFunc(void *arg){
	ProduceThread *pt=static_cast<ProduceThread*>(arg);
	pt->run();

	return NULL;
}

void ProduceThread::run(){
	while(1){
		int data=rand()%1000;
		cout<<"produce a data:"<<data<<endl;
		buffer_.produce(data);
		sleep(5);
	}
}

void ProduceThread::join(){
	 pthread_join(tid_,NULL);
}



