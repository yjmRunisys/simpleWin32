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
	printf("warn:\t%s\n",msg.c_str());
	SetEvent(hLogEven);
}

void COutPut::InfoLog(string msg)
{
	DWORD dw = WaitForSingleObject (hLogEven,INFINITE);
	
	printf("info:\t%s\n",msg.c_str());
	SetEvent(hLogEven);
}

void COutPut::writeFileBina(string src,string fileName)
{   
	FILE *fp;
	fopen_s(&fp,fileName.c_str(),"wb");
	if(fp == NULL)
		return;
	fwrite(src.c_str(),1,src.size(),fp);
	fclose(fp);
}

void COutPut::writeFileBina(char* src,int size,string fileName)
{
	FILE *fp;
	fopen_s(&fp,fileName.c_str(),"wb");
	if(fp == NULL)
		return;
	fwrite(src,1,size,fp);
	fclose(fp);
}

void AfxInfoLog(string msg)
{
	g_pMainWnd->InfoLog(msg);
}


