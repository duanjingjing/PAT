/*************************************************************************
	> File Name: pure.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 02:43:21 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

class Animal{
public:
	virtual void run()=0;
};

int main(int argc,const char* argv[]){
	cout<<"sizeof Animal "<<sizeof(Animal)<<endl;
	return 0;
}
