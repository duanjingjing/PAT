/*************************************************************************
	> File Name: Invest.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 07 Sep 2014 09:58:14 PM PDT
 ************************************************************************/

#include<iostream>
using namespace std;


class Investment{
	....
};

Investment* createInvestment();//返回指针,指向Investment继承体系内的动态分配对象

void f(){

	Investment* pInv=createInvestment();
	...
    delete pInv;
}

//以对象管理资源
//
void f(){
	std::auto_ptr<Investment> pInv(createInvestment());
	std::auto_ptr<Investment> pInv2(pInv1);
}




