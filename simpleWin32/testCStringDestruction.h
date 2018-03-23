#pragma once
#include "stdafx.h"

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

CString::mCs = new CString(_T("Ok"));

CTestCString mTCS;

