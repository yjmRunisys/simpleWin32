#pragma once
#include "windows.h"
#include "string"

using namespace std;
class COutPut
{
public:	
	void WarnLog(string msg);
	void InfoLog(string msg);

	static COutPut *getInstance();

private:
	COutPut(void);
	~COutPut(void);
	static COutPut *pOutPut;
	HANDLE hLogEven;//保证发送独占性，通过事件处理保证独占性

private:
	//销毁单例模式COutPut
	class CGarbe{
		public:
			~CGarbe();

	};

	static CGarbe garbe;
};

extern COutPut *g_pMainWnd;

