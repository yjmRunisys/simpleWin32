#pragma once
// ��������
// 
// 	���� - ����ʡ ֻΪƷ������
// 	JD
// 	��ǰ�����ǹ�����Ҫȥ���С��ٻ��̵ꡢũó���еȡ���������֮��Խ��Խ�����ϲ���������㲻����������Ե��ܶ�ö�����
// 	����ͳģʽ�������кܶ�ô���
// 	���㡢��ݣ���ʡʱ��ͷ��á�
// 	������Ϣ͸���������˽����������ȡ�
// 	������ƷӦ�о��У����Էǳ�����ػ������ҡ�
// 	����֮�⣬�ܶ������̳ǻ����ϸ���ֻ��˫ 11��˫ 12�����졢Ԫ�������ڣ����ֻ���Ӧ�о��С�����
// 	�񾩶����Ա�������ѷ��Щ����ƽ̨���ͻ���ѡ��ϲ���ı�����Ȼ����н��㡣�����Ĺ����У����ǲ��������Щ��վ��������������ע��ֻ�����ǣ����궩���󣬽�����һ��ʱ����ջ�����ʵ����Ļ�����񱻷ַ�����ͬ����ϵͳ�������Ŷӡ���Ӧ�̡����Ա��ȥ��ɣ�Ϊ�˷��㣬���Խ��ж������٣�
// 	�¶��� �C> ������֤ �C> ��� �C> ���� �C> ���� �C> ����
// 	PS�� ˵���ٶȣ��Ͳ��ò��佱�����ˣ������ܸ����������µ��������ʹ����
// 	����ʵ��
// 	������ϵͳ
// 	��ϵͳ���� 3 ���������Ŷӣ�ȷ�ϸ����ϵ��Ӧ�̣�����Ӧ�̣�ȷ�Ͽ�桢��װ����ϵ��ݣ������Ա��������Ա�����Ͱ�������

	// sub_system.h
#ifndef SUB_SYSTEM_H
#define SUB_SYSTEM_H

#include <iostream>
#include <string>
#include <windows.h>

const std::string c_stateToStrCourier[] = { "�յ�", "��֤�ɴ���", "������Ա", "���Ͱ���", "��ȡ����ȷ��", "���" };
const std::string c_stateToStrVendor[] = { "�յ�", "ȷ�Ͽ��", "�Ӳֿ�õ���Ʒ", "��װ", "��ϵ���Ա", "���" };
const std::string c_stateToStrOrderTeam[] = { "�յ�", "ȷ�ϸ���", "��ϵ��Ӧ��", "���" };
const int c_nMsec = 300;  // ����ʱ�䣨���룩 - Sleep(c_nMsec) �������滻ΪһЩ���õĴ���

// �����Ŷ�
class OrderTeam
{
public:
	void submitRequest() {
		m_nState = 0;
	}

	// ���״̬
	bool checkStatus() {
		std::cout << "�����Ŷ� - ��ǰ״̬��" << c_stateToStrOrderTeam[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}

private:
	enum States {
		Received,  // �յ�
		VerifyPayment,  // ȷ�ϸ���
		ContactVendor,  // ��ϵ��Ӧ��
		Complete  // ���
	};
	int m_nState;
};

// ��Ӧ��
class Vendor
{
public:
	void submitRequest() {
		m_nState = 0;
	}

	// ���״̬
	bool checkStatus() {
		std::cout << "��Ӧ�� - ��ǰ״̬��" << c_stateToStrVendor[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}

private:
	enum States {
		Received,  // �յ�
		VerifyInventory,  // ȷ�Ͽ��
		GetItemFromWareHouse,  // �Ӳֿ�õ���Ʒ
		PackItem,  // ��װ
		ContactCourier,  // ��ϵ���Ա
		Complete  // ���
	};
	int m_nState;
};

// ���Ա
class Courier
{
public:
	// ������ת�������Ա
	void submitRequest() {
		m_nState = 0;
	}

