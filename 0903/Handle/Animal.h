/*************************************************************************
	> File Name: Animal.h
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 01:50:20 AM PDT
 ************************************************************************/

#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>

class Animal{
public:
	virtual ~Animal(){}
	virtual void display() const=0;
	virtual Animal* copy() const=0;
};

class Cat:public Animal{
public:
	void display() const{
		std::cout<<"Cat "<<std::endl;
	}

	Cat* copy() const{
		return new Cat(*this);
	}
};

class Dog:public Animal{
public:
	void display() const{
		std::cout<<"Dog "<<std::endl;
	}

	Dog* copy() const{
		return new Dog(*this);
	}
};

class Bear:public Animal{
public:
	void display() const{
		std::cout<<"Bear "<<std::endl;
	}

	Bear* copy() const{
		return new Bear(*this);
	}
};


#endif
