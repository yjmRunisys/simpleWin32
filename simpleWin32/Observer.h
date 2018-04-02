#pragma once
/************************************************************************/
/* 观察者模式（Observer Pattern），定义了对象间的一对多的依赖关系，让多个
观察者对象同时监听某一个主题对象（被观察者）。当主题对象的状态发生更改时，
会通知所有观察者，让它们能够自动更新。 

自从有了滴滴、快滴、Uber、神舟等各大打车平台，广大市民的出行便利了不少。
但自从合并以后，补助少了，价格也上涨了很多，不 * XX 倍甚至打不到车。。。

滴滴：好，第一个月，价格上调至 12.5。。。 
过了不久，心里想着：纳尼，都垄断了，还不多涨涨，果断 15.0。。。

合并就是为了垄断，再无硝烟四起的价格战，整合成统一价格模式，
用户也就没有了自由选择权。

DiDi

在这里，滴滴相当于主题，司机相当于观察者。*/
/************************************************************************/

/************************************************************************/
/* 创建抽象主题

提供关于注册、注销、通知观察者的接口：                                                                     */
/************************************************************************/

// subject.h
#ifndef SUBJECT_H
#define SUBJECT_H

class IObserver;

// 抽象主题
class ISubject
{
public:
	virtual void Attach(IObserver *) = 0;  // 注册观察者
	virtual void Detach(IObserver *) = 0;  // 注销观察者
	virtual void Notify() = 0;  // 通知观察者
};

#endif // SUBJECT_H

/************************************************************************/
/* 创建抽象观察者

提供一个 Update() 接口，用于更新价格：                                                                     */
/************************************************************************/

// observer.h
#ifndef OBSERVER_H
#define OBSERVER_H

// 抽象观察者
class IObserver
{
public:
	virtual void Update(float price) = 0;  // 更新价格
};

#endif // OBSERVER_H

/************************************************************************/
/* 创建具体主题

抽象主题的具体实现，用于管理所有的观察者：                                                                     */
/************************************************************************/

// concrete_subject.h
#ifndef CONCRETE_SUBJECT_H
#define CONCRETE_SUBJECT_H

//#include "subject.h"
//#include "observer.h"
#include <iostream>
#include <list>

using namespace std;

// 具体主题
//价格为状态值
class ConcreteSubject : public ISubject
{
public:
	ConcreteSubject() { m_fPrice = 10.0; }

	void SetPrice(float price) {
		m_fPrice = price;
	}

	//注册观察者
	void Attach(IObserver *observer) {
		m_observers.push_back(observer);
	}

	//注销观察者
	void Detach(IObserver *observer) {
		m_observers.remove(observer);
	}

	//通知观察者
	void Notify() {
		list<IObserver *>::iterator it = m_observers.begin();
		while (it != m_observers.end()) {
			(*it)->Update(m_fPrice);
			++it;
		}
	}

private:
	list<IObserver *> m_observers;  // 观察者列表
	float m_fPrice;  // 价格
};

#endif // CONCRETE_SUBJECT_H



/************************************************************************/
/* 创建具体观察者

抽象观察者的具体实现，当接收到通知后，调整对应的价格：                                                                     */
/************************************************************************/

// concrete_observer.h
#ifndef CONCRETE_OBSERVER_H
#define CONCRETE_OBSERVER_H

#include "observer.h"
#include <iostream>
#include <string>

using namespace std;

// 具体观察者
class ConcreteObserver : public IObserver
{
public:
	ConcreteObserver(string name) { m_strName = name; }

	void Update(float price) {
		cout << m_strName << " - price: " << price << "\n";
	}

private:
	string m_strName;  // 名字
};

#endif // CONCRETE_OBSERVER_H

/************************************************************************/
/* 创建客户端

创建主题以及对应的观察者，并添加观察者并更新价格：                                                                     */
/************************************************************************/

// main.cpp
//#include "concrete_subject.h"
//#include "concrete_observer.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testObserver()
{
	// 创建主题、观察者
	ConcreteSubject *pSubject = new ConcreteSubject();
	IObserver *pObserver1 = new ConcreteObserver("Jack Ma");
	IObserver *pObserver2 = new ConcreteObserver("Pony");

	// 注册观察者
	pSubject->Attach(pObserver1);
	pSubject->Attach(pObserver2);

	// 更改价格，并通知观察者
	pSubject->SetPrice(12.5);
	pSubject->Notify();

	// 注销观察者
	pSubject->Detach(pObserver2);
	// 再次更改状态，并通知观察者
	pSubject->SetPrice(15.0);
	pSubject->Notify();

	SAFE_DELETE(pObserver1);
	SAFE_DELETE(pObserver2);
	SAFE_DELETE(pSubject);

	getchar();

	return 0;
}