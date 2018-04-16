#pragma once
/************************************************************************/
/* �۲���ģʽ��Observer Pattern���������˶�����һ�Զ��������ϵ���ö��
�۲��߶���ͬʱ����ĳһ��������󣨱��۲��ߣ�������������״̬��������ʱ��
��֪ͨ���й۲��ߣ��������ܹ��Զ����¡� 

�Դ����˵εΡ���Ρ�Uber�����۵ȸ����ƽ̨���������ĳ��б����˲��١�
���ԴӺϲ��Ժ󣬲������ˣ��۸�Ҳ�����˺ܶ࣬�� * XX �������򲻵���������

�εΣ��ã���һ���£��۸��ϵ��� 12.5������ 
���˲��ã��������ţ����ᣬ��¢���ˣ����������ǣ����� 15.0������

�ϲ�����Ϊ��¢�ϣ�������������ļ۸�ս�����ϳ�ͳһ�۸�ģʽ��
�û�Ҳ��û��������ѡ��Ȩ��

DiDi

������ε��൱�����⣬˾���൱�ڹ۲��ߡ�*/
/************************************************************************/

/************************************************************************/
/* ������������

�ṩ����ע�ᡢע����֪ͨ�۲��ߵĽӿڣ�                                                                     */
/************************************************************************/

// subject.h
#ifndef SUBJECT_H
#define SUBJECT_H

class IObserver;

// ��������
class ISubject
{
public:
	virtual void Attach(IObserver *) = 0;  // ע��۲���
	virtual void Detach(IObserver *) = 0;  // ע���۲���
	virtual void Notify() = 0;  // ֪ͨ�۲���
};

#endif // SUBJECT_H

/************************************************************************/
/* ��������۲���

�ṩһ�� Update() �ӿڣ����ڸ��¼۸�                                                                     */
/************************************************************************/

// observer.h
#ifndef OBSERVER_H
#define OBSERVER_H

// ����۲���
class IObserver
{
public:
	virtual void Update(float price) = 0;  // ���¼۸�
};

#endif // OBSERVER_H

/************************************************************************/
/* ������������

��������ľ���ʵ�֣����ڹ������еĹ۲��ߣ�                                                                     */
/************************************************************************/

// concrete_subject.h
#ifndef CONCRETE_SUBJECT_H
#define CONCRETE_SUBJECT_H

//#include "subject.h"
//#include "observer.h"
#include <iostream>
#include <list>

using namespace std;

// ��������
//�۸�Ϊ״ֵ̬
class ConcreteSubject : public ISubject
{
public:
	ConcreteSubject() { m_fPrice = 10.0; }

	void SetPrice(float price) {
		m_fPrice = price;
	}

	//ע��۲���
	void Attach(IObserver *observer) {
		m_observers.push_back(observer);
	}

	//ע���۲���
	void Detach(IObserver *observer) {
		m_observers.remove(observer);
	}

	//֪ͨ�۲���
	void Notify() {
		list<IObserver *>::iterator it = m_observers.begin();
		while (it != m_observers.end()) {
			(*it)->Update(m_fPrice);
			++it;
		}
	}

private:
	list<IObserver *> m_observers;  // �۲����б�
	float m_fPrice;  // �۸�
};

#endif // CONCRETE_SUBJECT_H



/************************************************************************/
/* ��������۲���

����۲��ߵľ���ʵ�֣������յ�֪ͨ�󣬵�����Ӧ�ļ۸�                                                                     */
/************************************************************************/

// concrete_observer.h
#ifndef CONCRETE_OBSERVER_H
#define CONCRETE_OBSERVER_H

#include "observer.h"
#include <iostream>
#include <string>

using namespace std;

// ����۲���
class ConcreteObserver : public IObserver
{
public:
	ConcreteObserver(string name) { m_strName = name; }

	void Update(float price) {
		cout << m_strName << " - price: " << price << "\n";
	}

private:
	string m_strName;  // ����
};

#endif // CONCRETE_OBSERVER_H

/************************************************************************/
/* �����ͻ���

���������Լ���Ӧ�Ĺ۲��ߣ�����ӹ۲��߲����¼۸�                                                                     */
/************************************************************************/

// main.cpp
//#include "concrete_subject.h"
//#include "concrete_observer.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testObserver()
{
	// �������⡢�۲���
	ConcreteSubject *pSubject = new ConcreteSubject();
	IObserver *pObserver1 = new ConcreteObserver("Jack Ma");
	IObserver *pObserver2 = new ConcreteObserver("Pony");

	// ע��۲���
	pSubject->Attach(pObserver1);
	pSubject->Attach(pObserver2);

	// ���ļ۸񣬲�֪ͨ�۲���
	pSubject->SetPrice(12.5);
	pSubject->Notify();

	// ע���۲���
	pSubject->Detach(pObserver2);
	// �ٴθ���״̬����֪ͨ�۲���
	pSubject->SetPrice(15.0);
	pSubject->Notify();

	SAFE_DELETE(pObserver1);
	SAFE_DELETE(pObserver2);
	SAFE_DELETE(pSubject);

	getchar();

	return 0;
}