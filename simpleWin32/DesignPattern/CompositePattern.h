#pragma once
//Component为递归调用，可获取子节点，且子节点为向量
//主要子节点在递归中删除

// 案例分析
// 
// 	只要有人的地方就有恩怨，有恩怨就会有江湖，人就是江湖！ 
// 	– 金庸《笑傲江湖》
// 	Swordsman
// 	江湖公司由任我行一手创建，理所当然，他就是董事长。
// 	下设总经理一职，原本让令狐冲担任，却被婉拒，所以只能由自己兼任。
// 	再往下就是各事业部：日月神教、五岳剑派、以及其他门派等。
// 	日月神教的头儿叫做教主（东方不败），底下有光明左右使、十大长老、堂主、舵主、香主等。
// 	五岳剑派的头儿叫做盟主（左冷蝉），各派分别为：嵩山（左冷蝉）、泰山（天门道长）、衡山（莫大）、
// 	华山（岳不群）、恒山（定闲师太），各头目被称为掌门。
// 	另外，还有一些很 NB 的部门，不仅历史悠久，而且威望超高，是武林中的泰山北斗：少林（方证大师）、武当（冲虚道长）。。。

// 	代码实现
// 	透明组合模式
// 	创建抽象构件
// 
// 	Component 需要定义访问及管理子构件的接口：

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
	virtual void Add(Component *cmpt) = 0;  // 添加构件
	virtual void Remove(Component *cmpt) = 0;  // 删除构件
	virtual Component* GetChild(int index) = 0;  // 获取构件
	virtual void Operation(int indent) = 0;  // 显示构件（以缩进的方式）

private:
	Component();  // 不允许

protected:
	string m_strName;
};

#endif // COMPONENT_H

// 	创建叶子构件
// 
// 	作为 Component 的子类，Leaf 需要实现 Component 中定义的所有接口，但是 Leaf 不能包含子构件。
// 	因此，在 Leaf 中实现访问和管理子构件的函数时，需要进行异常处理或错误提示。 当然，这无疑会给 Leaf 的实现带来麻烦。

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
	Leaf();  // 不允许
};

#endif // LEAF_H

// 	创建容器构件
// 	由于容器构件中可以包含子节点，因此对容器构件进行处理时可以使用递归方式。

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
	// 递归显示
	void Operation(int indent) 
	{
		string newStr(indent, '-');
		cout << newStr << "+ " << m_strName << endl;
		// 显示每个节点的孩子
		vector<Component*>::iterator it = m_elements.begin();
		while (it != m_elements.end()) 
		{
			(*it)->Operation(indent + 2);
			++it;
		}
	}

private:
	Composite();  // 不允许

private:
	vector<Component *> m_elements;
};

#endif // COMPOSITE_H

// 	创建客户端
// 	最终，来看看任大教主的组织结构：

// main.cpp
//#include "composite.h"
//#include "leaf.h"

int testComposite()
{
	// 创建一个树形结构
	// 创建根节点
	Component *pRoot = new Composite("江湖公司（任我行）");

	// 创建分支
	Component *pDepart1 = new Composite("日月神教（东方不败）");
	pDepart1->Add(new Leaf("光明左使（向问天）"));
	pDepart1->Add(new Leaf("光明右使（曲洋）"));
	pRoot->Add(pDepart1);

	Component *pDepart2 = new Composite("五岳剑派（左冷蝉）");
	pDepart2->Add(new Leaf("嵩山（左冷蝉）"));
	pDepart2->Add(new Leaf("衡山（莫大）"));
	pDepart2->Add(new Leaf("华山（岳不群）"));
	pDepart2->Add(new Leaf("泰山（天门道长）"));
	pDepart2->Add(new Leaf("恒山（定闲师太）"));
	pRoot->Add(pDepart2);

	// 添加和删除叶子
	pRoot->Add(new Leaf("少林（方证大师）"));
	pRoot->Add(new Leaf("武当（冲虚道长）"));
	Component *pLeaf = new Leaf("青城（余沧海）");
	pRoot->Add(pLeaf);

	// 小丑，直接裁掉
	pRoot->Remove(pLeaf);

	// 递归地显示组织架构
	pRoot->Operation(1);

	// 删除分配的内存
	SAFE_DELETE(pRoot);

	getchar();

	return 0;
}

// 	输出如下：
// 
// 	-+ 江湖公司（任我行） 
// 	—+ 日月神教（东方不败） 
// 	—– 光明左使（向问天） 
// 	—– 光明右使（曲洋） 
// 	—+ 五岳剑派（左冷蝉） 
// 	—– 嵩山（左冷蝉） 
// 	—– 衡山（莫大） 
// 	—– 华山（岳不群） 
// 	—– 泰山（天门道长） 
// 	—– 恒山（定闲师太） 
// 	— 少林（方证大师） 
// 	— 武当（冲虚道长）


// 	安全组合模式
// 
// 	创建抽象构件

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
	virtual void Operation(int indent) = 0;  // 显示构件（以缩进的方式）

private:
	Component();  // 不允许

protected:
	string m_strName;
};

#endif // COMPONENT_H

//	创建叶子构件

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
	Leaf();  // 不允许
};

#endif // LEAF_H

//	注意： 与透明模式不同，这里已经没有了访问及管理子构件的接口，所有的接口都在 Composite 中，不再赘述（同上）。