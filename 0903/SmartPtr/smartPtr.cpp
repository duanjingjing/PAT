/*************************************************************************
	> File Name: smartPtr.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 01:40:09 AM PDT
 ************************************************************************/

#include "smartPtr.h"

SmartPtr::SmartPtr(Animal* ptr):ptr_(ptr){
}

SmartPtr::~SmartPtr(){
	delete ptr_;
}

Animal &SmartPtr::operator*(){
	return *ptr_;
}

const Animal& SmartPtr::operator*() const{
	return *ptr_;
}

Animal* SmartPtr::operator->(){
	return ptr_;
}

const Animal* SmartPtr::operator->() const{
	return ptr_;
}



