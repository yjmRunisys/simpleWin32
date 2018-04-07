#pragma once
// 
//职责链模式（Chain of Responsibility Pattern）使多个对象都有机会处理请求
//从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。

// 	创建抽象处理者
// 	抽象处理者除了提供一个处理请假的接口之外，还有一个很关键的地方就是定义后继者，这样便可以构建一条链：

//为对象设置后继处理

	// handler.h
#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>

// 抽象处理者
class IHandler
{
public:
	IHandler() 
	{ 
		m_pSuccessor = NULL; 
	}
	virtual ~IHandler() {}
	void SetSuccessor(IHandler *successor) 
	{ 
		m_pSuccessor = successor; 
	}
	virtual void HandleRequest(float days) = 0;

protected:
	IHandler *m_pSuccessor;  // 后继者
};

#endif // HANDLER_H

// 	创建具体处理者
// 	具体处理者包含 Manager、Director、CEO，它们的实现基本相同，只是批准的天数不一样：

	// concrete_handler.h
#ifndef CONCRETE_HANDLER_H
#define CONCRETE_HANDLER_H

//#include "handler.h"

	// 经理
class Manager : public IHandler
{
public:
	Manager() {}
	~Manager() {}
	virtual void HandleRequest(float days) override 
	{
		if (days <= 1) {
			std::cout << "Manager 批准了 " << days << " 天假" << std::endl;
		} else {
			m_pSuccessor->HandleRequest(days);
		}
	}
};

// 总监
class Director : public IHandler
{
public:
	Director() {}
	~Director() {}
	virtual void HandleRequest(float days) override 
	{
		if (days <= 3) 
		{
			std::cout << "Director 批准了 " << days << " 天假" << std::endl;
		} else {
			m_pSuccessor->HandleRequest(days);
		}
	}
};

// 总裁
class CEO : public IHandler
{
public:
	CEO() {}
	~CEO() {}
	virtual void HandleRequest(float days) override 
	{
		if (days <= 7) {
			std::cout << "CEO 批准了 " << days << " 天假" << std::endl;
		} else 
		{
			std::cout << "给你放长假，以后不用来上班啦！" << std::endl;
		}
	}
};

#endif // CONCRETE_HANDLER_H

// 	注意： 由于 CEO 位于最高层（处于链的末尾），所以请求到此结束，不会继续向下传递。
// 	创建客户端
// 	开始请假，说出你的理由：

	// main.cpp
//#include "concrete_handler.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testChainResponsibility()
{
	IHandler *manager = new Manager();
	IHandler *director = new Director();
	IHandler *ceo = new CEO();

	// 职责链：经理 -> 总监 -> 总裁
	manager->SetSuccessor(director);
	director->SetSuccessor(ceo);

	manager->HandleRequest(1);
	manager->HandleRequest(2);
	manager->HandleRequest(5);
	manager->HandleRequest(10);

	SAFE_DELETE(manager);
	SAFE_DELETE(director);
	SAFE_DELETE(ceo);

	getchar();

	return 0;
}

// 	输出如下：

// 	Manager 批准了 1 天假 
// 	Director 批准了 2 天假 
//	CEO 批准了 5 天假 
//	给你放长假，以后不用来上班啦！