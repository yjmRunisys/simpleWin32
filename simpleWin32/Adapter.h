#pragma once
//不适用的对象，继承于子类适配器，子类适配器包含兼容的对象，调用兼容对象的方法，
//从而使得不适用的对象变得可用，此为对象适配器

//类适配器为构造两种对象的子类，使得原本不适用的对象变得可适用，但要使用类的多继承

//适配器模式

// 对象适配器
// 	创建目标接口
// 	俄罗斯提供的插座：

	// target.h
#ifndef TARGET_H
#define TARGET_H

#include <iostream>

	// 俄罗斯提供的插座
class IRussiaSocket
{
public:
	// 使用双脚圆形充电（暂不实现）
	virtual void Charge() = 0;
};

#endif // TARGET_H

// 	创建适配者
// 	再来看看我们自带的充电器：

	// adaptee.h
#ifndef ADAPTEE_H
#define ADAPTEE_H

#include <iostream>

	using namespace std;

// 自带的充电器 - 两脚扁型
class OwnCharger
{
public:
	void ChargeWithFeetFlat() {
		cout << "OwnCharger::ChargeWithFeetFlat" << endl;
	}
};

#endif // ADAPTEE_H

// 	创建适配器
// 	定义一个电源适配器，并使用我们自带的充电器充电：

	// adapter.h
#ifndef ADAPTER_H
#define ADAPTER_H

//#include "target.h"
//#include "adaptee.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

	// 电源适配器
class PowerAdapter : public IRussiaSocket
{
public:
	PowerAdapter() : m_pCharger(new OwnCharger()){}
	~PowerAdapter() {
		SAFE_DELETE(m_pCharger);
	}
	void Charge() {
		//  使用自带的充电器（两脚扁型）充电
		m_pCharger->ChargeWithFeetFlat();
	}

private:
	OwnCharger *m_pCharger;  // 持有需要被适配的接口对象 - 自带的充电器
};

#endif // ADAPTER_H

// 创建客户端
// 	最终，客户端实现如下：

	// main.cpp
#include "adapter.h"

int testAdapter()
{
	// 创建适配器
	IRussiaSocket *pAdapter = new PowerAdapter();

	// 充电
	pAdapter->Charge();

	SAFE_DELETE(pAdapter);

	getchar();

	return 0;
}

// 	输出如下：
// 	OwnCharger::ChargeWithFeetFlat

// 	这说明适配器起作用了，现在可以使用两脚扁型插孔充电了。我们并没有改变俄罗斯提供的插座，
// 		只提供了一个适配器就能使用中国的标准插口充电。这就是适配器模式的魅力：不改变原有接口，却还能使用新接口的功能。

// 	类适配器
// 
// 	Target 和 Adaptee 保持不变，只需要将 Adapter 变为多继承的方式即可：

#ifndef ADAPTER_H
#define ADAPTER_H

#include "target.h"
#include "adaptee.h"

	// 电源适配器
class PowerAdapter : public IRussiaSocket, OwnCharger
{
public:
	PowerAdapter() {}
	void Charge() {
		// 使用自带的充电器（两脚扁型）充电
		ChargeWithFeetFlat();
	}
};

#endif // ADAPTER_H

//	除此之外，其他用法和“对象适配器”一致。