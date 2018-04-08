#pragma once

//Invoker管理消息队列
//Receive执行具体的动作，分布于各个Command中

// 命令队列
// 
// 	根据命令模式，实现一个命令队列，形成一个命令链。
// 	以打车为例，又是滴滴（~O(∩_∩)O~），用户发起一个“打车”命令，
// 	司机接单，到达终点时，用户再次发起一个“付款”命令，司机收款。
// 	和上述示例类似， Command 是一个抽象类，将被用作执行命令的接口。
// 	其他的 ConcreteCommand 类派生自它，提供了具体的命令（打车/付款）。
// 
// 	command.h

#ifndef COMMAND_H
#define COMMAND_H

class Reciever;

// 提供执行命令的接口
class Command
{
public:
	Command(Reciever *reciever)	: m_pReciever(reciever)
	{

	}
	virtual void execute() = 0;  // 执行命令
protected:
	Reciever *m_pReciever;
};

// 打车
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

// 付款
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


// 	有了 Command，就需要有对应的 Invoker 来持有命令，然后进行触发。
// 	invoker.h

#ifndef INVOKER_H
#define INVOKER_H

#include <list>
#include "command.h"

// 命令的持有者
class Invoker
{
public:
	Invoker(){

	}
	void addCmd(Command *cmd)  // 添加命令
	{
		m_cmds.push_back(cmd);
	}
	void deleteCmd(Command *cmd)  // 删除命令
	{
		m_cmds.remove(cmd);
	}
	void notify()  // 执行命令
	{
		std::list<Command *>::iterator it = m_cmds.begin();
		while (it != m_cmds.end()) {
			(*it)->execute();
			++it;
		}
	}

private:
	std::list<Command *> m_cmds;  // 命令队列
};

#endif // INVOKER_H
//
//	最后是 Reciever，也就是司机，用于执行命令（接单/收款）。
// 
// 	reciever.h

#ifndef RECIEVER_H
#define RECIEVER_H

	// 司机
class Reciever
{
public:
	void takeOrder()  // 接单
	{
		std::cout << "Take order..." << std::endl;
	}
	void receipt()  // 收款
	{
		std::cout << "Receipt..." << std::endl;
	}
};

#endif // RECIEVER_H


//	使用起来比较简单：

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

//	输出如下：

// 	Take command… 
// 	Take order… 
// 	Pay command… 
// 	Receipt…
// 	开始，我们创建了两个命令（打车 & 付款），通过 Invoker 的 addCmd() 将他们加入至命令队列，
// 	然后 notify() 通知执行命令，这样，就形成了一个命令链。
// 	兴趣点
// 	要降低发送者和接收者之间的耦合度，命令模式是一种非常好的方式。
// 	在实现命令模式时，要记住，最重要的事情是：命令只是发送者和接收者之间的链接。
	// 	它应该只告诉接收者发送者期望的是什么，而不应该以任何方式改变发送者和接收者的逻辑。