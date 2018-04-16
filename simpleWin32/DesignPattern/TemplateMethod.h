#pragma once

/************************************************************************/
/* 模版方法

创建抽象类

抽象类由 Company 表示，它提供了一套固定的模板方法 Recruit()，用于标准化算法的骨架    
注意： 相同的行为 CareerTalk() 和 ReceiveResume() 有默认实现，不同的行为 Interview() 和 Offer() 采用“占位符”方式，需要由具体公司来实现。*/
/************************************************************************/
// abstract_class.h
#ifndef ABSTRACT_CLASS_H
#define ABSTRACT_CLASS_H

#include <iostream>

// 公司
class Company
{
public:
	virtual ~Company() {}

	// 校园招聘
	void Recruit() {
		std::cout << "---------- Begin ----------" << std::endl;
		CareerTalk();
		ReceiveResume();
		Interview();
		Offer();
		std::cout << "---------- End ----------" << std::endl;
	}

	// 宣讲会
	void CareerTalk() {
		std::cout << "Delivery" << std::endl;
	}

	// 接收简历
	void ReceiveResume() {
		std::cout << "Receive Resume" << std::endl;
	}

	// 面试
	virtual void Interview() = 0;

	// 发放 Offer
	virtual void Offer() = 0;
};

#endif // ABSTRACT_CLASS_H

/************************************************************************/
/* 创建具体类

具体公司有两个 - Alibaba、Tencent，它们的面试、录用方式不同                                                                     */
/************************************************************************/

// concrete_class.h
#ifndef CONCRETE_CLASS_H
#define CONCRETE_CLASS_H

//#include "abstract_class.h"
#include <iostream>

// 阿里
class Alibaba : public Company
{
public:
	virtual void Interview() override {
		std::cout << "First interview -> Second interview -> Third interview" << std::endl;
	}

	virtual void Offer() override {
		std::cout << "30W" << std::endl;
	}
};

// 腾讯
class Tencent : public Company
{
public:
	virtual void Interview() override {
		std::cout << "First interview -> Second interview" << std::endl;
	}

	virtual void Offer() override {
		std::cout << "25W" << std::endl;
	}
};

#endif // CONCRETE_CLASS_H

/************************************************************************/
/* 创建客户端

校招开启，Offer 快到碗里来                                                                     */
/************************************************************************/
// main.cpp
//#include "concrete_class.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testTemplateMethod()
{
	// 阿里校招
	Company *alibaba = new Alibaba();
	alibaba->Recruit();

	// 腾讯校招
	Company *tencent = new Tencent();
	tencent->Recruit();

	SAFE_DELETE(tencent);
	SAFE_DELETE(alibaba);

	getchar();

	return 0;
}
