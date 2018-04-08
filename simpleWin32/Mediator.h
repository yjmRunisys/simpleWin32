#pragma once
// 代码实现
// 
// 	创建抽象中介者
// 	由于中介需要和所有参与者打交道，所以它除了注册参与者之外，还需要将发送者的消息传递出去：
//中介维护消息接收者与发送者链表，具有注册参与者、消息分发

	// mediator.h
#pragma once

//#include "colleague.h"
#include <list>

class IColleague;

// 抽象中介者
class IMediator
{
public:
	// 注册参与者
	virtual void registerColleague(IColleague* colleague) 
	{ 
		m_colleagues.emplace_back(colleague); 
	}
	const std::list<IColleague*>& getColleagues() const 
	{ 
		return
			m_colleagues; 
	}

	// 将发送者的消息发送给所有参与者
	virtual void distributeMessage(const IColleague* sender, const std::string& message) const = 0;

private:
	std::list<IColleague*> m_colleagues;
};

// 	创建具体中介者
// 	具体中介者的职责是遍历所有的参与者，将发送者的消息通知到每一个人：

	// concrete_mediator.h
#ifndef CONCRETE_MEDIATOR_H
#define CONCRETE_MEDIATOR_H

//#include "mediator.h"

	// 具体中介者
class ConcreteMediator : public IMediator
{
public:
	// 将发送者的消息发送给所有参与者（但不包括发送者自己）
	virtual void distributeMessage(const IColleague* sender, const std::string& message) const override 
	{
		for (const IColleague* c : getColleagues())
			if (c != sender)  // 不要将消息发送给自己
				c->receiveMessage(sender, message);
	}
};

#endif // CONCRETE_MEDIATOR_H

// 	注意： 这里需要添加限制 c != sender，防止将消息回传给发送者自己。
// 	创建抽象同事
// 	由于房东和租客均由同事类表示，所以既需要（房东）发送消息，又需要（租客）接收消息：

	// colleague.h
#pragma once

//#include "mediator.h"
#include <string>

class IMediator;

// 抽象同事类
class IColleague
{
public:
	IColleague(const std::string& name) : m_strName (name) 
	{}
	std::string getName() const 
	{
		return m_strName; 
	}

	// 通过中介者，将自己的消息发布出去
	virtual void sendMessage(const IMediator& mediator, const std::string& message) const = 0;
	// 接收来自发送者的消息
	virtual void receiveMessage(const IColleague* sender, const std::string& message) const = 0;

private:
	std::string m_strName;
};

// 	创建具体同事
// 	在内部，具体的消息发送由中介者完成：

	// concrete_colleague.h
#ifndef CONCRETE_COLLEAGUE_H
#define CONCRETE_COLLEAGUE_H

//#include "colleague.h"
#include <iostream>

	// 具体同事类
class ConcreteColleague : public IColleague
{
public:
	using IColleague::IColleague;

	// 通过中介者，将自己的消息发布出去
	virtual void sendMessage(const IMediator& mediator, const std::string& message) const override 
	{
		mediator.distributeMessage(this, message);
	}

private:
	// 接收来自发送者的消息
	virtual void receiveMessage(const IColleague* sender, const std::string& message) const override 
	{
		std::cout << getName() << " received the message from "
			<< sender->getName() << ": " << message << std::endl;
	}
};

#endif // CONCRETE_COLLEAGUE_H

// 	创建客户端
// 	找房啦！一旦房东将房子挂出去，中介便会通知所有需要租房的人：

	// main.cpp
//#include "concrete_colleague.h"
//#include "concrete_mediator.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testMediator()
{
	// 房东
	IColleague *landlord = new ConcreteColleague("Tom");

	// 租客
	IColleague *jerry = new ConcreteColleague("Jerry");
	IColleague *tuffy = new ConcreteColleague("Tuffy");

	// 中介者 - 添加租客
	ConcreteMediator mediator;
	mediator.registerColleague(jerry);
	mediator.registerColleague(tuffy);

	// 房东通过中介将消息发送出去
	landlord->sendMessage(mediator, "Xi'erqi, two bedroom house, 6000/month.");

	SAFE_DELETE(jerry);
	SAFE_DELETE(tuffy);

	getchar();

	return 0;
}

// 	输出如下：
// 	Jerry received the message from Tom: Xi’erqi, two bedroom house, 6000/month. 
//	Tuffy received the message from Tom: Xi’erqi, two bedroom house, 6000/month.