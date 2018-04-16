#pragma once
#ifndef COMMAND_H
#define COMMAND_H

class IReciever;

// 提供执行命令的接口
class Command
{
public:
	Command(IReciever *reciever):m_pReciever(reciever)
	{

	}
	virtual int execute() = 0;  // 执行命令
protected:
	IReciever *m_pReciever;//具体执行，命令分类和执行相应命令
};

#ifndef RECIEVER_H
#define RECIEVER_H

namespace TYPES
{
	enum ACTION
	{
		ADD,  // 加法
		SUBTRACT,  // 减法
		MULTIPLY,  // 乘法
		DIVIDE   // 除法
	};
}

// 命令接收者
class IReciever
{
public:
	virtual void setAction(TYPES::ACTION action) = 0;  // 设置具体命令
	virtual int getResult() = 0;  // 获取命令结果
};

//命令接收者具体实现
class Calculator : public IReciever
{
public:
	Calculator(int x, int y): m_nX(x),m_nY(y)
	{

	}
	void setAction(TYPES::ACTION action)
	{
		m_currentAction = action;
	}
	int getResult()
	{
		int nResult;
		switch (m_currentAction) {
		case TYPES::ACTION::ADD :
			nResult = m_nX + m_nY;
			break;
		case TYPES::ACTION::SUBTRACT :
			nResult = m_nX - m_nY;
			break;
		case TYPES::ACTION::MULTIPLY :
			nResult = m_nX * m_nY;
			break;
		case TYPES::ACTION::DIVIDE :
			nResult = m_nX / m_nY;
			break;
		default:
			break;
		}

		return nResult;
	}

private:
	int m_nX;
	int m_nY;
	TYPES::ACTION m_currentAction;
};

#endif // RECIEVER_H

// 加法
class AddCommand : public Command
{
public:
	AddCommand(IReciever *reciever): Command(reciever)
	{

	}
	int execute()
	{
		printf("Action_add\n");
		m_pReciever->setAction(TYPES::ACTION::ADD);
		return m_pReciever->getResult();
	}
};

// 减法
class SubtractCommand : public Command
{
public:
	SubtractCommand(IReciever *reciever):Command(reciever)
	{

	}
	int execute()
	{
		printf("Action_Subtract\n");
		m_pReciever->setAction(TYPES::ACTION::SUBTRACT);
		return m_pReciever->getResult();
	}
};

// 乘法
class MultiplyCommand : public Command
{
public:
	MultiplyCommand(IReciever *reciever): Command(reciever)
	{

	}
	int execute()
	{
		printf("Action_Multi\n");
		m_pReciever->setAction(TYPES::ACTION::MULTIPLY);
		return m_pReciever->getResult();
	}
};

// 除法
class DivideCommand : public Command
{
public:
	DivideCommand(IReciever *reciever): Command(reciever)
	{

	}
	int execute()
	{
		printf("Action_Divide\n");
		m_pReciever->setAction(TYPES::ACTION::DIVIDE);
		return m_pReciever->getResult();
	}
};

#endif // COMMAND_H

/************************************************************************/
/* 需要一个类，让用户选择要执行的命令 - Client（也就是 UI）。最后，还需要
写一个 Invoker，在示例中依然是用户界面。                                                                     */
/************************************************************************/

namespace spaceCmdPattern{
	// 计算结果

	Calculator calculator(20, 10);
	Command *command = NULL;  // 用于调用命令
	AddCommand addCmd(&calculator);  // 加法
	SubtractCommand subCmd(&calculator);  // 减法
	MultiplyCommand mulCmd(&calculator);  // 乘法
	DivideCommand divCmd(&calculator);  // 除法

	void onCalculate()
	{
		for (int i=0;i<3;i++)
		{
			if (i == 0) {
				command = &addCmd;
			} else if (i == 1) {
				command = &subCmd;
			} else if (i == 2) {
				command = &mulCmd;
			} else if (i == 3) {
				command = &divCmd;
			}

			int nResult = command->execute();
			printf("myresult is %d\n",nResult);
		}

	}

	
}

using namespace spaceCmdPattern;

void testCmdPattern()
{
	onCalculate();
}
