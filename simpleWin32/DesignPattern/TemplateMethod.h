#pragma once

/************************************************************************/
/* ģ�淽��

����������

�������� Company ��ʾ�����ṩ��һ�׹̶���ģ�巽�� Recruit()�����ڱ�׼���㷨�ĹǼ�    
ע�⣺ ��ͬ����Ϊ CareerTalk() �� ReceiveResume() ��Ĭ��ʵ�֣���ͬ����Ϊ Interview() �� Offer() ���á�ռλ������ʽ����Ҫ�ɾ��幫˾��ʵ�֡�*/
/************************************************************************/
// abstract_class.h
#ifndef ABSTRACT_CLASS_H
#define ABSTRACT_CLASS_H

#include <iostream>

// ��˾
class Company
{
public:
	virtual ~Company() {}

	// У԰��Ƹ
	void Recruit() {
		std::cout << "---------- Begin ----------" << std::endl;
		CareerTalk();
		ReceiveResume();
		Interview();
		Offer();
		std::cout << "---------- End ----------" << std::endl;
	}

	// ������
	void CareerTalk() {
		std::cout << "Delivery" << std::endl;
	}

	// ���ռ���
	void ReceiveResume() {
		std::cout << "Receive Resume" << std::endl;
	}

	// ����
	virtual void Interview() = 0;

	// ���� Offer
	virtual void Offer() = 0;
};

#endif // ABSTRACT_CLASS_H

/************************************************************************/
/* ����������

���幫˾������ - Alibaba��Tencent�����ǵ����ԡ�¼�÷�ʽ��ͬ                                                                     */
/************************************************************************/

// concrete_class.h
#ifndef CONCRETE_CLASS_H
#define CONCRETE_CLASS_H

//#include "abstract_class.h"
#include <iostream>

// ����
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

// ��Ѷ
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
/* �����ͻ���

У�п�����Offer �쵽������                                                                     */
/************************************************************************/
// main.cpp
//#include "concrete_class.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testTemplateMethod()
{
	// ����У��
	Company *alibaba = new Alibaba();
	alibaba->Recruit();

	// ��ѶУ��
	Company *tencent = new Tencent();
	tencent->Recruit();

	SAFE_DELETE(tencent);
	SAFE_DELETE(alibaba);

	getchar();

	return 0;
}
