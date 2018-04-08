#pragma once
//���ṩ�������������Ĵ���ʱ����

//ԭ��ģʽ��Prototype Pattern����һ�ִ��������ģʽ������һ�������ٴ�������һ���ɶ��ƵĶ��󣬶�����֪���κδ�����ϸ�ڡ�
//ԭ��ģʽ
// ��������
// 
// 	�����ŵ� ��ǣ���� 
// 	ӭ���ճ� ������ϼ 
// 	���� 
// 	����·�ںη� ·�ڽ��� 
// 	����·�ںη� ·�ڽ���
// 	һ�ס�����·�ںη����������������˵����ҡ�����ֻҪǰ��һ�죬С����Ǿ���Ҳ�ѳֲ�ס�ˡ�����
// 	�����μǡ���Ϊ�Ĵ�����֮һ����ν�Ǽ�����������һ���Ĵ��ڡ���С���󣬸��ǰٿ����ᡣ

// 	�ǵ�������ڴ�Ʒ�֡�����ʨ��ʱ�򣬻��һ����ë���û�Ϊ��ǧ���������գ���硢��磬�����˲��ã�������
// 		ԭ��ģʽ������ˣ�ͬ���ṩ�����Ҹ��ƹ��ܡ�
// 
// 	����дͼƬ����
// 
// 	ע�� �����μǡ��м��أ�����ձ��ǻ���ɽ��һ����ʯ������������ɣ��޸�ĸ���������գ���������ʦ������������ա�
// 	PS�� ʾ���еĳ���ԭ��Ϊ���ӣ�Monkey���࣬������ʯ�࣬ǧ��Ҫһ���±ƣ�
// 	����ʵ��
// 	��������ԭ��
// 	����һ�������� Monkey�����ṩһ�� Clone() �ӿڣ��������Ҹ��ơ�

	// prototype.h
#ifndef PROTOTYPE_H
#define PROTOTYPE_H

	// ����
class Monkey
{
public:
	Monkey(){}
	virtual ~Monkey(){}
	virtual Monkey* Clone() = 0;  // ��¡
	virtual void Play() = 0;  // ��ˣ
};

#endif // PROTOTYPE_H

// 	��������ԭ��
// 	�������ڿճ�����

	// concrete_prototype.h
#ifndef CONCRETE_PROTOTYPE_H
#define CONCRETE_PROTOTYPE_H

//#include "prototype.h"
#include <iostream>
#include <string>

	using namespace std;

// �����
class SunWuKong : public Monkey
{
public:
	SunWuKong(string name){ m_strName = name; }
	~SunWuKong(){}

	// �������캯��
	SunWuKong(const SunWuKong &other) {
		m_strName = other.m_strName;
	}
	Monkey* Clone() {
		// ���ÿ������캯��
		return new SunWuKong(*this);
	}
	void Play() {
		cout << m_strName << " play Golden-Hoop-Stick" << endl;
	}

private:
	string m_strName;
};

#endif // CONCRETE_PROTOTYPE_H

// 	ͬ���Ǻ��ӣ���ĺ�������� LOL�������������ǽ𹿰���Golden-Hoop-Stick����˭Ҫ���������ʥ�أ�
// 	�����ͻ���
// 	��һ����ë�������������

	// main.cpp
//#include "concrete_prototype.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testProtype()
{
	// �����
	Monkey *pSWK = new SunWuKong("Qi Tian Da Sheng");

	// ��¡���Ӻ���
	Monkey *pSWK1 = pSWK->Clone();
	Monkey *pSWK2 = pSWK1->Clone();

	pSWK1->Play();
	pSWK2->Play();

	SAFE_DELETE(pSWK1);
	SAFE_DELETE(pSWK2);
	SAFE_DELETE(pSWK);

	getchar();

	return 0;
}

// 	������£�

// 	Qi Tian Da Sheng play Golden-Hoop-Stick 
	// 	Qi Tian Da Sheng play Golden-Hoop-Stick
	// 	������������⣬���ǻ����Դ�������⨺��ʵ���������һ���޶������ߴ�ս���ֵ��췭�ظ����������ǿ��գ