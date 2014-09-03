/*************************************************************************
	> File Name: Handle.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 01:58:27 AM PDT
 ************************************************************************/

#include "Handle.h"
#include "Animal.h"

Handle::Handle():ptr_(NULL){
}

Handle::Handle(const Animal& other):
	ptr_(other.copy()){//这里通过引用触发了多态
}

Handle::Handle(const Handle& other)
:ptr_(other.ptr_->copy()){

}

Handle::~Handle(){
	delete ptr_;
}

Handle& Handle::operator=(const Handle& other){
	if(this!=&other){
		delete ptr_;
		ptr_=other.ptr_->copy();
	}

	return *this;
}


Animal* Handle::operator->(){
	return ptr_;
}

const Animal* Handle::operator->() const{
	return ptr_;
}


