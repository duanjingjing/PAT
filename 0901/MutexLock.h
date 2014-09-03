/*************************************************************************
	> File Name: MutexLock.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 02 Sep 2014 08:47:21 PM PDT
 ************************************************************************/

#ifndef MUTEX_LOCK_H
#define MUTEX_LOCK_H

#include <pthread.h>
#include <stdexcept>

class MutexLock{
	public:
		MutexLock(){
			if(pthread_mutex_init(&lock_,NULL)){
				throw std::runtime_error("init lock fail!");
			}
		}

		~MutexLock(){
			if(pthread_mutex_destroy(&lock_)){
				throw std::runtime_error("destroy lock fail!");
			}
		}

		void lock(){
			if(pthread_mutex_lock(&lock_)){
				throw std::runtime_error("lock failed!");
			}
		}

		void unlock(){
			if(pthread_mutex_unlock(&lock_)){
				throw std::runtime_error("unlock failed!");
			}
		}

		//这里提供指针是为了cond的wait操作
		pthread_mutex_t* getMutexPtr(){
			return &lock_;
		}

private:
		pthread_mutex_t lock_;
};










#endif
