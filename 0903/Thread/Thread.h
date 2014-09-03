/*************************************************************************
	> File Name: Thread.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 05:06:05 AM PDT
 ************************************************************************/

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

class Thread{
public:
	virtual Thread(){}
	virtual void run()=0;
	static void* threadFunc(void *arg);
	void start();
	void join();

private:
	pthread_t tid_;
};


#endif
