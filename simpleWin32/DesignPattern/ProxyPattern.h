#pragma once
//����ģʽ ����Proxyʵ�ֶ�����ٴη�װ����������Ϊ����Proxy�ĳ�Ա����������������ó�Ա����ִ��
// ��������
// 
// 	�й��ƶ� - ������
// 	CMCC
// 
// 	����ʵ�����У������޴����� - �������ֻ������̡���Ʊ���۵㡣����
// 	�ǵø��ϴ�ѧʱ��ȥѧУ�����������϶�Ҫ���ֻ����û��� Nokia�����쿨����ֵ��
// 	ѧУ�����ĸ��ִ����ࣺܶ���쿨���쿨�����еش�����ֻҪ 18 ����������ֵ����ֵ���� 100 �� 50��������
// 	����ߺ��������˷� O(��_��)O����~
// 	�������ģʽ�������Ϊ���ƶ���˾�ѳ�ֵ��ְ���и�������㣬���������ƶ���˾��ֵ��
// 	�ͻ�ֱ��������򽻵��������ƶ���˾��

// 	����ʵ��
// 	������������
// 	����һ������������ ITelco����Ϊ���ṩһ���ӿ� Recharge()�����ڳ�ֵ��

// subject.h
#ifndef SUBJECTPROXY_H
#define SUBJECTPROXY_H

// ������Ӫ��
class ITelco
{
public:
	virtual ~ITelco(){}
	virtual void Recharge(int money) = 0;  // ��ֵ
};

#endif // SUBJECT_H

// 	������ʵ����
// 	��һֱ�õ����ƶ������Ծ�ѡ���ɣ����̳��Գ��������࣬�ṩ��ҵ�񷽷��ľ���ʵ�֣�

	// real_subject.h
#ifndef REAL_SUBJECT_H
#define REAL_SUBJECT_H

//#include "subject.h"
#include <iostream>

	// �й��ƶ�
class CMCC : public ITelco
{
public:
	void Recharge(int money) override {
		std::cout << "Recharge " << money;
	}
};

#endif // REAL_SUBJECT_H

// 	��������
// 	���ڸտ�ѧ�����������ʮ�ֻ𱬣�С�˿͹˲��� - ���� 50 ���䣺

	// proxy.h
#ifndef PROXY_H
#define PROXY_H

//#include "subject.h"
//#include "real_subject.h"
#include <iostream>
// �����
class Proxy : public ITelco
{
public:
	Proxy() : m_pCMCC(NULL) {}
	~Proxy() { delete m_pCMCC; }

	// ���� 50 ����
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


// 	ע�⣺ ������Ҳ�ǳ�������������࣬����ʱ������ԭ��ҵ�񷽷��Ļ����ϸ���һЩ�µķ��������Թ��ܽ��������Լ����
// 	�����ͻ���
// 	���ڣ���ʼ�ŶӰ�ҵ������

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

// 	������£�

// 	Sorry, too little money 
//	Recharge 100
//	һ��ʼ�������� 20 ��Ǯȥ��ֵ������㲻���䡣����һŭ֮�£���˦ 100��