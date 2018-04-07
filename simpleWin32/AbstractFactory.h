#pragma once

//抽象工厂定义构造具体工厂（根据工厂类别），具体工厂继承于抽象工厂，可产生相应的产品
// 创建抽象产品
// 	在我们的示例中，需要有两个产品 - 汽车和自行车：

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

// 自行车接口
class IBike
{
public:
	virtual string Name() = 0;  // 自行车名称
};

#endif // PRODUCT_H

// 	创建具体产品
// 	有了抽象产品，继续创建一些具体的产品：

	// concrete_product.h
#ifndef CONCRETE_PRODUCT_H
#define CONCRETE_PRODUCT_H

//#include "product.h"

	/********** 汽车 **********/
	// 奔驰
class BenzCar : public ICar
{
public:
	string Name() {
		return "Benz Car";
	}
};

// 宝马
class BmwCar : public ICar
{
public:
	string Name() {
		return "Bmw Car";
	}
};

// 奥迪
class AudiCar : public ICar
{
public:
	std::string Name() {
		return "Audi Car";
	}
};

/********** 自行车 **********/
// 奔驰
class BenzBike : public IBike
{
public:
	string Name() {
		return "Benz Bike";
	}
};

// 宝马
class BmwBike : public IBike
{
public:
	string Name() {
		return "Bmw Bike";
	}
};

// 奥迪
class AudiBike : public IBike
{
public:
	string Name() {
		return "Audi Bike";
	}
};

#endif // CONCRETE_PRODUCT_H

// 	这样，为汽车和自行车都准备好了所有的具体类。
// 	创建抽象工厂
// 	产品有了，当然要有相应的制造商与其相关联，所以呢，要有具体的工厂。但在这之前，需要一个抽象工厂：

	// factory.h
#ifndef FACTORY_H
#define FACTORY_H

//#include "product.h"

	// 抽象工厂
class AFactory
{
public:
	enum FACTORY_TYPE {
		BENZ_FACTORY,  // 奔驰工厂
		BMW_FACTORY,  // 宝马工厂
		AUDI_FACTORY  // 奥迪工厂
	};

	virtual ICar* CreateCar() = 0;  // 生产汽车
	virtual IBike* CreateBike() = 0;    // 生产自行车
	static AFactory* CreateFactory(FACTORY_TYPE factory)  // 创建工厂
	{
		AFactory *pFactory = NULL;
		switch (factory) {
		case FACTORY_TYPE::BENZ_FACTORY:  // 奔驰工厂
			pFactory = new BenzFactory();
			break;
		case FACTORY_TYPE::BMW_FACTORY:  // 宝马工厂
			pFactory = new BmwFactory();
			break;
		case FACTORY_TYPE::AUDI_FACTORY:  // 奥迪工厂
			pFactory = new AudiFactory();
			break;
		default:
			break;
		}
		return pFactory;
	}
};

#endif // FACTORY_H


// 	创建具体工厂
// 	为每个制造商创建具体的工厂：

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

	IBike* CreateBike() {
		return new BenzBike();
	}
};

// 宝马工厂
class BmwFactory : public AFactory
{
public:
	ICar* CreateCar() {
		return new BmwCar();
	}

	IBike* CreateBike() {
		return new BmwBike();
	}
};

// 奥迪工厂
class AudiFactory : public AFactory
{
public:
	ICar* CreateCar() {
		return new AudiCar();
	}

	IBike* CreateBike() {
		return new AudiBike();
	}
};

#endif // CONCRETE_FACTORY_H

// 	这样以来，具体的产品就与其制造商关联起来了。
// 	创建客户端
// 	当一切准备就绪，就可以实现客户端了，利用相关产品的这种层次结构来创建产品。

	// main.cpp
//#include "factory.h"
//#include "product.h"
#include <iostream>

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testAbstractFactory()
{
	// 奔驰
	AFactory *pFactory = AFactory::CreateFactory(AFactory::FACTORY_TYPE::BENZ_FACTORY);
	ICar *pCar = pFactory->CreateCar();
	IBike *pBike = pFactory->CreateBike();

	cout << "Benz factory - Car: " << pCar->Name() << endl;
	cout << "Benz factory - Bike: " << pBike->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pBike);
	SAFE_DELETE(pFactory);

	// 宝马
	pFactory = AFactory::CreateFactory(AFactory::FACTORY_TYPE::BMW_FACTORY);
	pCar = pFactory->CreateCar();
	pBike = pFactory->CreateBike();
	cout << "Bmw factory - Car: " << pCar->Name() << endl;
	cout << "Bmw factory - Bike: " << pBike->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pBike);
	SAFE_DELETE(pFactory);

	// 奥迪
	pFactory = AFactory::CreateFactory(AFactory::FACTORY_TYPE::AUDI_FACTORY);
	pCar = pFactory->CreateCar();
	pBike = pFactory->CreateBike();
	cout << "Audi factory - Car: " << pCar->Name() << endl;
	cout << "Audi factory - Bike: " << pBike->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pBike);
	SAFE_DELETE(pFactory);

	getchar();

	return 0;
}

// 	输出如下：
	// 
	// 	Benz factory - Car: Benz Car 
	// 	Benz factory - Bike: Benz Bike 
	// 	Bmw factory - Car: Bmw Car 
	// 	Bmw factory - Bike: Bmw Bike 
	// 	Audi factory - Car: Audi Car 
	// 	Audi factory - Bike: Audi Bike
	// 	到这里，抽象工厂模式的基本框架已经有了，我们仅输出了具体产品的名字，其实还可以包含更多的信息，请根据需要自行扩展。