/*************************************************************************
	> File Name: mutex.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Mon 08 Sep 2014 12:22:44 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;


//资源管理类(RAII)
class Lock{
public:
	explicit Lock(Mutex* pm):mutexPtr(pm,unlock()){//并以unlock函数为删除器
		lock(mutexPtr.get());
	}

private:
	std::trl::shared_ptr<mutex>  mutexPtr;//我们所要做的释放动作是解除锁定而非删除,使用shared_ptr替换raw_pointer
};
 

Mutex m;
...
{
	Lock m1(&m);
}

//在资源管理类中提供对原始资源的访问
std::trl::shared_ptr<Investment> pInv(createInvestment());

int daysHeld(const Investmnet* pi);//返回投资天数

int days=daysHeld(pInv);//错误！

//trl::shared_ptr和auto_ptr都提供一个get成员函数,用来执行显示转换
int days=daysHeld(pInv.get());//

FontHandle getFont();//这是个C API.
void releaseFont(FontHandle fh);

class Font{
public:
	explicit Font(FontHandle fh):f(fh){}//获得资源，采用pass-by-value
	~Font(){releaseFont(f);}//释放资源
	FontHandle get() const{return f;}//显示转换函数
	operator FontHandle() const {return f;} //隐式转换函数
private:
	FontHandle f;
};

Font f(getFont());
int newFontSize();
....





