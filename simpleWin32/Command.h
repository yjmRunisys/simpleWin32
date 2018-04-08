#pragma once

//Invoker������Ϣ����
//Receiveִ�о���Ķ������ֲ��ڸ���Command��

// �������
// 
// 	��������ģʽ��ʵ��һ��������У��γ�һ����������
// 	�Դ�Ϊ�������ǵεΣ�~O(��_��)O~�����û�����һ�����򳵡����
// 	˾���ӵ��������յ�ʱ���û��ٴη���һ����������˾���տ
// 	������ʾ�����ƣ� Command ��һ�������࣬��������ִ������Ľӿڡ�
// 	������ ConcreteCommand �������������ṩ�˾���������/�����
// 
// 	command.h

#ifndef COMMAND_H
#define COMMAND_H

class Reciever;

// �ṩִ������Ľӿ�
class Command
{
public:
	Command(Reciever *reciever)	: m_pReciever(reciever)
	{

	}
	virtual void execute() = 0;  // ִ������
protected:
	Reciever *m_pReciever;
};

// ��
class TakeCommand : public Command
{
public:
	TakeCommand(Reciever *reciever): Command(reciever)
	{

	}
	void execute(){
		std::cout << "Take command..." << std::endl;
		m_pReciever->takeOrder();
	}

};

// ����
class PayCommand : public Command
{
public:
	PayCommand(Reciever *reciever)	: Command(reciever)
	{

	}
	void execute(){
		std::cout << "Pay command..." << std::endl;
		m_pReciever->receipt();
	}
};

#endif // COMMAND_H


// 	���� Command������Ҫ�ж�Ӧ�� Invoker ���������Ȼ����д�����
// 	invoker.h

#ifndef INVOKER_H
#define INVOKER_H

#include <list>
#include "command.h"

// ����ĳ�����
class Invoker
{
public:
	Invoker(){

	}
	void addCmd(Command *cmd)  // �������
	{
		m_cmds.push_back(cmd);
	}
	void deleteCmd(Command *cmd)  // ɾ������
	{
		m_cmds.remove(cmd);
	}
	void notify()  // ִ������
	{
		std::list<Command *>::iterator it = m_cmds.begin();
		while (it != m_cmds.end()) {
			(*it)->execute();
			++it;
		}
	}

private:
	std::list<Command *> m_cmds;  // �������
};

#endif // INVOKER_H
//
//	����� Reciever��Ҳ����˾��������ִ������ӵ�/�տ��
// 
// 	reciever.h

#ifndef RECIEVER_H
#define RECIEVER_H

	// ˾��
class Reciever
{
public:
	void takeOrder()  // �ӵ�
	{
		std::cout << "Take order..." << std::endl;
	}
	void receipt()  // �տ�
	{
		std::cout << "Receipt..." << std::endl;
	}
};

#endif // RECIEVER_H


//	ʹ�������Ƚϼ򵥣�

//#include "invoker.h"
//#include "reciever.h"
#include "command.h"

int testCommand()
{
	Reciever *rev = new Reciever();
	Command *cmd1 = new TakeCommand(rev);
	PayCommand *cmd2 = new PayCommand(rev);
	Invoker inv;

	inv.addCmd(cmd1);
	inv.addCmd(cmd2);
	inv.notify();

	delete cmd1;
	delete cmd2;
	delete rev;

	return 0;
}

//	������£�

// 	Take command�� 
// 	Take order�� 
// 	Pay command�� 
// 	Receipt��
// 	��ʼ�����Ǵ�������������� & �����ͨ�� Invoker �� addCmd() �����Ǽ�����������У�
// 	Ȼ�� notify() ִ֪ͨ��������������γ���һ����������
// 	��Ȥ��
// 	Ҫ���ͷ����ߺͽ�����֮�����϶ȣ�����ģʽ��һ�ַǳ��õķ�ʽ��
// 	��ʵ������ģʽʱ��Ҫ��ס������Ҫ�������ǣ�����ֻ�Ƿ����ߺͽ�����֮������ӡ�
	// 	��Ӧ��ֻ���߽����߷�������������ʲô������Ӧ�����κη�ʽ�ı䷢���ߺͽ����ߵ��߼���