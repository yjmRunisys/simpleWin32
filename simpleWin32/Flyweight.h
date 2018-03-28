// flyweight.h
#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#include <iostream>
#include <string>

//创建抽象享元类
// 玩家 - 有武器和使命
class IPlayer
{
public:
	virtual ~IPlayer() {}

	// 分配武器
	virtual void assignWeapon(std::string weapon) = 0;

	// 使命
	virtual void mission() = 0;

protected:
	std::string m_task; // 内部状态
	std::string m_weapon; // 外部状态
};

#endif // FLYWEIGHT_H

// concrete_flyweight.h
#ifndef CONCRETE_FLYWEIGHT_H
#define CONCRETE_FLYWEIGHT_H

//具体享元类有两个 - Terrorist、CounterTerrorist：

//#include "flyweight.h"

// 恐怖分子
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

// 反恐精英
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
//创建享元工厂 即享元池

//#include "concrete_flyweight.h"
#include <map>

// 用于获取玩家
class PlayerFactory
{
public:
	// 如果 T/CT 对象存在，则直接从享元池获取；否则，创建一个新对象并添加到享元池中，然后返回。
	static IPlayer* getPlayer(std::string type)
	{
		IPlayer *p = NULL;
		if (m_map.find(type) != m_map.end()) {
			p = m_map[type];
		}
		else {
			// 创建 T/CT 对象
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
			// 一旦创建，将其插入到 map 中
			m_map.insert(std::make_pair(type, p));
		}
		return p;
	}

private:
	// 存储 T/CT 对象（享元池）
	static std::map<std::string, IPlayer*> m_map;//实例对象需要初始化

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
	// 玩家类型和武器
	static std::string s_playerType[2] = { "T", "CT" };
	static std::string s_weapons[4] = { "AK-47", "Maverick", "Gut Knife", "Desert Eagle" };

	srand((unsigned)time(NULL));

	int playerLen;//玩家个数
	int weaponsLen;//武器个数
	GET_ARRAY_LEN(s_playerType, playerLen);
	GET_ARRAY_LEN(s_weapons, weaponsLen);

	// 假设，游戏中有十位玩家
	for (int i = 0; i < 10; i++) {
		// 获取随机玩家和武器
		int typeIndex = rand() % playerLen;
		int weaponIndex = rand() % weaponsLen;
		std::string type = s_playerType[typeIndex];
		std::string weapon = s_weapons[weaponIndex];

		// 获取玩家
		IPlayer *p = PlayerFactory::getPlayer(type);

		// 从武器库中随机分配武器
		p->assignWeapon(weapon);

		// 派玩家去执行任务
		p->mission();
	}

	getchar();
}

