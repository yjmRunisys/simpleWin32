#pragma once
//װ����ģʽ��װ����(Decorator)���й�����Component),�൱��װ������չ�˹����Ĺ��ܣ�����Decorator�̳�Coponent
// ��������
// 
// 	�ǰͿˣ�Starbucks��
// 	starbucks
// 	���ǰͿ˹��򿧷�ʱ������Ҫ�������м�����ֵ�ζƷ�����ϣ���
// 	��ζƷ�ܶ࣬��Щ���շѣ����磺��ɰ�ǡ���ݷ۵ȣ�����Щ����Ҫ�����շѣ����磺���͡�Ħ�����ǽ��ȣ������Գ�����������ɣ�
// 	�������Ȳ�������������Ҫ������͡�Ħ�����ǽ�����ʱ���Ϳ�������װ����ģʽ˼����ʵ�֡�
// 	�����ǰͿˣ��Ƽ������Ƚϻ���¼���
// 	�����ǰͿ������ǣ���һ��Цʮ�� ~O(��_��)O~��
// 	�����ǰͿ��й�CEO�����������ţ�ʲôʱ��Ų������б��˿���֪���޴�?��
// 	����ʵ��
// 	��������
// 	���ȣ������������ϵĻ��࣬���ṩ���ƺͼ�Ǯ��

	// component.h
#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

using namespace std;

// �������ϵĻ���
class IBeverage
{
public:
	virtual string Name() = 0;  // ����
	virtual double Cost() = 0;  // ��Ǯ
};

#endif // COMPONENT_H

// 	�������幹��
// 	���裬���������Ŀ��� - �ڿ��ȣ����ڻ�Ͽ��ȣ�����Ⱥ��࿧�ȶ���

	// concrete_component.h
#ifndef CONCRETE_COMPONENT_H
#define CONCRETE_COMPONENT_H

//#include "component.h"

	/********** ��������ϣ����ȣ�**********/

	// �ڿ��ȣ����ڻ�Ͽ���
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

// ��Ⱥ��࿧�ȶ�
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

// 	����װ��
// 	�������ˣ�ʣ�µľ�����ӵ�ζƷ����ͬ���̳� IBeverage�������п��ȵ�ʵ����

	// decorator.h
#ifndef DECORATOR_H
#define DECORATOR_H

#include "component.h"

	// ��ζƷ
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
// ��������װ��
// 	��������շѵĵ�ζƷ��
		// concrete_decorator.h
#ifndef CONCRETE_DECORATOR_H
#define CONCRETE_DECORATOR_H

//#include "decorator.h"

	/********** ��������ϣ���ζƷ��**********/

	// ����
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

// Ħ��
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

// �ǽ�
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

// 	�����ͻ���
// 	���գ����ǿ���Ϊ���������Ӧ�ĵ�ζƷ��

// main.cpp
//#include "concrete_component.h"
//#include "concrete_decorator.h"
#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testDecorator()
{
	/********** �ڿ��� **********/
	IBeverage *pHouseBlend = new HouseBlend();
	cout << pHouseBlend->Name() << " : " << pHouseBlend->Cost() << endl;

	// �ڿ��� + ����
	CondimentDecorator *pCream = new Cream(pHouseBlend);
	cout << pCream->Name() << " : " << pCream->Cost() << endl;

	// �ڿ��� + Ħ��
	CondimentDecorator *pMocha = new Mocha(pHouseBlend);
	cout << pMocha->Name() << " : " << pMocha->Cost() << endl;

	// �ڿ��� + �ǽ�
	CondimentDecorator *pSyrup = new Syrup(pHouseBlend);
	cout << pSyrup->Name() << " : " << pSyrup->Cost() << endl;

	/********** ��Ⱥ��࿧�ȶ� **********/
	IBeverage *pDarkRoast = new DarkRoast();
	cout << pDarkRoast->Name() << " : " << pDarkRoast->Cost() << endl;

	// ��Ⱥ��࿧�ȶ� + ����
	CondimentDecorator *pCreamDR = new Cream(pDarkRoast);
	cout << pCreamDR->Name() << " : " << pCreamDR->Cost() << endl;

	// ��Ⱥ��࿧�ȶ� + ���� + Ħ��
	CondimentDecorator *pCreamMocha = new Mocha(pCreamDR);
	cout << pCreamMocha->Name() << " : " << pCreamMocha->Cost() << endl;

	// ��Ⱥ��࿧�ȶ� + ���� + Ħ�� + �ǽ�
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

//	������£�

// HouseBlend : 30 
//			 HouseBlend Cream : 33.5 
//			 HouseBlend Mocha : 32 
//			 HouseBlend Syrup : 33 
// DarkRoast : 28.5 
//			DarkRoast Cream : 32 
//			DarkRoast Cream Mocha : 34 
//			DarkRoast Cream Mocha Syrup : 37
//			��ζƷ���������ϣ�����ͬһ��ζƷ������Ӷ�ݣ����磺�� �����ǽ�������ͬʱ����̡�Ħ�����ǽ���