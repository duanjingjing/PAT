/*************************************************************************
	> File Name: Condition.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 02 Sep 2014 08:51:30 PM PDT
 ************************************************************************/

#ifndef CONDITION_H
#define CONDITION_H

#include <pthread.h>
//condition中仅包含Mutex的引用,所以不需要头文件
class MutexLock;

class Condition{
public:
	Condition(MutexLock &lock);
	~Condition();
	void wait();
	void notify();
	void notifyAll();

private:
	pthread_cond_t cond_;
	MutexLock &lock_;
};










#endif
