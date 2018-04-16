#pragma once
//装饰者模式，装饰者(Decorator)持有构件（Component),相当于装饰者扩展了构件的功能，此外Decorator继承Coponent
// 案例分析
// 
// 	星巴克（Starbucks）
// 	starbucks
// 	在星巴克购买咖啡时，可以要求在其中加入各种调味品（辅料）。
// 	调味品很多，有些不收费（例如：白砂糖、香草粉等），有些则需要额外收费（例如：奶油、摩卡、糖浆等），所以充分利用起来吧！
// 	倘若咖啡不带劲，我们想要添加奶油、摩卡和糖浆，这时，就可以利用装饰者模式思想来实现。
// 	关于星巴克，推荐两个比较火的事件：
// 	老罗星巴克奇遇记（看一次笑十次 ~O(∩_∩)O~）
// 	《致星巴克中国CEO王静瑛公开信：什么时候才不觉得中杯顾客无知或愚蠢?》
// 	代码实现
// 	创建构建
// 	首先，定义所有饮料的基类，并提供名称和价钱：

	// component.h
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

using namespace std;

// 所有饮料的基类
class IBeverage
{
public:
	virtual string Name() = 0;  // 名称
	virtual double Cost() = 0;  // 价钱
};

#endif // COMPONENT_H

// 	创建具体构建
// 	假设，有两款具体的咖啡 - 黑咖啡（属于混合咖啡）和深度烘培咖啡豆：

	// concrete_component.h
#ifndef CONCRETE_COMPONENT_H
#define CONCRETE_COMPONENT_H

//#include "component.h"

	/********** 具体的饮料（咖啡）**********/

	// 黑咖啡，属于混合咖啡
class HouseBlend : public IBeverage
{
public:
	string Name() {
		return "HouseBlend";
	}

	double Cost() {
		return 30.0;
	}
};

// 深度烘培咖啡豆
class DarkRoast : public IBeverage
{
public:
	string Name() {
		return "DarkRoast";
	}

	double Cost() {
		return 28.5;
	}
};

#endif // CONCRETE_COMPONENT_H

// 	创建装饰
// 	咖啡有了，剩下的就是添加调味品，其同样继承 IBeverage，并持有咖啡的实例：

	// decorator.h
#ifndef DECORATOR_H
#define DECORATOR_H

#include "component.h"

	// 调味品
class CondimentDecorator : public IBeverage
{
public :
	CondimentDecorator(IBeverage *beverage) : m_pBeverage(beverage) {}

	string Name() {
		return m_pBeverage->Name();
	}

	double Cost() {
		return m_pBeverage->Cost();
	}

protected :
	IBeverage *m_pBeverage;
} ;

#endif // DECORATOR_H
// 创建具体装饰
// 	添加三种收费的调味品：
		// concrete_decorator.h
#ifndef CONCRETE_DECORATOR_H
#define CONCRETE_DECORATOR_H

//#include "decorator.h"

	/********** 具体的饮料（调味品）**********/

	// 奶油
class Cream : public CondimentDecorator
{
public:
	Cream(IBeverage *beverage) : CondimentDecorator(beverage) {}

	string Name() {
		return m_pBeverage->Name() + " Cream";
	}

	double Cost() {
		return m_pBeverage->Cost() + 3.5;
	}
};

// 摩卡
class Mocha : public CondimentDecorator
{
public:
	Mocha(IBeverage *beverage) : CondimentDecorator(beverage) {}

	string Name() {
		return m_pBeverage->Name() + " Mocha";
	}

	double Cost() {
		return m_pBeverage->Cost() + 2.0;
	}
};

// 糖浆
class Syrup : public CondimentDecorator
{
public:
	Syrup(IBeverage *beverage) : CondimentDecorator(beverage) {}

	string Name() {
		return m_pBeverage->Name() + " Syrup";
	}

	double Cost() {
		return m_pBeverage->Cost() + 3.0;
	}
};

#endif // CONCRETE_DECORATOR_H

// 	创建客户端
// 	最终，我们可以为咖啡添加相应的调味品：

// main.cpp
//#include "concrete_component.h"
//#include "concrete_decorator.h"
#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testDecorator()
{
	/********** 黑咖啡 **********/
	IBeverage *pHouseBlend = new HouseBlend();
	cout << pHouseBlend->Name() << " : " << pHouseBlend->Cost() << endl;

	// 黑咖啡 + 奶油
	CondimentDecorator *pCream = new Cream(pHouseBlend);
	cout << pCream->Name() << " : " << pCream->Cost() << endl;

	// 黑咖啡 + 摩卡
	CondimentDecorator *pMocha = new Mocha(pHouseBlend);
	cout << pMocha->Name() << " : " << pMocha->Cost() << endl;

	// 黑咖啡 + 糖浆
	CondimentDecorator *pSyrup = new Syrup(pHouseBlend);
	cout << pSyrup->Name() << " : " << pSyrup->Cost() << endl;

	/********** 深度烘培咖啡豆 **********/
	IBeverage *pDarkRoast = new DarkRoast();
	cout << pDarkRoast->Name() << " : " << pDarkRoast->Cost() << endl;

	// 深度烘培咖啡豆 + 奶油
	CondimentDecorator *pCreamDR = new Cream(pDarkRoast);
	cout << pCreamDR->Name() << " : " << pCreamDR->Cost() << endl;

	// 深度烘培咖啡豆 + 奶油 + 摩卡
	CondimentDecorator *pCreamMocha = new Mocha(pCreamDR);
	cout << pCreamMocha->Name() << " : " << pCreamMocha->Cost() << endl;

	// 深度烘培咖啡豆 + 奶油 + 摩卡 + 糖浆
	CondimentDecorator *pCreamMochaSyrup = new Syrup(pCreamMocha);
	cout << pCreamMochaSyrup->Name() << " : " << pCreamMochaSyrup->Cost() << endl;

	SAFE_DELETE(pSyrup);
	SAFE_DELETE(pMocha);
	SAFE_DELETE(pCream);
	SAFE_DELETE(pHouseBlend);

	SAFE_DELETE(pCreamMochaSyrup);
	SAFE_DELETE(pCreamMocha);
	SAFE_DELETE(pCreamDR);
	SAFE_DELETE(pDarkRoast);

	getchar();

	return 0;
}

//	输出如下：

// HouseBlend : 30 
//			 HouseBlend Cream : 33.5 
//			 HouseBlend Mocha : 32 
//			 HouseBlend Syrup : 33 
// DarkRoast : 28.5 
//			DarkRoast Cream : 32 
//			DarkRoast Cream Mocha : 34 
//			DarkRoast Cream Mocha Syrup : 37
//			调味品可以随便组合，甚至同一调味品可以添加多份（例如：来 三份糖浆）或者同时添加奶、摩卡和糖浆。