#pragma once

//�򵥹�������չ��ֱ�ӹ��칤�����࣬ÿ��������������Ĳ�Ʒ��������չ

// ����ģʽ�����ͼ򵥹���ģʽ��࣬�򵥹���ģʽ - �ڲ�Ʒ�������ʱ����Ҫ���һ���жϷ�֧����Υ���˿���-���ԭ��
// 	��ˣ�����ģʽ����Ϊ�˽���������������ġ�
// 
// 	BMW
// 	���ԣ����� �򵥹���ģʽ һ���е� BBA ��˵��Ҫ�ֱ��ɶ�Ӧ�Ĺ�����������
// 
// 	����ʵ��
// 	���������Ʒ
// 	�����ǵ�ʾ���У���Ҫ��һ��������Ʒ - ICar��

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
// 	���˳����Ʒ������Ϊ�䴴��һЩ����Ĳ�Ʒ��

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
// 	��Ʒ���ˣ���ȻҪ����Ӧ�Ĺ�����������������֮ǰ����Ҫһ�����󹤳���

	// factory.h
#ifndef FACTORY_H
#define FACTORY_H

//#include "product.h"

	// �����ӿ�
class AFactory
{
public:
	virtual ICar* CreateCar() = 0;  // ��������
};

#endif // FACTORY_H

// 	�������幤��
// 	Ϊÿ�������̴�����Ӧ�ĵĹ�����

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
};

// ������
class BmwFactory : public AFactory
{
public:
	ICar* CreateCar() {
		return new BmwCar();
	}
};

// �µϹ���
class AudiFactory : public AFactory
{
public:
	ICar* CreateCar() {
		return new AudiCar();
	}
};

#endif // CONCRETE_FACTORY_H
// 	����������ÿ������ֻ���������Լ��Ĳ�Ʒ��
// 	�����ͻ���
// 	��һ��׼���������Ϳ���ʵ�ֿͻ����ˣ�

	// main.cpp
//#include "concrete_factory.h"
//#include "product.h"
#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testFactoryMethod()
{
	// ����
	AFactory *pFactory = new BenzFactory();
	ICar *pCar = pFactory->CreateCar();
	cout << "Benz factory: " << pCar->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pFactory);

	// ����
	pFactory = new BmwFactory();
	pCar = pFactory->CreateCar();
	cout << "Bmw factory: " << pCar->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pFactory);

	// �µ�
	pFactory = new AudiFactory();
	pCar = pFactory->CreateCar();
	cout << "Audi factory: " << pCar->Name() << endl;

	SAFE_DELETE(pCar);
	SAFE_DELETE(pFactory);

	getchar();

	return 0;
}

// 	������£�
	// 
	// 	Benz factory: Benz Car 
	// 	Bmw factory: Bmw Car 
	// 	Audi factory: Audi Car