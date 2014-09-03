/*************************************************************************
	> File Name: Buffer.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 02 Sep 2014 09:08:48 PM PDT
 ************************************************************************/

#include "Buffer.h"
using namespace std;

Buffer::Buffer(size_t size):mutex_(),full_(mutex_),
	empty_(mutex_),size_(size){
}


Buffer::~Buffer(){

}

bool Buffer::isEmpty() const{
	 mutex_.lock();
	 bool ret=queue_.isEmpty();
	 mutex_.unlock();

	 return ret;
}

bool Buffer::isFull() const{
	mutex_.lock();
	bool ret=queue_.getSize()>=size_;
	mutex_.unlock();
	return ret;
}

void Buffer::produce(int data){
	mutex_.lock();
	while(queue_.getSize()>=size_){
		empty_.wait();
	}

	queue_.push(data);
	cout<<"produce size="<<queue_.getSize()<<endl;

	full_.notify();
	mutex_.unlock();
}

/*
 *如果中间assert失败
 *
 *
 */
int  Buffer::consume(){
	mutex_.lock();

	while(queue_.isEmpty()){
		full_.wait();
	}

	int ret=queue_.top();
	queue_.pop();
	cout<<"consume size="<<queue_.getSize()<<endl;

	empty_.notify();
	mutex_.unlock();

	return ret;
}
