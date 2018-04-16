#pragma once

class CRecordTime{//计时
	/*定义-开始计时-结束计时-打印时间 四步使用
	或定义-开始计时-结束计时-获取时间 四步使用
	CRecordTime mRecordTime;//定义
	mRecordTime.StartRecordTime();//开始计时
	mRecordTime.EndRecordTime();//结束计时
	mRecordTime.PrintTime(_T("跨文件打开"));//打印时间
	mRecordTime.GetTimeSpan();//获取时间
	*/
public:
	LARGE_INTEGER litmp;
	LONGLONG qt1,qt2;
	double dft,dff,dfm;//dff时钟频率

	CRecordTime()
	{
		//获得时钟频率
		QueryPerformanceFrequency(&litmp);
		dff = (double)litmp.QuadPart;
	}
	~CRecordTime();

	//开始计时
	void StartRecordTime()
	{
		QueryPerformanceCounter(&litmp);
		qt1 = litmp.QuadPart;
	}

	//结束计时
	void EndRecordTime()
	{
		QueryPerformanceCounter(&litmp);
		qt2 = litmp.QuadPart;
	}

	//获取时间段,us
	ULONG64 GetTimeSpan()
	{
		dfm = (double)(qt2 - qt1);
		dft = dfm/dff;

		ULONG64 timeSpan = (ULONG64)(dft * 1000*1000);
		return timeSpan;

	}

	//打印时间，打印时注意API使用
	void PrintTime(string csHead)
	{
		ULONG64 t = GetTimeSpan();
		string str;
		char strFormat[MAX_PATH];
		sprintf_s(strFormat,"用时%ld us\0",t);
		
		str = csHead + strFormat;
		printf("%s",str.c_str());
	}

};