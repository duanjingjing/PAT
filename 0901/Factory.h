/*************************************************************************
	> File Name: Factory.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 12:22:31 AM PDT
 ************************************************************************/

#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include "Buffer.h"
#include "ProduceThread.h"
#include "ConsumeThread.h"


class Factory{
public:
	Factory(size_t bufferSize,
			size_t producerNum,
			size_t consumerNum);
	void start();

private:
	size_t bufferSize_;
	Buffer buffer_;

	size_t producerNum_;
	size_t consumerNum_;

	std::vector<ProduceThread> produceThreads_;
	std::vector<ConsumeThread> consumeThreads_;
};



#endif
