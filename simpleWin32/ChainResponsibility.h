#pragma once
// 
//ְ����ģʽ��Chain of Responsibility Pattern��ʹ��������л��ᴦ������
//�Ӷ���������ķ����ߺͽ�����֮�����Ϲ�ϵ������Щ��������һ���������������������ݸ�����ֱ����һ����������Ϊֹ��

// 	������������
// 	�������߳����ṩһ��������ٵĽӿ�֮�⣬����һ���ܹؼ��ĵط����Ƕ������ߣ���������Թ���һ������

//Ϊ�������ú�̴���

	// handler.h
#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>

// ��������
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
	IHandler *m_pSuccessor;  // �����
};

#endif // HANDLER_H

// 	�������崦����
// 	���崦���߰��� Manager��Director��CEO�����ǵ�ʵ�ֻ�����ͬ��ֻ����׼��������һ����

	// concrete_handler.h
#ifndef CONCRETE_HANDLER_H
#define CONCRETE_HANDLER_H

//#include "handler.h"

	// ����
class Manager : public IHandler
{
public:
	Manager() {}
	~Manager() {}
	virtual void HandleRequest(float days) override 
	{
		if (days <= 1) {
			std::cout << "Manager ��׼�� " << days << " ���" << std::endl;
		} else {
			m_pSuccessor->HandleRequest(days);
		}
	}
};

// �ܼ�
class Director : public IHandler
{
public:
	Director() {}
	~Director() {}
	virtual void HandleRequest(float days) override 
	{
		if (days <= 3) 
		{
			std::cout << "Director ��׼�� " << days << " ���" << std::endl;
		} else {
			m_pSuccessor->HandleRequest(days);
		}
	}
};

// �ܲ�
class CEO : public IHandler
{
public:
	CEO() {}
	~CEO() {}
	virtual void HandleRequest(float days) override 
	{
		if (days <= 7) {
			std::cout << "CEO ��׼�� " << days << " ���" << std::endl;
		} else 
		{
			std::cout << "����ų��٣��Ժ������ϰ�����" << std::endl;
		}
	}
};

#endif // CONCRETE_HANDLER_H

// 	ע�⣺ ���� CEO λ����߲㣨��������ĩβ�����������󵽴˽���������������´��ݡ�
// 	�����ͻ���
// 	��ʼ��٣�˵��������ɣ�

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

	// ְ���������� -> �ܼ� -> �ܲ�
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

// 	������£�

// 	Manager ��׼�� 1 ��� 
// 	Director ��׼�� 2 ��� 
//	CEO ��׼�� 5 ��� 
//	����ų��٣��Ժ������ϰ�����