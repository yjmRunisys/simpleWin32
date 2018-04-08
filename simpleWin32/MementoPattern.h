#pragma once

// 代码实现
// 	创建备忘录
// 	穿越至某一时刻，这个时刻指具体的日期时间，用 DateTime 表示，并为其提供相应的 setter 和 getter 方法：

	// memento.h
#ifndef MEMENTO_H
#define MEMENTO_H

#include <iostream>
#include <string>

	// 日期时间
class DateTime
{
public:
	DateTime(std::string dt)
		: m_dateTime(dt) {}

	void SetDateTime(std::string dt) {
		m_dateTime = dt;
	}

	std::string GetDateTime() {
		return m_dateTime;
	}

private:
	std::string m_dateTime;
};

#endif // MEMENTO_H

// 	创建发起人
// 	Life 用于创建 DateTime，以记录当前的日期时间，并可以使用 DateTime 进行恢复：

	// originator.h
#ifndef ORIGINATOR_H
#define ORIGINATOR_H

//#include "memento.h"
#include <iostream>
#include <string>

	// 一生
class Life
{
public:
	void SetDateTime(std::string dt) {
		std::cout << "Set date time to " << dt << std::endl;
		m_dateTime = dt;
	}

	// 仅用于打印
	std::string GetDateTime() {
		return m_dateTime;
	}

	// 恢复日期时间
	void SetMemento(DateTime *dt) {
		m_dateTime = dt->GetDateTime();
	}

	// 创建日期时间
	DateTime *CreateMemento() {
		return new DateTime(m_dateTime);
	}

private:
	std::string m_dateTime;
};

#endif // ORIGINATOR_H

// 	创建管理者
// 	这是时光倒流的关键，通过 PandoraBox，至尊宝才可以弥补遗憾：

	// care_taker.h
#ifndef CARE_TAKER_H
#define CARE_TAKER_H

//#include "originator.h"
#include <iostream>
#include <vector>

	// 月光宝盒
class PandoraBox
{
public:
	PandoraBox(Life *life)
		: m_pLife(life) {}

	~PandoraBox() {
		for (int i = 0; i < m_history.size(); i++) {
			delete m_history.at(i);
		}
		m_history.clear();
	}

	// 保存备份
	void Save() {
		std::cout << "Save ..." << std::endl;;
		m_history.push_back(m_pLife->CreateMemento());
	}

	// 穿越至上一时刻
	void Undo() {
		std::cout << "Undo ..." << std::endl;;
		m_pLife->SetMemento(m_history.back());
		m_history.pop_back();
	}

private:
	Life *m_pLife;
	std::vector<DateTime *> m_history;
};

#endif // CARE_TAKER_H

// 	创建客户端
// 	想启动“月光宝盒”，体验一把穿越的感觉？大声喊出那句烂熟于心的“般bō若rě波罗蜜”：

	// main.cpp
//#include "originator.h"
//#include "care_taker.h"

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

int testMementoPattern()
{
	Life *life = new Life();
	PandoraBox *box = new PandoraBox(life);

	// 设置并保存一个历史时间
	life->SetDateTime("2000/10/01 00:00:00");
	box->Save();

	// 设置并保存一个历史时间
	life->SetDateTime("2010/10/01 00:00:00");
	box->Save();

	// 设置一个历史时间
	life->SetDateTime("2018/10/01 00:00:00");

	// 穿越
	box->Undo();
	std::cout << "Actual date time is " << life->GetDateTime() << std::endl;

	// 再次穿越
	box->Undo();
	std::cout << "Actual date time is " << life->GetDateTime() << std::endl;

	SAFE_DELETE(life);
	SAFE_DELETE(box);

	getchar();

	return 0;
}
/*
	输出如下：

	Set date time to 2000/10/01 00:00:00 
	Save … 
	Set date time to 2010/10/01 00:00:00 
	Save … 
	Set date time to 2018/10/01 00:00:00 
	Undo … 
	Actual date time is 2010/10/01 00:00:00 
	Undo … 
	Actual date time is 2000/10/01 00:00:00
	*/