/*************************************************************************
	> File Name: 3.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 02:31:01 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

class Base{
public:
	 void print()const{
		cout<<"In Base"<<endl;
	}
};

class Derived:public Base{
public:
	void print() const{
		cout<<"In Derived"<<endl;
	}
};

int main(int argc,const char* argv[]){
	cout<<"sizeof Base "<<sizeof(Base)<<endl;
	cout<<"sizeof Derived "<<sizeof(Derived)<<endl;

	return 0;
}
