#pragma once

//简单工厂的拓展，直接构造工厂子类，每个工厂生产具体的产品，便于拓展

// 工厂模式基本和简单工厂模式差不多，简单工厂模式 - 在产品子类添加时，需要添加一个判断分支，这违背了开放-封闭原则。
// 	因此，工厂模式就是为了解决这个问题而产生的。
// 
// 	BMW
// 	所以，对于 简单工厂模式 一节中的 BBA 来说，要分别由对应的工厂来生产。
// 
// 	代码实现
// 	创建抽象产品
// 	在我们的示例中，需要有一个汽车产品 - ICar：

	// product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

// 汽车接口
class ICar
{
public:
	virtual string Name() = 0;  // 汽车名称
};

#endif // PRODUCT_H

// 	创建具体产品
// 	有了抽象产品，继续为其创建一些具体的产品：

	// concrete_product.h
#ifndef CONCRETE_PRODUCT_H
#define CONCRETE_PRODUCT_H

//#include "product.h"

	// 奔驰汽车
class BenzCar : public ICar
{
public:
	string Name() {
		return "Benz Car";
	}
};

// 宝马汽车
class BmwCar : public ICar
{
public:
	string Name() {
		return "Bmw Car";
	}
};

// 奥迪汽车
class AudiCar : public ICar
{
public:
	string Name() {
		return "Audi Car";
	}
};

#endif // CONCRETE_PRODUCT_H

// 	创建工厂
// 	产品有了，当然要有相应的工厂来生产，但在这之前，需要一个抽象工厂：

	// factory.h
#ifndef FACTORY_H
#define FACTORY_H

//#include "product.h"

	// 工厂接口
class AFactory
{
public:
	virtual ICar* CreateCar() = 0;  // 生产汽车
};

#endif // FACTORY_H

// 	创建具体工厂
// 	为每个制造商创建对应的的工厂：

	// concrete_factory.h
#ifndef CONCRETE_FACTORY_H
#define CONCRETE_FACTORY_H

//#include "factory.h"
//#include "concrete_product.h"

	// 奔驰工厂
class BenzFactory : public AFactory
{
public:
	ICar* CreateCar() {
		return new BenzCar();
	}
};

// 宝马工厂
class BmwFactory : public AFactory
{
public:
	ICar* CreateCar() {
		return new BmwCar();
	}
};

// 奥迪工厂
class AudiFactory : public AFactory
{
public:
	ICar* CreateCar() {
		return new AudiCar();
	}
};

#endif // CONCRETE_FACTORY_H
// 	这样以来，每个工厂只负责生产自己的产品。
// 	创建客户端
// 	当一切准备就绪，就可以实现客户端了：

	// main.cpp
//#include "concrete_factory.h"
//#include "product.h"
#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testFactoryMethod()
{
	// 奔驰
	AFactory *pFactory = new BenzFactory();
	ICar *pCar = pFactory->CreateCar();
	cout << "Benz factory: " << pCar->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pFactory);

	// 宝马
	pFactory = new BmwFactory();
	pCar = pFactory->CreateCar();
	cout << "Bmw factory: " << pCar->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pFactory);

	// 奥迪
	pFactory = new AudiFactory();
	pCar = pFactory->CreateCar();
	cout << "Audi factory: " << pCar->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pFactory);

	getchar();

	return 0;
}

// 	输出如下：
	// 
	// 	Benz factory: Benz Car 
	// 	Bmw factory: Bmw Car 
	// 	Audi factory: Audi Car