	// ���״̬
	bool checkStatus() {
		std::cout << "���Ա - ��ǰ״̬��" << c_stateToStrCourier[m_nState] << std::endl;

		Sleep(c_nMsec);
		m_nState++;

		return (m_nState == Complete);
	}

private:
	enum States {
		Received,  // �յ�
		VerifyReachbility,  // ��֤�ɴ���
		AssignPerson,  // ������Ա
		DispatchPackage,  // ���Ͱ���
		GetDeliveryConfirmation,  // ��ȡ����ȷ��
		Complete  // ���
	};
	int m_nState;
};

#endif // SUB_SYSTEM_H

// 	�������
// 	�������Ϲ������ۣ��ṩ�˱�¶���ͻ��Ľӿڣ���Ȼ���Ը��ٶ���������Ȼ���ر���ĸ��ӹ��̡�

	// facade.h
#ifndef FACADE_H
#define FACADE_H

//#include "sub_system.h"

	// �������
class OnlineShoppingFacade
{
public:
	OnlineShoppingFacade() {
		m_nCount = 0;
	}

	// ���ظ��ٴ���
	int followupNum() {
		return m_nCount;
	}

	// �ύ����
	void submitRequest() {
		m_nState = 0;
	}

	// ���ٶ���
	bool checkStatus(){
		// �յ���������
		switch (m_nState) {
		case Received:
			m_nState++;
			// ������ת���������Ŷ�
			m_order.submitRequest();
			std::cout << "********** �ύ�������Ŷӣ����ٴ�����" << m_nCount << " **********" << std::endl;
			break;
		case SubmittedToOrderTeam:
			// ��������Ŷ������֤������Ӧ�̷�������
			if (m_order.checkStatus()) {
				m_nState++;
				m_vendor.submitRequest();
				std::cout << "********** �ύ����Ӧ�̣����ٴ�����" << m_nCount << " **********" << std::endl;
			}
			break;
		case SubmittedToVendor:
			// �����Ӧ���ѽ��������������ת�������Ա
			if (m_vendor.checkStatus()) {
				m_nState++;
				m_courier.submitRequest();
				std::cout << "********** �ύ�����Ա�����ٴ�����" << m_nCount << " **********" << std::endl;
			}
			break;
		case SubmittedToCourier:
			// ��������������������
			if (m_courier.checkStatus())
				return true;
		default:
			break;
		}

		m_nCount++;

		// ����δ���
		return false;
	}

private:
	enum States {
		Received,  // �յ�
		SubmittedToOrderTeam,  // �ύ�������Ŷ�
		SubmittedToVendor,  // �ύ����Ӧ��
		SubmittedToCourier  // �ύ�����Ա
	};

	int m_nState;  // ����״̬
	int m_nCount;  // ���ٴ���

	OrderTeam m_order;
	Vendor m_vendor;
	Courier m_courier;
};

#endif // FACADE_H

// 	�����ͻ���
// 	���գ��ͻ���ʵ�����£�

	// main.cpp
//#include "facade.h"

int testFacade()
{
	OnlineShoppingFacade facade;

	// �ύ����
	facade.submitRequest();

	// ���ٶ�����ֱ���������
	while (!facade.checkStatus());

	std::cout << "********** ������ɣ����ٴ�����" << facade.followupNum() << " **********" << std::endl;

	getchar();

	return 0;
}

// 	������£�
	// 
	// 	********** �ύ�������Ŷӣ����ٴ�����0 ********** 
	// 	�����Ŷ� - ��ǰ״̬���յ� 
	// 	�����Ŷ� - ��ǰ״̬��ȷ�ϸ��� 
	// 	�����Ŷ� - ��ǰ״̬����ϵ��Ӧ�� 
	// 	********** �ύ����Ӧ�̣����ٴ�����3 ********** 
	// 	��Ӧ�� - ��ǰ״̬���յ� 
	// 	��Ӧ�� - ��ǰ״̬��ȷ�Ͽ�� 
	// 	��Ӧ�� - ��ǰ״̬���Ӳֿ�õ���Ʒ 
	// 	��Ӧ�� - ��ǰ״̬����װ 
	// 	��Ӧ�� - ��ǰ״̬����ϵ���Ա 
	// 	********** �ύ�����Ա�����ٴ�����8 ********** 
	// 	���Ա - ��ǰ״̬���յ� 
	// 	���Ա - ��ǰ״̬����֤�ɴ��� 
	// 	���Ա - ��ǰ״̬��������Ա 
	// 	���Ա - ��ǰ״̬�����Ͱ��� 
	// 	���Ա - ��ǰ״̬����ȡ����ȷ�� 
	// 	********** ������ɣ����ٴ�����13 **********