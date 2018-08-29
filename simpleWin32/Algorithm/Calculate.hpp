#pragma once
//ʵ�ּ�������׺���ʽת��׺���ʽ
#include "string"
#include "stack"

using namespace std;
class CCalculate
{
public:
	CCalculate()
	{
		InitCal();
	}
public:
	/*****************************************************************************

	��Ϊ��׺���ʽ����(����)��

	1.������������ֱ����ӵ���׺���ʽ��

	2.ջΪ��ʱ�������������ֱ����ջ

	3.���������ţ�������ջ

	4.���������ţ�ִ�г�ջ������������ջ��Ԫ�������ֱ������ջ���������ţ������Ų������

	5.����������������Ӽ��˳��������������ȼ����ڻ��ߵ��ڸ��������ջ��Ԫ�أ�Ȼ�󽫸��������ջ��

	6.���ս�ջ�е�Ԫ�����γ�ջ�������
	*****************************************************************************/
	void PushIntoStack(char *strSrc)
	{
		int len = (int)strlen(strSrc);
		int j = 0;
		for (int i=0;i<len;i++)
		{
			if (i==5)
			{
				int yjm = 1;
			}
			if (strSrc[i] >= '0' && strSrc[i] <= '9')
			{
				posStr.push_back(strSrc[i]);
			}else if (strSrc[i] == '*' || strSrc[i] == '/')
			{
				if (m_stack.empty())
				{
					m_stack.push(strSrc[i]);
				}else{
					while(m_stack.top() == '*' || m_stack.top() == '/')
					{
						posStr.push_back(m_stack.top());
						m_stack.pop();
						if (m_stack.empty())
						{
							break;
						}
					}
					m_stack.push(strSrc[i]);
				}
				
			}else if (strSrc[i] == '+' || strSrc[i] == '-')
			{
				if (m_stack.empty())
				{
					m_stack.push(strSrc[i]);
				}else{
					while(m_stack.top() == '*' || m_stack.top() == '/' || m_stack.top() == '+' || m_stack.top() == '-')
					{
						posStr.push_back(m_stack.top());
						m_stack.pop();
						if (m_stack.empty())
						{
							break;
						}
					}
					m_stack.push(strSrc[i]);
				}
			}else if (strSrc[i] == ')')
			{
				if (!m_stack.empty())
				{
					while(m_stack.top() != '(')
					{
						posStr.push_back(m_stack.top());
						m_stack.pop();
						if (m_stack.empty())
						{
							break;
						}
					}
					m_stack.pop();
				}
			}else{
				m_stack.push(strSrc[i]);
			}
		}

		while(!m_stack.empty())
		{
			posStr.push_back(m_stack.top());
			m_stack.pop();
		}

	}

	//�����׺���ʽ
	int CalPostStr()
	{
		stack<int> stackTmp;
		int topNum;
		for (int i=0;i<(int)posStr.size();i++)
		{
			if (posStr[i] >= '0' && posStr[i] <= '9')
			{
				stackTmp.push(posStr[i] - '0');
			}else if (posStr[i] == '+')
			{
				topNum = stackTmp.top();
				stackTmp.pop();
				topNum = stackTmp.top() + topNum;
				stackTmp.pop();
				stackTmp.push(topNum);
			}else if (posStr[i] == '-')
			{
				topNum = stackTmp.top();
				stackTmp.pop();
				topNum = stackTmp.top() - topNum;
				stackTmp.pop();
				stackTmp.push(topNum);
			}else if (posStr[i] == '*')
			{
				topNum = stackTmp.top();
				stackTmp.pop();
				topNum = stackTmp.top() * topNum;
				stackTmp.pop();
				stackTmp.push(topNum);
			}else if (posStr[i] == '/')
			{
				topNum = stackTmp.top();
				stackTmp.pop();
				topNum = stackTmp.top() / topNum;
				stackTmp.pop();
				stackTmp.push(topNum);
			}
		}

		return stackTmp.top();
	}

	//����������ʽ
	int Cal(char str[])
	{
		InitCal();
		PushIntoStack(str);
		int ret = CalPostStr();
		return ret;
	}

	//���ջ
	void ClearStack(stack<char> &m_stack)
	{
		while(!m_stack.empty())
		{
			m_stack.pop();
		}
	}

	//��ʼ������
	void InitCal()
	{
		ClearStack(m_stack);		
		posStr.clear();
	}
private:
	stack<char> m_stack;
	string posStr;//��׺ʽ
};