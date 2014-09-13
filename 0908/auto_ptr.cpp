/*************************************************************************
	> File Name: auto_ptr.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Sun 07 Sep 2014 11:50:51 PM PDT
 ************************************************************************/

#include<iostream>

class Investment{...};

std::auto_ptr<Investment> pInv1(createInvestment());
//收auto_ptrs管理的资源必须绝对没有一个以上的auto_ptr同时指向它
std::auto_ptr<Investment> pInv2(pInv1);//现在pInv2指向对象,pInv1被设为null
pInv1=pInv2;

void f(){
	...
	std::trl::shared_ptr<Investment>
	pInv(createInvestment());
	...

    std::trl::shared_ptr<Investment> pInv2(pInv1);
	pInv1=pInv2;
	...
}






