#pragma once

// ����ʵ��
// 	��������¼
// 	��Խ��ĳһʱ�̣����ʱ��ָ���������ʱ�䣬�� DateTime ��ʾ����Ϊ���ṩ��Ӧ�� setter �� getter ������

	// memento.h
#ifndef MEMENTO_H
#define MEMENTO_H

#include <iostream>
#include <string>

	// ����ʱ��
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

// 	����������
// 	Life ���ڴ��� DateTime���Լ�¼��ǰ������ʱ�䣬������ʹ�� DateTime ���лָ���

	// originator.h
#ifndef ORIGINATOR_H
#define ORIGINATOR_H

//#include "memento.h"
#include <iostream>
#include <string>

	// һ��
class Life
{
public:
	void SetDateTime(std::string dt) {
		std::cout << "Set date time to " << dt << std::endl;
		m_dateTime = dt;
	}

	// �����ڴ�ӡ
	std::string GetDateTime() {
		return m_dateTime;
	}

	// �ָ�����ʱ��
	void SetMemento(DateTime *dt) {
		m_dateTime = dt->GetDateTime();
	}

	// ��������ʱ��
	DateTime *CreateMemento() {
		return new DateTime(m_dateTime);
	}

private:
	std::string m_dateTime;
};

#endif // ORIGINATOR_H

// 	����������
// 	����ʱ�⵹���Ĺؼ���ͨ�� PandoraBox�����𱦲ſ����ֲ��ź���

	// care_taker.h
#ifndef CARE_TAKER_H
#define CARE_TAKER_H

//#include "originator.h"
#include <iostream>
#include <vector>

	// �¹ⱦ��
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

	// ���汸��
	void Save() {
		std::cout << "Save ..." << std::endl;;
		m_history.push_back(m_pLife->CreateMemento());
	}

	// ��Խ����һʱ��
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

// 	�����ͻ���
// 	���������¹ⱦ�С�������һ�Ѵ�Խ�ĸо������������Ǿ��������ĵġ���b����r�������ۡ���

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

	// ���ò�����һ����ʷʱ��
	life->SetDateTime("2000/10/01 00:00:00");
	box->Save();

	// ���ò�����һ����ʷʱ��
	life->SetDateTime("2010/10/01 00:00:00");
	box->Save();

	// ����һ����ʷʱ��
	life->SetDateTime("2018/10/01 00:00:00");

	// ��Խ
	box->Undo();
	std::cout << "Actual date time is " << life->GetDateTime() << std::endl;

	// �ٴδ�Խ
	box->Undo();
	std::cout << "Actual date time is " << life->GetDateTime() << std::endl;

	SAFE_DELETE(life);
	SAFE_DELETE(box);

	getchar();

	return 0;
}
/*
	������£�

	Set date time to 2000/10/01 00:00:00 
	Save �� 
	Set date time to 2010/10/01 00:00:00 
	Save �� 
	Set date time to 2018/10/01 00:00:00 
	Undo �� 
	Actual date time is 2010/10/01 00:00:00 
	Undo �� 
	Actual date time is 2000/10/01 00:00:00
	*/