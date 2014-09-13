/*************************************************************************
	> File Name: shape.cpp
	> Author: canjian
	> Mail:410001089@qq.com 
	> Created Time: Fri 12 Sep 2014 12:37:18 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;


条款34:区分接口继承和实现继承

class Shape{
public:
	virtual void draw() const=0;
	virtual void error(const std:string& msg);
	int objectID() const;
	...
};

class Rectangle:public Shape{...};
class Ellipse:public Shape{...};

//pure virtual函数有两个最突出的特性:它们必须被任何"继承了它们"的具象class重新声明，而且它们在抽象class中通常没有定义。

Shape *ps=new Shape;//错误！Shape是抽象的
Shape *ps1=new Rectangle;
ps1->draw();//调用Rectangle::draw
Shape* ps2=new Ellipse;
ps2->draw();
ps1->Shape::draw();
ps2->Shape::draw();



/***********************************************/
class Airport{...}; //用以表现机场
class Airplane{
public:
	virtual void fly(const Airport& destination)=0;
	...
protected:
	void defaultFly(const Airport& destination);
};


void Airplane::defaultFly(const Airport& destination){
	缺省行为,将飞机飞至指定的目的地
}



class ModelA:public Airplane{
public:
	virtual void fly(const Airport& destination){
		defaultFly(destination);
	}
	...
};

class ModelB:public Airplane{
public:
	virtual void fly(const Airport& destination){
		defaultFly(destination);
	}
	...
};

class ModelC:public Airplane{
public:
	virtual void fly(const Airport& destination);
	...
};

void ModelC::fly(const Airport& destination){
	将C型飞机飞至指定的目的地
}

class Airplane{
public:
	virtual void fly(const Airport& destination)=0;
};

void Airplane::fly(const Airport& destination){ //pure virtual函数实现
	缺省行为,将飞机飞至目的地
}

class ModelA:public Airplane{
public:
	virtual void fly(const Airport& destination){
		Airplane::fly(destination);
	}
	...
};

class Shape{
public:
	int objectID() const;
	...
};

no-virtual 函数代表的意义是不变性,所以它绝该在derived class中重新定义

考虑virtual函数以外的其他选择
class GameCharacter{
public:
	virtual int healthValue() const;//返回人物的健康指数
	...
};


//Non-Virtual Interface手法实现Template Method模式

class GameCharacter{
public:
	int healthValue() const{//我们把这个non-virtual函数称为virtual函数的外覆器
		...
		int retValue=doHealthValue();
		...
		return retValue;
	}
private:
	virtual int doHealthValue() const{
		...
	}
};

//藉由Function Pointers实现Strategy模式
class GameCharacter;//前置声明(forward declaration)
//以下函数是计算健康指数的缺省算法
int defaultHealthCalc(const GameCharacter& gc);
class GameCharacter{
public:
	typedef int (*HealthFunc)(const GameCharacter&);
	explicit GameCharacter(HealthFunc hcf=defaultHealthCalc):healthFunc(hcf){}
	int healthValue() const{
		return healthFunc(*this);
	}
private:
	HealthFunc healthFunc;
};

class EvilBadGuy:public GameCharacter{
public:
	explicit EvilBadGuy(HealthFunc )
};
