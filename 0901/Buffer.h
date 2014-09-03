/*************************************************************************
	> File Name: Buffer.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 02 Sep 2014 09:06:06 PM PDT
 ************************************************************************/

#ifndef BUFFER_H
#define BUFFER_H


#include "Queue.h"
#include "MutexLock.h"
#include "Condition.h"
#include <iostream>

class Buffer{
public:
	Buffer(size_t size);
	~Buffer();

	bool isEmpty() const;
	bool isFull() const;

	void produce(int data);
	int consume();

private:
	Queue queue_;
	/*
	 *mutable代表在const函数中仍可以被修改
	 */
    mutable MutexLock mutex_;
	Condition full_;
	Condition empty_;
	size_t size_;
};







#endif
