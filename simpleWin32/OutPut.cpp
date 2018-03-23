#include "StdAfx.h"
#include "OutPut.h"
#include <locale.h>

COutPut *g_pMainWnd = COutPut::getInstance();
COutPut *COutPut::pOutPut = NULL;

COutPut::CGarbe COutPut::garbe;

COutPut *COutPut::getInstance()
{
	setlocale( LC_ALL, "" );

	if (pOutPut == NULL)
	{
		pOutPut = new COutPut();
	}

	return pOutPut;
}

COutPut::CGarbe::~CGarbe()
{
	if (pOutPut != NULL)
	{
		delete pOutPut;
		pOutPut = NULL;
	}

}

COutPut::COutPut(void)
{
	//日志事件创立
	hLogEven = CreateEvent(NULL,FALSE,TRUE,_T("COMM_LogEven"));//第一次可使用，谁使用完谁解放，保证独占性
}


COutPut::~COutPut(void)
{
	if (hLogEven != NULL)
	{
		CloseHandle(hLogEven);
		hLogEven = NULL;
	}
}

void COutPut::WarnLog(string msg)
{
	DWORD dw = WaitForSingleObject (hLogEven,INFINITE);
	printf("warn:%s\n",msg.c_str());
	SetEvent(hLogEven);
}

void COutPut::InfoLog(string msg)
{
	DWORD dw = WaitForSingleObject (hLogEven,INFINITE);
	
	printf("info:%s\n",msg.c_str());
	SetEvent(hLogEven);
}


