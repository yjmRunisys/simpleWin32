#pragma once

/************************************************************************/
/* 创建访问者

访问者需要为每个景点都提供一个访问方法                                                                     */
/************************************************************************/

// visitor.h
#ifndef VISITOR_H
#define VISITOR_H

class BellTower;//大雁塔
class TerracottaWarriors;//兵马俑

// 访问者
class IVisitor
{
public:
	virtual ~IVisitor() {}
	virtual void Visit(BellTower *) = 0;
	virtual void Visit(TerracottaWarriors *) = 0;
};

#endif // VISITOR_H
/************************************************************************/
/* 创建具体访问者

具体访问者有两种 - 游客、清洁工，它们分别实现了不同的访问操作（游客只管吃喝玩乐，清洁工负责清理垃圾）                                                                     */
/************************************************************************/
// concrete_visitor.h
#ifndef CONCRETE_VISITOR_H
#define CONCRETE_VISITOR_H

//#include "visitor.h"
//#include "concrete_element.h"

// 游客
class Tourist : public IVisitor
{
public:
	virtual void Visit(BellTower *) override {
		std::cout << "I'm visiting the Bell Tower!" << std::endl;
	}

	virtual void Visit(TerracottaWarriors *) override {
		std::cout << "I'm visiting the Terracotta Warriors!" << std::endl;
	}
};

// 清洁工
class Cleaner : public IVisitor
{
public:
	virtual void Visit(BellTower *) override {
		std::cout << "I'm cleaning up the garbage of Bell Tower!" << std::endl;
	}

	virtual void Visit(TerracottaWarriors *) override {
		std::cout << "I'm cleaning up the garbage of Terracotta Warriors!" << std::endl;
	}
};

#endif // CONCRETE_VISITOR_H

/************************************************************************/
/* 创建元素

景点中定义了一个 Accept() 接口，用于接受访问者的访问：                                                                     */
/************************************************************************/
// element.h
#ifndef ELEMENT_H
#define ELEMENT_H

class IVisitor;

// 地方
class IPlace
{
public:
	virtual ~IPlace() {}
	virtual void Accept(IVisitor *visitor) = 0;
};

#endif // ELEMENT_H

/************************************************************************/
/* 创建具体元素

具体元素有两个 - 钟楼、兵马俑，它们实现了 Accept() 方法：  

注意： 在 Accept() 方法中，通过调用 Visitor 的 visit() 方法（以当前对象为参数）来实现对景点的访问。*/
/************************************************************************/

// concrete_element.h
#ifndef CONCRETE_ELEMENT_H
#define CONCRETE_ELEMENT_H

//#include "element.h"
//#include "visitor.h"
#include <iostream>

// 钟楼
class BellTower : public IPlace
{
public:
	virtual void Accept(IVisitor *visitor) override {
		std::cout << "Bell Tower is accepting visitor." << std::endl;
		visitor->Visit(this);
	}
};

// 兵马俑
class TerracottaWarriors : public IPlace
{
public:
	virtual void Accept(IVisitor *visitor) override {
		std::cout << "Terracotta Warriors is accepting visitor." << std::endl;
		visitor->Visit(this);
	}
};

#endif // CONCRETE_ELEMENT_H

/************************************************************************/
/* 创建对象结构

添加景点，并为每一个景点添加访问者：                                                                     */
/************************************************************************/

// object_structure.h
#ifndef OBJECT_STRUCTURE_H
#define OBJECT_STRUCTURE_H

//#include "element.h"
#include <list>

// 城市（西安）
class City
{
public:
	void Attach(IPlace *place) {
		m_places.push_back(place);
	}

	void Detach(IPlace *place) {
		m_places.remove(place);
	}

	void Accept(IVisitor *visitor) {
		// 为每一个 element 设置 visitor，进行对应的操作
		for (std::list<IPlace*>::iterator it = m_places.begin(); it != m_places.end(); ++it) {
			(*it)->Accept(visitor);
		}
	}

private:
	std::list<IPlace *> m_places;
};

#endif // OBJECT_STRUCTURE_H

/************************************************************************/
/* 创建客户端

欢迎来到古城西安，开始访问之旅吧：                                                                     */
/************************************************************************/

// main.cpp
//#include "concrete_visitor.h"
//#include "object_structure.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testVisitor()
{
	City *city = new City();

	// 景点 - 钟楼、兵马俑
	IPlace *bellTower = new BellTower();
	IPlace *warriors = new TerracottaWarriors();

	// 访问者 - 游客、清洁工
	IVisitor *tourist = new Tourist();
	IVisitor *cleaner = new Cleaner();

	// 添加景点
	city->Attach(bellTower);
	city->Attach(warriors);

	// 接受访问
	city->Accept(tourist);
	city->Accept(cleaner);

	SAFE_DELETE(cleaner);
	SAFE_DELETE(tourist);
	SAFE_DELETE(warriors);
	SAFE_DELETE(bellTower);
	SAFE_DELETE(city);

	getchar();

	return 0;
}