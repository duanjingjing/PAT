/*************************************************************************
	> File Name: ConsumeThread.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 12:04:35 AM PDT
 ************************************************************************/

#ifndef CONSUME_THREAD_H
#define CONSUME_THREAD_H

#include <pthread.h>
#include <iostream>

class Buffer;

class ConsumeThread{
public:
	ConsumeThread(Buffer& buffer);

	void start();
	static void* threadFunc(void* arg);
	void run();
	void join();
private:
	pthread_t tid_;
	Buffer & buffer_;
};



#endif
