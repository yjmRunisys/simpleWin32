// hwTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Calculate.hpp"
#include "iostream"

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	//CHwTest::SortStringNum();
	CCalculate cal;
	string str = "3+5*2-9*(3+6)";
	int result = cal.Cal((char*)str.data());

	cout<<str<<"="<<result<<endl;
	
	return 0;
}

