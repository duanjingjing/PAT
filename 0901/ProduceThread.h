/*************************************************************************
	> File Name: ProduceThread.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 02 Sep 2014 11:57:32 PM PDT
 ************************************************************************/

#ifndef PRODUCE_THREAD_H
#define PRODUCE_THREAD_H

#include <pthread.h>

class Buffer;
class ProduceThread{
public:
	ProduceThread(Buffer &buffer);

	void start();
	static void* threadFunc(void* arg);
	void run();
	void join();
private:
	pthread_t tid_;
	Buffer &buffer_;
};


#endif
