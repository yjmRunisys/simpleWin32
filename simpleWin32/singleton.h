// singleton.h
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

using namespace std;

// 单例 - 自动释放
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
	Singleton() {}  // 构造函数（被保护）

private:
	static Singleton *m_pSingleton;  // 指向单例对象的指针

	// GC 机制
	class GC
	{
	public:
		~GC()
		{
			// 可以在这里销毁所有的资源，例如：db 连接、文件句柄等
			if (m_pSingleton != NULL) {
				cout << "Here destroy the m_pSingleton..." << endl;
				delete m_pSingleton;
				m_pSingleton = NULL;
			}
		}
		static GC gc;  // 用于释放单例
	};
};

#endif // SINGLETON_H

Singleton* Singleton::m_pSingleton = new Singleton();
Singleton::GC Singleton::GC::gc; // 重要

int testSingleton()
{
	Singleton *pSingleton1 = Singleton::GetInstance();
	Singleton *pSingleton2 = Singleton::GetInstance();

	cout << (pSingleton1 == pSingleton2) << endl;

	return 0;
}