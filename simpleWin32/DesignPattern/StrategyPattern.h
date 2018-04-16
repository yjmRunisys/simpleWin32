#pragma once
// 代码实现
// 	创建抽象策略 
// 	抽象策略由 IStrategy 表示，它提供了一个 Travel() 接口，用于提供出行方式：

// strategy.h
#ifndef STRATEGY_H
#define STRATEGY_H

	// 出行策略
class IStrategy
{
public:
	virtual void Travel() = 0;
};

#endif // STRATEGY_H

// 	创建具体策略
// 
// 	有三种具体的策略可供选择，骑自行车、开车、坐火车：

	// concrete_strategy.h
#ifndef CONCRETE_STRATEGY_H
#define CONCRETE_STRATEGY_H

//#include "strategy.h"
#include <iostream>

	// 骑自行车
class BikeStrategy : public IStrategy
{
public:
	virtual void Travel() override { std::cout << "Travel by bike" << std::endl; }
};

// 开车
class CarStrategy : public IStrategy
{
public:
	virtual void Travel() override { std::cout << "Travel by car" << std::endl; }
};

// 坐火车
class TrainStrategy : public IStrategy
{
public:
	virtual void Travel() override { std::cout << "Travel by train" << std::endl; }
};

#endif // CONCRETE_STRATEGY_H

// 	创建环境角色
// 	环境角色对外提供了一个 Travel() 接口，最终由客户端调用。在内部，它最终调用的是 IStrategy 的相应方法：

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

// 	创建客户端
// 
// 	旅程开始，尽情享受吧：

	// main.cpp
//#include "context.h"
//#include "concrete_strategy.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testStrategy()
{
	// 策略之间可以相互替换
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