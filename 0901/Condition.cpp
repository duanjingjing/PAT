/*************************************************************************
	> File Name: Condition.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 02 Sep 2014 08:54:23 PM PDT
 ************************************************************************/

#include "Condition.h"
#include "MutexLock.h"
#include <stdexcept>

using namespace std;

Condition::Condition(MutexLock &lock):lock_(lock){
	if(pthread_cond_init(&cond_,NULL)){
		throw std::runtime_error("init cond error!");
	}
}

Condition::~Condition(){
	if(pthread_cond_destroy(&cond_)){
		throw std::runtime_error("destroy cond error!");
	}
}

void Condition::wait(){
	if(pthread_cond_wait(&cond_,lock_.getMutexPtr())){
		throw std::runtime_error("wait cond error!");
	}
}

void Condition::notify(){
	if(pthread_cond_signal(&cond_)){
		throw std::runtime_error("signal cond error!");
	}
}

void Condition::notifyAll(){
	if(pthread_cond_broadcast(&cond_)){
		throw std::runtime_error("boradcast cond error!");
	}
}


