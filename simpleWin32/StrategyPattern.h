#pragma once
// ����ʵ��
// 	����������� 
// 	��������� IStrategy ��ʾ�����ṩ��һ�� Travel() �ӿڣ������ṩ���з�ʽ��

// strategy.h
#ifndef STRATEGY_H
#define STRATEGY_H

	// ���в���
class IStrategy
{
public:
	virtual void Travel() = 0;
};

#endif // STRATEGY_H

// 	�����������
// 
// 	�����־���Ĳ��Կɹ�ѡ�������г������������𳵣�

	// concrete_strategy.h
#ifndef CONCRETE_STRATEGY_H
#define CONCRETE_STRATEGY_H

//#include "strategy.h"
#include <iostream>

	// �����г�
class BikeStrategy : public IStrategy
{
public:
	virtual void Travel() override { std::cout << "Travel by bike" << std::endl; }
};

// ����
class CarStrategy : public IStrategy
{
public:
	virtual void Travel() override { std::cout << "Travel by car" << std::endl; }
};

// ����
class TrainStrategy : public IStrategy
{
public:
	virtual void Travel() override { std::cout << "Travel by train" << std::endl; }
};

#endif // CONCRETE_STRATEGY_H

// 	����������ɫ
// 	������ɫ�����ṩ��һ�� Travel() �ӿڣ������ɿͻ��˵��á����ڲ��������յ��õ��� IStrategy ����Ӧ������

	// context.h/
#ifndef CONTEXT_H
#define CONTEXT_H

//#include "strategy.h"

class Context
{
public:
	Context(IStrategy *strategy) { m_pStrategy = strategy; }
	void Travel() { m_pStrategy->Travel(); }

private:
	IStrategy *m_pStrategy;
};

#endif // CONTEXT_H

// 	�����ͻ���
// 
// 	�ó̿�ʼ���������ܰɣ�

	// main.cpp
//#include "context.h"
//#include "concrete_strategy.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testStrategy()
{
	// ����֮������໥�滻
	IStrategy *bike = new BikeStrategy();
	IStrategy *car = new CarStrategy();
	IStrategy *train = new TrainStrategy();

	Context *bikeContext = new Context(bike);
	Context *carContext = new Context(car);
	Context *trainContext = new Context(train);

	bikeContext->Travel();
	carContext->Travel();
	trainContext->Travel();

	SAFE_DELETE(bike);
	SAFE_DELETE(car);
	SAFE_DELETE(train);

	SAFE_DELETE(bikeContext);
	SAFE_DELETE(carContext);
	SAFE_DELETE(trainContext);

	getchar();

	return 0;
}