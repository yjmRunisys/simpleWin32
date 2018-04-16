// flyweight.h
#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#include <iostream>
#include <string>

//����������Ԫ��
// ��� - ��������ʹ��
class IPlayer
{
public:
	virtual ~IPlayer() {}

	// ��������
	virtual void assignWeapon(std::string weapon) = 0;

	// ʹ��
	virtual void mission() = 0;

protected:
	std::string m_task; // �ڲ�״̬
	std::string m_weapon; // �ⲿ״̬
};

#endif // FLYWEIGHT_H

// concrete_flyweight.h
#ifndef CONCRETE_FLYWEIGHT_H
#define CONCRETE_FLYWEIGHT_H

//������Ԫ�������� - Terrorist��CounterTerrorist��

//#include "flyweight.h"

// �ֲ�����
class Terrorist : public IPlayer
{
public:
	Terrorist() {
		m_task = "Plant a bomb";
	}

	virtual void assignWeapon(std::string weapon) override {
		m_weapon = weapon;
	}

	virtual void mission() override {
		std::cout << "Terrorist with weapon " + m_weapon + "," + " Task is " + m_task << std::endl;
	}
};

// ���־�Ӣ
class CounterTerrorist : public IPlayer
{
public:
	CounterTerrorist() {
		m_task = "Diffuse bomb";
	}

	virtual void assignWeapon(std::string weapon) override {
		m_weapon = weapon;
	}

	virtual void mission() override {
		std::cout << "Counter Terrorist with weapon " + m_weapon + "," + " Task is " + m_task << std::endl;
	}
};

#endif // CONCRETE_FLYWEIGHT_H

// flyweight_factory.h
#ifndef FLYWEIGHT_FACTORY_H
#define FLYWEIGHT_FACTORY_H
//������Ԫ���� ����Ԫ��

//#include "concrete_flyweight.h"
#include <map>

// ���ڻ�ȡ���
class PlayerFactory
{
public:
	// ��� T/CT ������ڣ���ֱ�Ӵ���Ԫ�ػ�ȡ�����򣬴���һ���¶�����ӵ���Ԫ���У�Ȼ�󷵻ء�
	static IPlayer* getPlayer(std::string type)
	{
		IPlayer *p = NULL;
		if (m_map.find(type) != m_map.end()) {
			p = m_map[type];
		}
		else {
			// ���� T/CT ����
			if (type == "T") {
				std::cout << "Terrorist Created" << std::endl;
				p = new Terrorist();
			}
			else if (type == "CT") {
				std::cout << "Counter Terrorist Created" << std::endl;
				p = new CounterTerrorist();
			}
			else {
				std::cout << "Unreachable code!" << std::endl;
			}
			// һ��������������뵽 map ��
			m_map.insert(std::make_pair(type, p));
		}
		return p;
	}

private:
	// �洢 T/CT ������Ԫ�أ�
	static std::map<std::string, IPlayer*> m_map;//ʵ��������Ҫ��ʼ��

	class CGarbage{
		public:
			~CGarbage()
			{
				int isize = m_map.size();
				if (isize > 1)
				{
					std::map<std::string, IPlayer*>::iterator p = m_map.begin();
					for(;p!= m_map.end();p++)
					{
						delete p->second;
					}
					
				}

				OutputDebugString("garbage out");
				
			}

	};

	static CGarbage garbage;
};


PlayerFactory::CGarbage PlayerFactory::garbage;
std::map<std::string, IPlayer*> PlayerFactory::m_map = std::map<std::string, IPlayer*>();


#endif // FLYWEIGHT_FACTORY_H

#include <ctime>

#define GET_ARRAY_LEN(array, len) {len = (sizeof(array) / sizeof(array[0]));}

void testFlyweight()
{
	// ������ͺ�����
	static std::string s_playerType[2] = { "T", "CT" };
	static std::string s_weapons[4] = { "AK-47", "Maverick", "Gut Knife", "Desert Eagle" };

	srand((unsigned)time(NULL));

	int playerLen;//��Ҹ���
	int weaponsLen;//��������
	GET_ARRAY_LEN(s_playerType, playerLen);
	GET_ARRAY_LEN(s_weapons, weaponsLen);

	// ���裬��Ϸ����ʮλ���
	for (int i = 0; i < 10; i++) {
		// ��ȡ�����Һ�����
		int typeIndex = rand() % playerLen;
		int weaponIndex = rand() % weaponsLen;
		std::string type = s_playerType[typeIndex];
		std::string weapon = s_weapons[weaponIndex];

		// ��ȡ���
		IPlayer *p = PlayerFactory::getPlayer(type);

		// ���������������������
		p->assignWeapon(weapon);

		// �����ȥִ������
		p->mission();
	}

	getchar();
}

