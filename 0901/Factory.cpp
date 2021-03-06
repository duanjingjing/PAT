/*************************************************************************
	> File Name: Factory.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 12:10:14 AM PDT
 ************************************************************************/


#include "Factory.h"
using namespace std;

Factory::Factory(size_t bufferSize,
				size_t producerNum,
				size_t consumeNum):
	bufferSize_(bufferSize),
    buffer_(bufferSize),
	producerNum_(producerNum),
	consumerNum_(consumeNum),
	produceThreads_(producerNum_,ProduceThread(buffer_)),
	consumeThreads_(consumerNum_,ConsumeThread(buffer_)){
}


void Factory::start(){
	for(vector<ProduceThread>::iterator it=produceThreads_.begin();
			it!=produceThreads_.end();it++){
		it->start();
	}

   for(vector<ConsumeThread>::iterator it=consumeThreads_.begin();it!=consumeThreads_.end();it++){
	   it->start();
   }


	for(vector<ProduceThread>::iterator it=produceThreads_.begin();
			it!=produceThreads_.end();it++){
		it->join();
	}

   for(vector<ConsumeThread>::iterator it=consumeThreads_.begin();it!=consumeThreads_.end();it++){
	   it->join();
   }

}





