#pragma once
#ifndef COMMAND_H
#define COMMAND_H

class IReciever;

// �ṩִ������Ľӿ�
class Command
{
public:
	Command(IReciever *reciever):m_pReciever(reciever)
	{

	}
	virtual int execute() = 0;  // ִ������
protected:
	IReciever *m_pReciever;//����ִ�У���������ִ����Ӧ����
};

#ifndef RECIEVER_H
#define RECIEVER_H

namespace TYPES
{
	enum ACTION
	{
		ADD,  // �ӷ�
		SUBTRACT,  // ����
		MULTIPLY,  // �˷�
		DIVIDE   // ����
	};
}

// ���������
class IReciever
{
public:
	virtual void setAction(TYPES::ACTION action) = 0;  // ���þ�������
	virtual int getResult() = 0;  // ��ȡ������
};

//��������߾���ʵ��
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

// �ӷ�
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

// ����
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

// �˷�
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

// ����
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
/* ��Ҫһ���࣬���û�ѡ��Ҫִ�е����� - Client��Ҳ���� UI������󣬻���Ҫ
дһ�� Invoker����ʾ������Ȼ���û����档                                                                     */
/************************************************************************/

namespace spaceCmdPattern{
	// ������

	Calculator calculator(20, 10);
	Command *command = NULL;  // ���ڵ�������
	AddCommand addCmd(&calculator);  // �ӷ�
	SubtractCommand subCmd(&calculator);  // ����
	MultiplyCommand mulCmd(&calculator);  // �˷�
	DivideCommand divCmd(&calculator);  // ����

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
