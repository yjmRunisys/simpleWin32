#pragma once
// ����ʵ��
// 
// 	���������н���
// 	�����н���Ҫ�����в����ߴ򽻵�������������ע�������֮�⣬����Ҫ�������ߵ���Ϣ���ݳ�ȥ��
//�н�ά����Ϣ�������뷢������������ע������ߡ���Ϣ�ַ�

	// mediator.h
#pragma once

//#include "colleague.h"
#include <list>

class IColleague;

// �����н���
class IMediator
{
public:
	// ע�������
	virtual void registerColleague(IColleague* colleague) 
	{ 
		m_colleagues.emplace_back(colleague); 
	}
	const std::list<IColleague*>& getColleagues() const 
	{ 
		return
			m_colleagues; 
	}

	// �������ߵ���Ϣ���͸����в�����
	virtual void distributeMessage(const IColleague* sender, const std::string& message) const = 0;

private:
	std::list<IColleague*> m_colleagues;
};

// 	���������н���
// 	�����н��ߵ�ְ���Ǳ������еĲ����ߣ��������ߵ���Ϣ֪ͨ��ÿһ���ˣ�

	// concrete_mediator.h
#ifndef CONCRETE_MEDIATOR_H
#define CONCRETE_MEDIATOR_H

//#include "mediator.h"

	// �����н���
class ConcreteMediator : public IMediator
{
public:
	// �������ߵ���Ϣ���͸����в����ߣ����������������Լ���
	virtual void distributeMessage(const IColleague* sender, const std::string& message) const override 
	{
		for (const IColleague* c : getColleagues())
			if (c != sender)  // ��Ҫ����Ϣ���͸��Լ�
				c->receiveMessage(sender, message);
	}
};

#endif // CONCRETE_MEDIATOR_H

// 	ע�⣺ ������Ҫ������� c != sender����ֹ����Ϣ�ش����������Լ���
// 	��������ͬ��
// 	���ڷ�������;���ͬ�����ʾ�����Լ���Ҫ��������������Ϣ������Ҫ����ͣ�������Ϣ��

	// colleague.h
#pragma once

//#include "mediator.h"
#include <string>

class IMediator;

// ����ͬ����
class IColleague
{
public:
	IColleague(const std::string& name) : m_strName (name) 
	{}
	std::string getName() const 
	{
		return m_strName; 
	}

	// ͨ���н��ߣ����Լ�����Ϣ������ȥ
	virtual void sendMessage(const IMediator& mediator, const std::string& message) const = 0;
	// �������Է����ߵ���Ϣ
	virtual void receiveMessage(const IColleague* sender, const std::string& message) const = 0;

private:
	std::string m_strName;
};

// 	��������ͬ��
// 	���ڲ����������Ϣ�������н�����ɣ�

	// concrete_colleague.h
#ifndef CONCRETE_COLLEAGUE_H
#define CONCRETE_COLLEAGUE_H

//#include "colleague.h"
#include <iostream>

	// ����ͬ����
class ConcreteColleague : public IColleague
{
public:
	using IColleague::IColleague;

	// ͨ���н��ߣ����Լ�����Ϣ������ȥ
	virtual void sendMessage(const IMediator& mediator, const std::string& message) const override 
	{
		mediator.distributeMessage(this, message);
	}

private:
	// �������Է����ߵ���Ϣ
	virtual void receiveMessage(const IColleague* sender, const std::string& message) const override 
	{
		std::cout << getName() << " received the message from "
			<< sender->getName() << ": " << message << std::endl;
	}
};

#endif // CONCRETE_COLLEAGUE_H

// 	�����ͻ���
// 	�ҷ�����һ�����������ӹҳ�ȥ���н���֪ͨ������Ҫ�ⷿ���ˣ�

	// main.cpp
//#include "concrete_colleague.h"
//#include "concrete_mediator.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testMediator()
{
	// ����
	IColleague *landlord = new ConcreteColleague("Tom");

	// ���
	IColleague *jerry = new ConcreteColleague("Jerry");
	IColleague *tuffy = new ConcreteColleague("Tuffy");

	// �н��� - ������
	ConcreteMediator mediator;
	mediator.registerColleague(jerry);
	mediator.registerColleague(tuffy);

	// ����ͨ���н齫��Ϣ���ͳ�ȥ
	landlord->sendMessage(mediator, "Xi'erqi, two bedroom house, 6000/month.");

	SAFE_DELETE(jerry);
	SAFE_DELETE(tuffy);

	getchar();

	return 0;
}

// 	������£�
// 	Jerry received the message from Tom: Xi��erqi, two bedroom house, 6000/month. 
//	Tuffy received the message from Tom: Xi��erqi, two bedroom house, 6000/month.