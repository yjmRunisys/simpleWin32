#pragma once
//ComponentΪ�ݹ���ã��ɻ�ȡ�ӽڵ㣬���ӽڵ�Ϊ����
//��Ҫ�ӽڵ��ڵݹ���ɾ��

// ��������
// 
// 	ֻҪ���˵ĵط����ж�Թ���ж�Թ�ͻ��н������˾��ǽ����� 
// 	�C ��ӹ��Ц��������
// 	Swordsman
// 	������˾��������һ�ִ�����������Ȼ�������Ƕ��³���
// 	�����ܾ���һְ��ԭ��������嵣�Σ�ȴ����ܣ�����ֻ�����Լ����Ρ�
// 	�����¾��Ǹ���ҵ����������̡��������ɡ��Լ��������ɵȡ�
// 	������̵�ͷ�������������������ܣ��������й�������ʹ��ʮ���ϡ������������������ȡ�
// 	�������ɵ�ͷ������������������������ɷֱ�Ϊ����ɽ�����������̩ɽ�����ŵ���������ɽ��Ī�󣩡�
// 	��ɽ������Ⱥ������ɽ������ʦ̫������ͷĿ����Ϊ���š�
// 	���⣬����һЩ�� NB �Ĳ��ţ�������ʷ�ƾã������������ߣ��������е�̩ɽ���������֣���֤��ʦ�����䵱�����������������

// 	����ʵ��
// 	͸�����ģʽ
// 	�������󹹼�
// 
// 	Component ��Ҫ������ʼ������ӹ����Ľӿڣ�

	// component.h
#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <string>

using namespace std;

class Component
{
public:
	Component(string name) : m_strName(name) {}
	virtual ~Component() {}
	virtual void Add(Component *cmpt) = 0;  // ��ӹ���
	virtual void Remove(Component *cmpt) = 0;  // ɾ������
	virtual Component* GetChild(int index) = 0;  // ��ȡ����
	virtual void Operation(int indent) = 0;  // ��ʾ�������������ķ�ʽ��

private:
	Component();  // ������

protected:
	string m_strName;
};

#endif // COMPONENT_H

// 	����Ҷ�ӹ���
// 
// 	��Ϊ Component �����࣬Leaf ��Ҫʵ�� Component �ж�������нӿڣ����� Leaf ���ܰ����ӹ�����
// 	��ˣ��� Leaf ��ʵ�ַ��ʺ͹����ӹ����ĺ���ʱ����Ҫ�����쳣����������ʾ�� ��Ȼ�������ɻ�� Leaf ��ʵ�ִ����鷳��

// leaf.h
#ifndef LEAF_H
#define LEAF_H

//#include "component.h"

class Leaf : public Component
{
public:
	Leaf(string name) : Component(name){}
	virtual ~Leaf(){}
	void Add(Component *cmpt) {
		cout << "Can't add to a Leaf" << endl;
	}
	void Remove(Component *cmpt) {
		cout << "Can't remove from a Leaf" << endl;
	}
	Component* GetChild(int index) {
		cout << "Can't get child from a Leaf" << endl;
		return NULL;
	}
	void Operation(int indent) {
		string newStr(indent, '-');
		cout << newStr << " " << m_strName <<endl;
	}

private:
	Leaf();  // ������
};

#endif // LEAF_H

// 	������������
// 	�������������п��԰����ӽڵ㣬��˶������������д���ʱ����ʹ�õݹ鷽ʽ��

	// composite.h
#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>
//#include "component.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

class Composite : public Component
{
public:
	Composite (string name) : Component(name) {}
	virtual ~Composite() {
		while (!m_elements.empty()) 
		{
			vector<Component*>::iterator it = m_elements.begin();
			SAFE_DELETE(*it);
			m_elements.erase(it);
		}
	}
	void Add(Component *cmpt) 
	{
		m_elements.push_back(cmpt);
	}

