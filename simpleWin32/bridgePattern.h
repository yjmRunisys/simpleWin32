#pragma once 
//桥接模式

//操作的抽象与实现分离

/*创建实现类接口,所有电器都有一些共性，可以被打开和关闭：*/

// implementor.h
#ifndef IMPLEMENTOR_H
#define IMPLEMENTOR_H

// 电器
class IElectricalEquipment
{
public:
	virtual ~IElectricalEquipment() {}

	// 打开
	virtual void PowerOn() = 0;

	// 关闭
	virtual void PowerOff() = 0;
};

#endif // IMPLEMENTOR_H

/*创建具体实现类,接下来，是真正的电器 - 电灯和风扇，它们实现了 IElectricalEquipment 接口*/
// concrete_implementor.h
#ifndef CONCRETE_IMPLEMENTOR_H
#define CONCRETE_IMPLEMENTOR_H

//#include "implementor.h"
#include <iostream>

// 电灯
class Light : public IElectricalEquipment
{
public:
	// 开灯
	virtual void PowerOn() override {
		std::cout << "Light is on." << std::endl;
	}

	// 关灯
	virtual void PowerOff() override {
		std::cout << "Light is off." << std::endl;
	}
};

// 风扇
class Fan : public IElectricalEquipment
{
public:
	// 打开风扇
	virtual void PowerOn() override {
		std::cout << "Fan is on." << std::endl;
	}

	// 关闭风扇
	virtual void PowerOff() override {
		std::cout << "Fan is off." << std::endl;
	}
};

#endif // CONCRETE_IMPLEMENTOR_H

/*创建抽象类,对于开关来说，它并不知道电灯和风扇的存在，只知道自己可以控制（打开/关闭）某个电器。也就是说，每个 ISwitch 应该持有一个 IElectricalEquipment 对象：*/
// abstraction.h
#ifndef ABSTRACTION_H
#define ABSTRACTION_H

//#include "implementor.h"

// 开关
class ISwitch
{
public:
	ISwitch(IElectricalEquipment *ee) { m_pEe = ee;}
	virtual ~ISwitch() {}

	// 打开电器
	virtual void On() = 0;

	// 关闭电器
	virtual void Off() = 0;

protected:
	IElectricalEquipment *m_pEe;
};

#endif // ABSTRACTION_H

/************************************************************************/
/* 创建扩充抽象类

特定类型的开关很多，比如拉链式开关、两位开关：                                                                     */
/************************************************************************/
// refined_abstraction.h
#ifndef REFINED_ABSTRACTION_H
#define REFINED_ABSTRACTION_H

//#include "abstraction.h"
#include <iostream>

// 拉链式开关
class PullChainSwitch : public ISwitch
{
public:
	PullChainSwitch(IElectricalEquipment *ee) : ISwitch(ee) {}

	// 用拉链式开关打开电器
	virtual void On() override {
		std::cout << "Switch on the equipment with a pull chain switch." << std::endl;
		m_pEe->PowerOn();
	}

	// 用拉链式开关关闭电器
	virtual void Off() override {
		std::cout << "Switch off the equipment with a pull chain switch." << std::endl;
		m_pEe->PowerOff();
	}
};

// 两位开关
class TwoPositionSwitch : public ISwitch
{
public:
	TwoPositionSwitch(IElectricalEquipment *ee) : ISwitch(ee) {}

	// 用两位开关打开电器
	virtual void On() override {
		std::cout << "Switch on the equipment with a two-position switch." << std::endl;
		m_pEe->PowerOn();
	}

	// 用两位开关关闭电器
	virtual void Off() override {
		std::cout << "Switch off the equipment with a two-position switch." << std::endl;
		m_pEe->PowerOff();
	}
};

#endif // REFINED_ABSTRACTION_H

/************************************************************************/
/* 创建客户端

很好，是时候将开关和电器关联起来了：                                                                     */
/************************************************************************/
// main.cpp
//#include "refined_abstraction.h"
//#include "concrete_implementor.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testBridgePatern()
{
    // 创建电器 - 电灯、风扇
    IElectricalEquipment *light = new Light();
    IElectricalEquipment *fan = new Fan();

    /**
     * 创建开关 - 拉链式开关、两位开关
     * 将拉链式开关和电灯关联起来，将两位开关和风扇关联起来
    **/
    ISwitch *pullChain = new PullChainSwitch(light);
    ISwitch *twoPosition= new TwoPositionSwitch(fan);

    // 开灯、关灯
    pullChain->On();
    pullChain->Off();

    // 打开风扇、关闭风扇
    twoPosition->On();
    twoPosition->Off();

    SAFE_DELETE(twoPosition);
    SAFE_DELETE(pullChain);
    SAFE_DELETE(fan);
    SAFE_DELETE(light);

    getchar();

    return 0;
}