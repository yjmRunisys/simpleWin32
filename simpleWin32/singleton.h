// singleton.h
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

using namespace std;

// ���� - �Զ��ͷ�
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		if (m_pSingleton == NULL) {		
			if (m_pSingleton == NULL) {
				m_pSingleton = new Singleton();
			}
		}
		return m_pSingleton;
	}

private:
	Singleton() {}  // ���캯������������

private:
	static Singleton *m_pSingleton;  // ָ���������ָ��

	// GC ����
	class GC
	{
	public:
		~GC()
		{
			// �����������������е���Դ�����磺db ���ӡ��ļ������
			if (m_pSingleton != NULL) {
				cout << "Here destroy the m_pSingleton..." << endl;
				delete m_pSingleton;
				m_pSingleton = NULL;
			}
		}
		static GC gc;  // �����ͷŵ���
	};
};

#endif // SINGLETON_H

Singleton* Singleton::m_pSingleton = new Singleton();
Singleton::GC Singleton::GC::gc; // ��Ҫ

int testSingleton()
{
	Singleton *pSingleton1 = Singleton::GetInstance();
	Singleton *pSingleton2 = Singleton::GetInstance();

	cout << (pSingleton1 == pSingleton2) << endl;

	return 0;
}