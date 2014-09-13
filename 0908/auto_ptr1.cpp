/*************************************************************************
	> File Name: auto_ptr1.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 07 Sep 2014 11:57:49 PM PDT
 ************************************************************************/

#include<iostream>
#include <string>
#include <memory>
using namespace std;

class Animal{
public:
	Animal(){}
	virtual ~Animal(){}
	virtual Animal* createAnimal()=0;
	virtual void print() const=0;
};


class Dog:public Animal{
public:
	Animal* createAnimal(){
		return new Dog(*this);
	}

	void print() const{
		cout<<"Dog called!\n";
	}
};

class Cat:public Animal{
public:
	Animal* createAnimal(){
		return new Cat(*this);
	}

	void print() const{
		cout<<"Cat called!\n";
	}
};

int main(int argc,const char* argv[]){
	Cat c1;
    Dog d1;
    shared_ptr<Animal> pInv(c1.createAnimal());
    shared_ptr<Animal> pInv2(d1.createAnimal());
	pInv->print();
    pInv=pInv2;
	pInv->print();

	/*
	if(pInv2==NULL){
		cout<<"pInv2 null"<<endl;
	}
	else{
	    pInv2->print();
	}
	*/
	pInv2->print();
}


