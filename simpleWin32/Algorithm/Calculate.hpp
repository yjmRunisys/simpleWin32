#pragma once
//实现计算器中缀表达式转后缀表达式
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

	变为后缀表达式方法(规则)：

	1.遇到操作数：直接添加到后缀表达式中

	2.栈为空时，遇到运算符，直接入栈

	3.遇到左括号：将其入栈

	4.遇到右括号：执行出栈操作，并将出栈的元素输出，直到弹出栈的是左括号，左括号不输出。

	5.遇到其他运算符：加减乘除：弹出所有优先级大于或者等于该运算符的栈顶元素，然后将该运算符入栈。

	6.最终将栈中的元素依次出栈，输出。
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

	//计算后缀表达式
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

	//计算运算表达式
	int Cal(char str[])
	{
		InitCal();
		PushIntoStack(str);
		int ret = CalPostStr();
		return ret;
	}

	//清空栈
	void ClearStack(stack<char> &m_stack)
	{
		while(!m_stack.empty())
		{
			m_stack.pop();
		}
	}

	//初始化运算
	void InitCal()
	{
		ClearStack(m_stack);		
		posStr.clear();
	}
private:
	stack<char> m_stack;
	string posStr;//后缀式
};