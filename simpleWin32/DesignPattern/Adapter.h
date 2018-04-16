#pragma once
//�����õĶ��󣬼̳��������������������������������ݵĶ��󣬵��ü��ݶ���ķ�����
//�Ӷ�ʹ�ò����õĶ����ÿ��ã���Ϊ����������

//��������Ϊ�������ֶ�������࣬ʹ��ԭ�������õĶ����ÿ����ã���Ҫʹ����Ķ�̳�

//������ģʽ

// ����������
// 	����Ŀ��ӿ�
// 	����˹�ṩ�Ĳ�����

	// target.h
#ifndef TARGET_H
#define TARGET_H

#include <iostream>

	// ����˹�ṩ�Ĳ���
class IRussiaSocket
{
public:
	// ʹ��˫��Բ�γ�磨�ݲ�ʵ�֣�
	virtual void Charge() = 0;
};

#endif // TARGET_H

// 	����������
// 	�������������Դ��ĳ������

	// adaptee.h
#ifndef ADAPTEE_H
#define ADAPTEE_H

#include <iostream>

	using namespace std;

// �Դ��ĳ���� - ���ű���
class OwnCharger
{
public:
	void ChargeWithFeetFlat() {
		cout << "OwnCharger::ChargeWithFeetFlat" << endl;
	}
};

#endif // ADAPTEE_H

// 	����������
// 	����һ����Դ����������ʹ�������Դ��ĳ������磺

	// adapter.h
#ifndef ADAPTER_H
#define ADAPTER_H

//#include "target.h"
//#include "adaptee.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

	// ��Դ������
class PowerAdapter : public IRussiaSocket
{
public:
	PowerAdapter() : m_pCharger(new OwnCharger()){}
	~PowerAdapter() {
		SAFE_DELETE(m_pCharger);
	}
	void Charge() {
		//  ʹ���Դ��ĳ���������ű��ͣ����
		m_pCharger->ChargeWithFeetFlat();
	}

private:
	OwnCharger *m_pCharger;  // ������Ҫ������Ľӿڶ��� - �Դ��ĳ����
};

#endif // ADAPTER_H

// �����ͻ���
// 	���գ��ͻ���ʵ�����£�

	// main.cpp
#include "adapter.h"

int testAdapter()
{
	// ����������
	IRussiaSocket *pAdapter = new PowerAdapter();

	// ���
	pAdapter->Charge();

	SAFE_DELETE(pAdapter);

	getchar();

	return 0;
}

// 	������£�
// 	OwnCharger::ChargeWithFeetFlat

// 	��˵���������������ˣ����ڿ���ʹ�����ű��Ͳ�׳���ˡ����ǲ�û�иı����˹�ṩ�Ĳ�����
// 		ֻ�ṩ��һ������������ʹ���й��ı�׼��ڳ�硣�����������ģʽ�����������ı�ԭ�нӿڣ�ȴ����ʹ���½ӿڵĹ��ܡ�

// 	��������
// 
// 	Target �� Adaptee ���ֲ��䣬ֻ��Ҫ�� Adapter ��Ϊ��̳еķ�ʽ���ɣ�

#ifndef ADAPTER_H
#define ADAPTER_H

#include "target.h"
#include "adaptee.h"

	// ��Դ������
class PowerAdapter : public IRussiaSocket, OwnCharger
{
public:
	PowerAdapter() {}
	void Charge() {
		// ʹ���Դ��ĳ���������ű��ͣ����
		ChargeWithFeetFlat();
	}
};

#endif // ADAPTER_H

//	����֮�⣬�����÷��͡�������������һ�¡