	void Remove(Component *cmpt) 
	{
		vector<Component*>::iterator it = m_elements.begin();
		while (it != m_elements.end())  
		{
			if (*it == cmpt) {
				SAFE_DELETE(cmpt);
				m_elements.erase(it);
				break;
			}
			++it;
		}
	}
	Component* GetChild(int index) 
	{
		if (index >= (int)m_elements.size())
			return NULL;

		return m_elements[index];
	}
	// �ݹ���ʾ
	void Operation(int indent) 
	{
		string newStr(indent, '-');
		cout << newStr << "+ " << m_strName << endl;
		// ��ʾÿ���ڵ�ĺ���
		vector<Component*>::iterator it = m_elements.begin();
		while (it != m_elements.end()) 
		{
			(*it)->Operation(indent + 2);
			++it;
		}
	}

private:
	Composite();  // ������

private:
	vector<Component *> m_elements;
};

#endif // COMPOSITE_H

// 	�����ͻ���
// 	���գ��������δ��������֯�ṹ��

// main.cpp
//#include "composite.h"
//#include "leaf.h"

int testComposite()
{
	// ����һ�����νṹ
	// �������ڵ�
	Component *pRoot = new Composite("������˾�������У�");

	// ������֧
	Component *pDepart1 = new Composite("������̣��������ܣ�");
	pDepart1->Add(new Leaf("������ʹ�������죩"));
	pDepart1->Add(new Leaf("������ʹ������"));
	pRoot->Add(pDepart1);

	Component *pDepart2 = new Composite("�������ɣ��������");
	pDepart2->Add(new Leaf("��ɽ���������"));
	pDepart2->Add(new Leaf("��ɽ��Ī��"));
	pDepart2->Add(new Leaf("��ɽ������Ⱥ��"));
	pDepart2->Add(new Leaf("̩ɽ�����ŵ�����"));
	pDepart2->Add(new Leaf("��ɽ������ʦ̫��"));
	pRoot->Add(pDepart2);

	// ��Ӻ�ɾ��Ҷ��
	pRoot->Add(new Leaf("���֣���֤��ʦ��"));
	pRoot->Add(new Leaf("�䵱�����������"));
	Component *pLeaf = new Leaf("��ǣ���׺���");
	pRoot->Add(pLeaf);

	// С��ֱ�Ӳõ�
	pRoot->Remove(pLeaf);

	// �ݹ����ʾ��֯�ܹ�
	pRoot->Operation(1);

	// ɾ��������ڴ�
	SAFE_DELETE(pRoot);

	getchar();

	return 0;
}

// 	������£�
// 
// 	-+ ������˾�������У� 
// 	��+ ������̣��������ܣ� 
// 	���C ������ʹ�������죩 
// 	���C ������ʹ������ 
// 	��+ �������ɣ�������� 
// 	���C ��ɽ��������� 
// 	���C ��ɽ��Ī�� 
// 	���C ��ɽ������Ⱥ�� 
// 	���C ̩ɽ�����ŵ����� 
// 	���C ��ɽ������ʦ̫�� 
// 	�� ���֣���֤��ʦ�� 
// 	�� �䵱�����������


// 	��ȫ���ģʽ
// 
// 	�������󹹼�

	// component.h
#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <string>

	using namespace std;

class Component
{
public:
	Component(string name) : m_strName(name) {}
	virtual ~Component() {}
	virtual void Operation(int indent) = 0;  // ��ʾ�������������ķ�ʽ��

private:
	Component();  // ������

protected:
	string m_strName;
};

#endif // COMPONENT_H

//	����Ҷ�ӹ���

	// leaf.h
#ifndef LEAF_H
#define LEAF_H

//#include "component.h"

class Leaf : public Component
{
public:
	Leaf(string name) : Component(name){}
	virtual ~Leaf(){}
	void Operation(int indent) {
		string newStr(indent, '-');
		cout << newStr << " " << m_strName <<endl;
	}

private:
	Leaf();  // ������
};

#endif // LEAF_H

//	ע�⣺ ��͸��ģʽ��ͬ�������Ѿ�û���˷��ʼ������ӹ����Ľӿڣ����еĽӿڶ��� Composite �У�����׸����ͬ�ϣ���