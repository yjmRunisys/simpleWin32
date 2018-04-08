#pragma once

//���󹤳����幹����幤�������ݹ�����𣩣����幤���̳��ڳ��󹤳����ɲ�����Ӧ�Ĳ�Ʒ
// ���������Ʒ
// 	�����ǵ�ʾ���У���Ҫ��������Ʒ - ���������г���

	// product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

// �����ӿ�
class ICar
{
public:
	virtual string Name() = 0;  // ��������
};

// ���г��ӿ�
class IBike
{
public:
	virtual string Name() = 0;  // ���г�����
};

#endif // PRODUCT_H

// 	���������Ʒ
// 	���˳����Ʒ����������һЩ����Ĳ�Ʒ��

	// concrete_product.h
#ifndef CONCRETE_PRODUCT_H
#define CONCRETE_PRODUCT_H

//#include "product.h"

	/********** ���� **********/
	// ����
class BenzCar : public ICar
{
public:
	string Name() {
		return "Benz Car";
	}
};

// ����
class BmwCar : public ICar
{
public:
	string Name() {
		return "Bmw Car";
	}
};

// �µ�
class AudiCar : public ICar
{
public:
	std::string Name() {
		return "Audi Car";
	}
};

/********** ���г� **********/
// ����
class BenzBike : public IBike
{
public:
	string Name() {
		return "Benz Bike";
	}
};

// ����
class BmwBike : public IBike
{
public:
	string Name() {
		return "Bmw Bike";
	}
};

// �µ�
class AudiBike : public IBike
{
public:
	string Name() {
		return "Audi Bike";
	}
};

#endif // CONCRETE_PRODUCT_H

// 	������Ϊ���������г���׼���������еľ����ࡣ
// 	�������󹤳�
// 	��Ʒ���ˣ���ȻҪ����Ӧ������������������������أ�Ҫ�о���Ĺ�����������֮ǰ����Ҫһ�����󹤳���

	// factory.h
#ifndef FACTORY_H
#define FACTORY_H

//#include "product.h"

	// ���󹤳�
class AFactory
{
public:
	enum FACTORY_TYPE {
		BENZ_FACTORY,  // ���۹���
		BMW_FACTORY,  // ������
		AUDI_FACTORY  // �µϹ���
	};

	virtual ICar* CreateCar() = 0;  // ��������
	virtual IBike* CreateBike() = 0;    // �������г�
	static AFactory* CreateFactory(FACTORY_TYPE factory)  // ��������
	{
		AFactory *pFactory = NULL;
		switch (factory) {
		case FACTORY_TYPE::BENZ_FACTORY:  // ���۹���
			pFactory = new BenzFactory();
			break;
		case FACTORY_TYPE::BMW_FACTORY:  // ������
			pFactory = new BmwFactory();
			break;
		case FACTORY_TYPE::AUDI_FACTORY:  // �µϹ���
			pFactory = new AudiFactory();
			break;
		default:
			break;
		}
		return pFactory;
	}
};

#endif // FACTORY_H


// 	�������幤��
// 	Ϊÿ�������̴�������Ĺ�����

	// concrete_factory.h
#ifndef CONCRETE_FACTORY_H
#define CONCRETE_FACTORY_H

//#include "factory.h"
//#include "concrete_product.h"

	// ���۹���
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

// ������
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

// �µϹ���
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

// 	��������������Ĳ�Ʒ�����������̹��������ˡ�
// 	�����ͻ���
// 	��һ��׼���������Ϳ���ʵ�ֿͻ����ˣ�������ز�Ʒ�����ֲ�νṹ��������Ʒ��

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
	// ����
	AFactory *pFactory = AFactory::CreateFactory(AFactory::FACTORY_TYPE::BENZ_FACTORY);
	ICar *pCar = pFactory->CreateCar();
	IBike *pBike = pFactory->CreateBike();

	cout << "Benz factory - Car: " << pCar->Name() << endl;
	cout << "Benz factory - Bike: " << pBike->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pBike);
	SAFE_DELETE(pFactory);

	// ����
	pFactory = AFactory::CreateFactory(AFactory::FACTORY_TYPE::BMW_FACTORY);
	pCar = pFactory->CreateCar();
	pBike = pFactory->CreateBike();
	cout << "Bmw factory - Car: " << pCar->Name() << endl;
	cout << "Bmw factory - Bike: " << pBike->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pBike);
	SAFE_DELETE(pFactory);

	// �µ�
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

// 	������£�
	// 
	// 	Benz factory - Car: Benz Car 
	// 	Benz factory - Bike: Benz Bike 
	// 	Bmw factory - Car: Bmw Car 
	// 	Bmw factory - Bike: Bmw Bike 
	// 	Audi factory - Car: Audi Car 
	// 	Audi factory - Bike: Audi Bike
	// 	��������󹤳�ģʽ�Ļ�������Ѿ����ˣ����ǽ�����˾����Ʒ�����֣���ʵ�����԰����������Ϣ���������Ҫ������չ��