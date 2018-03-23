#pragma once

class CRecordTime{//��ʱ
	/*����-��ʼ��ʱ-������ʱ-��ӡʱ�� �Ĳ�ʹ��
	����-��ʼ��ʱ-������ʱ-��ȡʱ�� �Ĳ�ʹ��
	CRecordTime mRecordTime;//����
	mRecordTime.StartRecordTime();//��ʼ��ʱ
	mRecordTime.EndRecordTime();//������ʱ
	mRecordTime.PrintTime(_T("���ļ���"));//��ӡʱ��
	mRecordTime.GetTimeSpan();//��ȡʱ��
	*/
public:
	LARGE_INTEGER litmp;
	LONGLONG qt1,qt2;
	double dft,dff,dfm;//dffʱ��Ƶ��

	CRecordTime()
	{
		//���ʱ��Ƶ��
		QueryPerformanceFrequency(&litmp);
		dff = (double)litmp.QuadPart;
	}
	~CRecordTime();

	//��ʼ��ʱ
	void StartRecordTime()
	{
		QueryPerformanceCounter(&litmp);
		qt1 = litmp.QuadPart;
	}

	//������ʱ
	void EndRecordTime()
	{
		QueryPerformanceCounter(&litmp);
		qt2 = litmp.QuadPart;
	}

	//��ȡʱ���,us
	ULONG64 GetTimeSpan()
	{
		dfm = (double)(qt2 - qt1);
		dft = dfm/dff;

		ULONG64 timeSpan = (ULONG64)(dft * 1000*1000);
		return timeSpan;

	}

	//��ӡʱ�䣬��ӡʱע��APIʹ��
	void PrintTime(string csHead)
	{
		ULONG64 t = GetTimeSpan();
		string str;
		char strFormat[MAX_PATH];
		sprintf_s(strFormat,"��ʱ%ld us\0",t);
		
		str = csHead + strFormat;
		printf("%s",str.c_str());
	}

};