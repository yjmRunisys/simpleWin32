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
	HANDLE hLogEven;//��֤���Ͷ�ռ�ԣ�ͨ���¼�����֤��ռ��

private:
	//���ٵ���ģʽCOutPut
	class CGarbe{
		public:
			~CGarbe();

	};

	static CGarbe garbe;
};

extern COutPut *g_pMainWnd;

