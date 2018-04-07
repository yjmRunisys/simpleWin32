#pragma once
// 创建抽象产品
// 	示例中，需要有一个汽车产品 - ICar：
//简单工厂为抽象工厂的简化，工厂定义产品类别，并根据类别生产不同的产品

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
// 	模型有了，来创建一些具体的汽车：

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
// 	要生产汽车，需要有相应的工厂：

	// factory.h
#ifndef FACTORY_H
#define FACTORY_H

//#include "concrete_product.h"

	// 工厂
class Factory
{
public:
	enum CAR_TYPE {
		BENZ_CAR,  // 奔驰汽车
		BMW_CAR,  // 宝马汽车
		AUDI_CAR  // 奥迪汽车
	};

	// 生产汽车
	ICar* CreateCar(CAR_TYPE type) {
		ICar *pCar = NULL;
		switch(type) {
		case CAR_TYPE::BENZ_CAR:
			pCar = new BenzCar();  // 奔驰汽车
			break;
		case CAR_TYPE::BMW_CAR:
			pCar = new BmwCar();  // 宝马汽车
			break;
		case CAR_TYPE::AUDI_CAR:
			pCar = new AudiCar();  // 奥迪汽车
			break;
		default:
			break;
		}
		return pCar;
	}
};

#endif // FACTORY_H

// 	这样以来，工厂就可以根据汽车类型来生产对应的汽车了。
// 	创建客户端
// 	当一切准备就绪，就可以实现客户端了：

	// main.cpp
//#include "factory.h"
//#include "product.h"
#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testSimpleFactory()
{
	// 工厂
	Factory *pFactory = new Factory();

	// 奔驰汽车
	ICar *pCar = pFactory->CreateCar(Factory::BENZ_CAR);
	cout << pCar->Name() << endl;

	SAFE_DELETE(pCar);

	// 宝马汽车
	pCar = pFactory->CreateCar(Factory::BMW_CAR);
	cout << pCar->Name() << endl;

	SAFE_DELETE(pCar);

	// 奥迪汽车
	pCar = pFactory->CreateCar(Factory::AUDI_CAR);
	cout << pCar->Name() << endl;

	SAFE_DELETE(pCar);

	getchar();

	return 0;
}

// 	输出如下：
	// 
	// 	Benz Car 
	// 	Bmw Car 
	// 	Audi Car