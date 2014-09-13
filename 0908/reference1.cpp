/*************************************************************************
	> File Name: reference1.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 08 Sep 2014 02:35:38 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;

//返回对象时,别妄想返回其referece

class Rational{
public:
	Rational(int numbertor=0,int demon=1);
	...
private:
	int n,d;

	friend Rational operator*(const Rational& lhs,
			                  const Rational& rhs);
};

const Rational& operator*(const Ration& lhs,
						const Ration& rhs){
	Rational* result=new Rational(lhs.n*rhs.n,lhs.d*rhs.d);
	return *result;
}


