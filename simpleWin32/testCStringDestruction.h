#pragma once
#include "stdafx.h"
#include <afxwin.h>

class CTestCString{
public:
	static CString *mCs;
	CTestCString()
	{

	}
	~CTestCString()
	{
		delete mCs;

		int yjm = 1;
	}
};

CString * CTestCString::mCs = new CString(_T("Ok"));

CTestCString mTCS;

