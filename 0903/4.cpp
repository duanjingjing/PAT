/*************************************************************************
	> File Name: 4.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Wed 03 Sep 2014 02:37:25 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

class Test{
public:
	virtual void test();
	int a_;
};

int main(int argc,const char* argv[]){
	cout<<sizeof(Test)<<endl;
	return 0;
}
