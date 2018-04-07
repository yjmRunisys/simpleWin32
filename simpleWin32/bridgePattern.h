#pragma once 
//�Ž�ģʽ

//�����ĳ�����ʵ�ַ���

/*����ʵ����ӿ�,���е�������һЩ���ԣ����Ա��򿪺͹رգ�*/

// implementor.h
#ifndef IMPLEMENTOR_H
#define IMPLEMENTOR_H

// ����
class IElectricalEquipment
{
public:
	virtual ~IElectricalEquipment() {}

	// ��
	virtual void PowerOn() = 0;

	// �ر�
	virtual void PowerOff() = 0;
};

#endif // IMPLEMENTOR_H

/*��������ʵ����,���������������ĵ��� - ��ƺͷ��ȣ�����ʵ���� IElectricalEquipment �ӿ�*/
// concrete_implementor.h
#ifndef CONCRETE_IMPLEMENTOR_H
#define CONCRETE_IMPLEMENTOR_H

//#include "implementor.h"
#include <iostream>

// ���
class Light : public IElectricalEquipment
{
public:
	// ����
	virtual void PowerOn() override {
		std::cout << "Light is on." << std::endl;
	}

	// �ص�
	virtual void PowerOff() override {
		std::cout << "Light is off." << std::endl;
	}
};

// ����
class Fan : public IElectricalEquipment
{
public:
	// �򿪷���
	virtual void PowerOn() override {
		std::cout << "Fan is on." << std::endl;
	}

	// �رշ���
	virtual void PowerOff() override {
		std::cout << "Fan is off." << std::endl;
	}
};

#endif // CONCRETE_IMPLEMENTOR_H

/*����������,���ڿ�����˵��������֪����ƺͷ��ȵĴ��ڣ�ֻ֪���Լ����Կ��ƣ���/�رգ�ĳ��������Ҳ����˵��ÿ�� ISwitch Ӧ�ó���һ�� IElectricalEquipment ����*/
// abstraction.h
#ifndef ABSTRACTION_H
#define ABSTRACTION_H

//#include "implementor.h"

// ����
class ISwitch
{
public:
	ISwitch(IElectricalEquipment *ee) { m_pEe = ee;}
	virtual ~ISwitch() {}

	// �򿪵���
	virtual void On() = 0;

	// �رյ���
	virtual void Off() = 0;

protected:
	IElectricalEquipment *m_pEe;
};

#endif // ABSTRACTION_H

/************************************************************************/
/* �������������

�ض����͵Ŀ��غܶ࣬��������ʽ���ء���λ���أ�                                                                     */
/************************************************************************/
// refined_abstraction.h
#ifndef REFINED_ABSTRACTION_H
#define REFINED_ABSTRACTION_H

//#include "abstraction.h"
#include <iostream>

// ����ʽ����
class PullChainSwitch : public ISwitch
{
public:
	PullChainSwitch(IElectricalEquipment *ee) : ISwitch(ee) {}

	// ������ʽ���ش򿪵���
	virtual void On() override {
		std::cout << "Switch on the equipment with a pull chain switch." << std::endl;
		m_pEe->PowerOn();
	}

	// ������ʽ���عرյ���
	virtual void Off() override {
		std::cout << "Switch off the equipment with a pull chain switch." << std::endl;
		m_pEe->PowerOff();
	}
};

// ��λ����
class TwoPositionSwitch : public ISwitch
{
public:
	TwoPositionSwitch(IElectricalEquipment *ee) : ISwitch(ee) {}

	// ����λ���ش򿪵���
	virtual void On() override {
		std::cout << "Switch on the equipment with a two-position switch." << std::endl;
		m_pEe->PowerOn();
	}

	// ����λ���عرյ���
	virtual void Off() override {
		std::cout << "Switch off the equipment with a two-position switch." << std::endl;
		m_pEe->PowerOff();
	}
};

#endif // REFINED_ABSTRACTION_H

/************************************************************************/
/* �����ͻ���

�ܺã���ʱ�򽫿��غ͵������������ˣ�                                                                     */
/************************************************************************/
// main.cpp
//#include "refined_abstraction.h"
//#include "concrete_implementor.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testBridgePatern()
{
    // �������� - ��ơ�����
    IElectricalEquipment *light = new Light();
    IElectricalEquipment *fan = new Fan();

    /**
     * �������� - ����ʽ���ء���λ����
     * ������ʽ���غ͵�ƹ�������������λ���غͷ��ȹ�������
    **/
    ISwitch *pullChain = new PullChainSwitch(light);
    ISwitch *twoPosition= new TwoPositionSwitch(fan);

    // ���ơ��ص�
    pullChain->On();
    pullChain->Off();

    // �򿪷��ȡ��رշ���
    twoPosition->On();
    twoPosition->Off();

    SAFE_DELETE(twoPosition);
    SAFE_DELETE(pullChain);
    SAFE_DELETE(fan);
    SAFE_DELETE(light);

    getchar();

    return 0;
}