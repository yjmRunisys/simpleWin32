#pragma once
//代理模式 代理Proxy实现对象的再次封装，操作对象为代理Proxy的成员变量，具体操作调用成员变量执行
// 案例分析
// 
// 	中国移动 - 代理商
// 	CMCC
// 
// 	在现实生活中，代理无处不在 - 代购、手机代理商、火车票代售点。。。
// 	记得刚上大学时，去学校报道，基本上都要买手机（好怀念 Nokia）、办卡、充值。
// 	学校附近的各种代理点很多：“办卡、办卡，动感地带月租只要 18 啦”、“充值、充值，充 100 送 50”。。。
// 	各种吆喝声此起彼伏 O(∩_∩)O哈哈~
// 	这里，代理模式可以理解为：移动公司把充值的职责托付给代理点，代理点代替移动公司充值，
// 	客户直接与代理点打交道，而非移动公司。

// 	代码实现
// 	创建抽象主题
// 	定义一个电信运行商 ITelco，并为其提供一个接口 Recharge()，用于充值：

// subject.h
#ifndef SUBJECTPROXY_H
#define SUBJECTPROXY_H

// 电信运营商
class ITelco
{
public:
	virtual ~ITelco(){}
	virtual void Recharge(int money) = 0;  // 充值
};

#endif // SUBJECT_H

// 	创建真实主题
// 	我一直用的是移动，所以就选它吧！它继承自抽象主题类，提供了业务方法的具体实现：

	// real_subject.h
#ifndef REAL_SUBJECT_H
#define REAL_SUBJECT_H

//#include "subject.h"
#include <iostream>

	// 中国移动
class CMCC : public ITelco
{
public:
	void Recharge(int money) override {
		std::cout << "Recharge " << money;
	}
};

#endif // REAL_SUBJECT_H

// 	创建代理
// 	由于刚开学，代理点生意十分火爆，小顾客顾不上 - 低于 50 不充：

	// proxy.h
#ifndef PROXY_H
#define PROXY_H

//#include "subject.h"
//#include "real_subject.h"
#include <iostream>
// 代理点
class Proxy : public ITelco
{
public:
	Proxy() : m_pCMCC(NULL) {}
	~Proxy() { delete m_pCMCC; }

	// 低于 50 不充
	void Recharge(int money) override {
		if (money >= 50) {
			if (m_pCMCC == NULL)
				m_pCMCC = new CMCC();
			m_pCMCC->Recharge(money);
		} else {
			std::cout << "Sorry, too little money" << std::endl;
		}
	}

private:
	CMCC *m_pCMCC;
};

#endif // PROXY_H


// 	注意： 代理类也是抽象主题类的子类，调用时可以在原有业务方法的基础上附加一些新的方法，来对功能进行扩充或约束。
// 	创建客户端
// 	现在，开始排队办业务啦：

	// main.cpp
//#include "proxy.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testProxy()
{
	Proxy* proxy = new Proxy();
	proxy->Recharge(20);
	proxy->Recharge(100);

	SAFE_DELETE(proxy);

	getchar();

	return 0;
}

// 	输出如下：

// 	Sorry, too little money 
//	Recharge 100
//	一开始我们拿了 20 块钱去充值，代理点不给充。。。一怒之下，狂甩 100！