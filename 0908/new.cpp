/*************************************************************************
	> File Name: new.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 08 Sep 2014 01:11:56 AM PDT
 ************************************************************************/

#include<iostream>

std::string* stringArray=new std::string[100];
...
delete stringArray;

int priority();
void processWidget(std::trl::shared_ptr<Widget> pw,
		int priority());

//以独立语句将newed对象存储于(置于)智能指针内。如果不这样做,一旦异常抛出,有可能导致难以察觉的
processWidget(std::trl::shared_ptr<Widget>(new Widget),priority());

//让接口容易被正确使用,不易被误用
struct Day{
   explicit Day(int d):val(d){}
   int val;
};

struct Month{
	explicit Month(int m):val(m){}
	int val;
};

struct Year{
	explicit Year(int y):val(y){}
	int val;
};

class Data{
public:
	Date(const Month& m,const Day& d,const Year& y);
    ...
};

std::trl::shared_ptr<Investment> createInvestment(){
	std::tr1::shared_ptr<Investment> retVal(static_cast<Investment*>(0),)
}

std::tr1::shared_ptr<Investment> pInv(static_cast<Investment*>(0),getRidInvestment);


