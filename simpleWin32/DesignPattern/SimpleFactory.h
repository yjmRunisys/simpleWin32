#pragma once
// ���������Ʒ
// 	ʾ���У���Ҫ��һ��������Ʒ - ICar��
//�򵥹���Ϊ���󹤳��ļ򻯣����������Ʒ��𣬲��������������ͬ�Ĳ�Ʒ

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

#endif // PRODUCT_H

// 	���������Ʒ
// 	ģ�����ˣ�������һЩ�����������

	// concrete_product.h
#ifndef CONCRETE_PRODUCT_H
#define CONCRETE_PRODUCT_H

//#include "product.h"

	// ��������
class BenzCar : public ICar
{
public:
	string Name() {
		return "Benz Car";
	}
};

// ��������
class BmwCar : public ICar
{
public:
	string Name() {
		return "Bmw Car";
	}
};

// �µ�����
class AudiCar : public ICar
{
public:
	string Name() {
		return "Audi Car";
	}
};

#endif // CONCRETE_PRODUCT_H

// 	��������
// 	Ҫ������������Ҫ����Ӧ�Ĺ�����

	// factory.h
#ifndef FACTORY_H
#define FACTORY_H

//#include "concrete_product.h"

	// ����
class Factory
{
public:
	enum CAR_TYPE {
		BENZ_CAR,  // ��������
		BMW_CAR,  // ��������
		AUDI_CAR  // �µ�����
	};

	// ��������
	ICar* CreateCar(CAR_TYPE type) {
		ICar *pCar = NULL;
		switch(type) {
		case CAR_TYPE::BENZ_CAR:
			pCar = new BenzCar();  // ��������
			break;
		case CAR_TYPE::BMW_CAR:
			pCar = new BmwCar();  // ��������
			break;
		case CAR_TYPE::AUDI_CAR:
			pCar = new AudiCar();  // �µ�����
			break;
		default:
			break;
		}
		return pCar;
	}
};

#endif // FACTORY_H

// 	���������������Ϳ��Ը�������������������Ӧ�������ˡ�
// 	�����ͻ���
// 	��һ��׼���������Ϳ���ʵ�ֿͻ����ˣ�

	// main.cpp
//#include "factory.h"
//#include "product.h"
#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testSimpleFactory()
{
	// ����
	Factory *pFactory = new Factory();

	// ��������
	ICar *pCar = pFactory->CreateCar(Factory::BENZ_CAR);
	cout << pCar->Name() << endl;

	SAFE_DELETE(pCar);

	// ��������
	pCar = pFactory->CreateCar(Factory::BMW_CAR);
	cout << pCar->Name() << endl;

	SAFE_DELETE(pCar);

	// �µ�����
	pCar = pFactory->CreateCar(Factory::AUDI_CAR);
	cout << pCar->Name() << endl;

	SAFE_DELETE(pCar);

	getchar();

	return 0;
}

// 	������£�
	// 
	// 	Benz Car 
	// 	Bmw Car 
	// 	Audi Car