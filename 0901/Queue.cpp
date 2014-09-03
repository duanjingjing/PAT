/*************************************************************************
	> File Name: Queue.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Tue 02 Sep 2014 09:01:04 PM PDT
 ************************************************************************/

#include "Queue.h"
#include <assert.h>

Queue::Queue():head_(NULL),tail_(NULL),size_(0){
}

Queue::~Queue(){
	clear();
}

void Queue::push(int data){
	NodePtr pt=new Node;
	pt->data_=data;
	pt->next_=NULL;

	if(head_==NULL){
		head_=tail_=pt;
	}
	else{
		tail_->next_=pt;
		tail_=pt;
	}

	size_++;
}


void Queue::pop(){
	assert(!isEmpty());
	NodePtr pt=head_;
	head_=head_->next_;
	delete pt;
	size_--;

}


int Queue::top() const{
	assert(!isEmpty());
	return head_->data_;
}

void Queue::clear() {
	while(!isEmpty()){
		pop();
	}
}

bool Queue::isEmpty() const{
	return head_==NULL;
}

size_t Queue::getSize() const{
	return size_;
}

