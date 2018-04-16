#pragma once

/************************************************************************/
/* ����������

��������ҪΪÿ�����㶼�ṩһ�����ʷ���                                                                     */
/************************************************************************/

// visitor.h
#ifndef VISITOR_H
#define VISITOR_H

class BellTower;//������
class TerracottaWarriors;//����ٸ

// ������
class IVisitor
{
public:
	virtual ~IVisitor() {}
	virtual void Visit(BellTower *) = 0;
	virtual void Visit(TerracottaWarriors *) = 0;
};

#endif // VISITOR_H
/************************************************************************/
/* �������������

��������������� - �ο͡���๤�����Ƿֱ�ʵ���˲�ͬ�ķ��ʲ������ο�ֻ�ܳԺ����֣���๤��������������                                                                     */
/************************************************************************/
// concrete_visitor.h
#ifndef CONCRETE_VISITOR_H
#define CONCRETE_VISITOR_H

//#include "visitor.h"
//#include "concrete_element.h"

// �ο�
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

// ��๤
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
/* ����Ԫ��

�����ж�����һ�� Accept() �ӿڣ����ڽ��ܷ����ߵķ��ʣ�                                                                     */
/************************************************************************/
// element.h
#ifndef ELEMENT_H
#define ELEMENT_H

class IVisitor;

// �ط�
class IPlace
{
public:
	virtual ~IPlace() {}
	virtual void Accept(IVisitor *visitor) = 0;
};

#endif // ELEMENT_H

/************************************************************************/
/* ��������Ԫ��

����Ԫ�������� - ��¥������ٸ������ʵ���� Accept() ������  

ע�⣺ �� Accept() �����У�ͨ������ Visitor �� visit() �������Ե�ǰ����Ϊ��������ʵ�ֶԾ���ķ��ʡ�*/
/************************************************************************/

// concrete_element.h
#ifndef CONCRETE_ELEMENT_H
#define CONCRETE_ELEMENT_H

//#include "element.h"
//#include "visitor.h"
#include <iostream>

// ��¥
class BellTower : public IPlace
{
public:
	virtual void Accept(IVisitor *visitor) override {
		std::cout << "Bell Tower is accepting visitor." << std::endl;
		visitor->Visit(this);
	}
};

// ����ٸ
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
/* ��������ṹ

��Ӿ��㣬��Ϊÿһ��������ӷ����ߣ�                                                                     */
/************************************************************************/

// object_structure.h
#ifndef OBJECT_STRUCTURE_H
#define OBJECT_STRUCTURE_H

//#include "element.h"
#include <list>

// ���У�������
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
		// Ϊÿһ�� element ���� visitor�����ж�Ӧ�Ĳ���
		for (std::list<IPlace*>::iterator it = m_places.begin(); it != m_places.end(); ++it) {
			(*it)->Accept(visitor);
		}
	}

private:
	std::list<IPlace *> m_places;
};

#endif // OBJECT_STRUCTURE_H

/************************************************************************/
/* �����ͻ���

��ӭ�����ų���������ʼ����֮�ðɣ�                                                                     */
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

	// ���� - ��¥������ٸ
	IPlace *bellTower = new BellTower();
	IPlace *warriors = new TerracottaWarriors();

	// ������ - �ο͡���๤
	IVisitor *tourist = new Tourist();
	IVisitor *cleaner = new Cleaner();

	// ��Ӿ���
	city->Attach(bellTower);
	city->Attach(warriors);

	// ���ܷ���
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