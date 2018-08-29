#pragma once
#include "stdafx.h"
#include "time.h"
#include "TcpSocket.h"

#define DATA_LEN 8*1024*1024
#define TEST_TIMES 100000
#define TIME_MINIMNUM 5*60//���ٲ���300s
#define CONNECT_IP "192.168.0.150"
#define CONNECT_PORT 10150
#define LOCAL_IP "192.168.0.150"

void TestTcpServer()
{
	CTcpSocket mServer;
	std::string strIp = CONNECT_IP;
	unsigned short port = CONNECT_PORT;
	unsigned int len =DATA_LEN;
	int transMode = 1;
	mServer.InitServer(strIp,port,len,transMode);
	unsigned char *bufSend = new unsigned char[len];

	int iiTest = 0;
	double t0,t1;
	t0 = GetTickCount();
	t1 = t0;
	double tIni = t0;
	ULONG64 dwCount0 = 0;
	ULONG64 dwCount = 0;
	LONG64 sendSize;
	while (iiTest++ <=TEST_TIMES || (t1 - tIni)/1000 < TIME_MINIMNUM)
	{
		sendSize = mServer.Send(bufSend,len);
		if (sendSize > 0)
		{
			dwCount += sendSize;
			t1 = GetTickCount();
			if (t1 - t0 > 1000)
			{//���ʱ�����1000ms��ˢ��

				//��ʾ�ٶ�
				//ƽ���ٶ�
				//mbreceived = dwCount /(1024*1024.0);  //�ѽ��յ����ֽڣ���λΪMB
				//secs = (t1 - tIni)/1000.0;//�������
				//mbsec = mbreceived/ secs;

				//˲ʱ�ٶ�
				double mbreceived1 = (dwCount - dwCount0) /(1024*1024.0);  //�ѽ��յ����ֽڣ���λΪMB
				double mbsec =  mbreceived1 * 1000 / (t1 - t0);				

				//����ϵͳ״̬	
				double readRate1 = mbsec;	
				double timePlayOnce1 = (t1 - tIni)/1000.0;

				printf("�Ѳ���ʱ��%.3f s,����������%lld Byte,�ٶ� %.3f M/s\n",timePlayOnce1,dwCount,mbsec);

				//����ͳ����
				t0 = t1;
				dwCount0 = dwCount;
			}
		}

	}

	delete[] bufSend;
}

void TestTcpClient()
{
	CTcpSocket mClient;
	std::string strIp = CONNECT_IP;
	unsigned short port = CONNECT_PORT;
	unsigned int len =DATA_LEN;
	int transMode = 1;
	double speed = 1000;
	mClient.InitClient(strIp,port,len,speed,transMode,LOCAL_IP);
	unsigned char *bufRecv = new unsigned char[len];

	int iiTest = 0;
	double t0,t1;
	t0 = GetTickCount();
	t1 = t0;
	double tIni = t0;
	ULONG64 dwCount0 = 0;
	ULONG64 dwCount = 0;
	LONG64 recSize;
	while (iiTest++ <=TEST_TIMES || (t1 - tIni)/1000 < TIME_MINIMNUM)
	{
		recSize = mClient.Recv(bufRecv,len);
		if (recSize > 0)
		{
			dwCount += recSize;
			t1 = GetTickCount();
			if (t1 - t0 > 1000)
			{//���ʱ�����1000ms��ˢ��

				//��ʾ�ٶ�
				//ƽ���ٶ�
				//mbreceived = dwCount /(1024*1024.0);  //�ѽ��յ����ֽڣ���λΪMB
				//secs = (t1 - tIni)/1000.0;//�������
				//mbsec = mbreceived/ secs;

				//˲ʱ�ٶ�
				double mbreceived1 = (dwCount - dwCount0) /(1024*1024.0);  //�ѽ��յ����ֽڣ���λΪMB
				double mbsec =  mbreceived1 * 1000 / (t1 - t0);				

				//����ϵͳ״̬	
				double readRate1 = mbsec;	
				double timePlayOnce1 = (t1 - tIni)/1000.0;

				printf("�Ѳ���ʱ��%.3f s,����������%lld Byte,�ٶ� %.3f MB/s\n",timePlayOnce1,dwCount,mbsec);			

				//����ͳ����
				t0 = t1;
				dwCount0 = dwCount;
			}
		}


	}

	delete[] bufRecv;
}

int AbsoluteServer()
{
	WORD sockVersion = MAKEWORD(2,2);
	WSADATA data;
	if (WSAStartup(sockVersion,&data) != 0)
	{
		return 0;
	}

	SOCKET slisten = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("invalid socket!\n");
		return 0;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(CONNECT_PORT);
	serverAddr.sin_addr.S_un.S_addr = /*INADDR_ANY*/inet_addr(CONNECT_IP);
	if (bind(slisten,(LPSOCKADDR)&serverAddr,sizeof(serverAddr)) == SOCKET_ERROR)
	{
		printf("bind error,%d!\n",GetLastError());
		closesocket(slisten);
		return 0;
	}

	//��ʼ����
	if (listen(slisten,5) == SOCKET_ERROR)
	{
		printf("listen error!\n");
		return 0;
	}

	//ѭ����������
	SOCKET sclient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	printf("��ص�ַ��%s\n",CONNECT_IP);
	printf("��ض˿�:%d\n",CONNECT_PORT);
	while(true)
	{
		printf("�ȴ�����...\n");
		sclient = accept(slisten,(SOCKADDR*)&remoteAddr,&nAddrlen);
		if (sclient == INVALID_SOCKET)
		{
			printf("accept error!");
			continue;
		}
		printf("���ܵ�һ�����ӣ�%s\r\n",inet_ntoa(remoteAddr.sin_addr));

		//��������
		// 		char *sendData0 = new char[1024*1024];
		// 		for (int i = 0;i<100000000;i++)
		// 		{
		// 			send(sclient,sendData0,1024,0);
		// 		}
		// 		delete[] sendData0;

		//��������
		int ret = recv(sclient,revData,255,0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			printf(revData);
		}

		//��������
		char *sendData = "��ã�TCP�ͻ���!\n";
		send(sclient,sendData,strlen(sendData),0);
		Sleep(60000);
		closesocket(sclient);
	}	

	closesocket(slisten);
	WSACleanup();
	return 0;
}

int AbsoluteClient()
{
	// 	WORD sockVersion = MAKEWORD(2,2);
	// 	WSADATA data;
	// 	if (WSAStartup(sockVersion,&data) != 0)
	// 	{
	// 		return 0;
	// 	}
	if(!CTcpSocket::NetStartUp())
	{
		return 0;
	}

	SOCKET sclient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket!\n");
		return 0;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(CONNECT_PORT);
	serAddr.sin_addr.S_un.S_addr = inet_addr(CONNECT_IP);
	if (connect(sclient,(sockaddr *)&serAddr,sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("connect error!\n");
		closesocket(sclient);
		return 0;
	}
	char *sendData = "��ã�TCP�����������ǿͻ��ˣ�\n";
	send(sclient,sendData,strlen(sendData),0);

	char recData[255];
	int ret = recv(sclient,recData,255,0);
	if (ret > 0)
	{
		recData[ret] = 0x00;
		printf(recData);
	}

	closesocket(sclient);
	WSACleanup();
	return 0;
}

typedef unsigned short uint16_t;
typedef unsigned int uint32t;
typedef int		int32_t;

bool NoBlockClient(const string& _host, uint16_t _port, uint32t _timeout, int32_t& _sockfd)
{

	// �����ʼ��  
	WORD wVersionRequested;  
	WSADATA wsaData;  
	wVersionRequested = MAKEWORD(2, 2);  
	WSAStartup( wVersionRequested, &wsaData );  

	// �����ͻ���socket(Ĭ��Ϊ������socket)  
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);  

	// ����Ϊ��������socket  
	int iMode = 1;  
	ioctlsocket(sockClient, FIONBIO, (u_long FAR*)&iMode); 

	// ��������  
	SOCKADDR_IN addrSrv;  
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  
	addrSrv.sin_family = AF_INET;  
	addrSrv.sin_port = htons(8888); 


	// ��ʱʱ��  
	struct timeval tm;  
	tm.tv_sec  = 5; //5������ 
	tm.tv_usec = 0;  
	int ret = -1;  

	// ����ȥ���ӷ����  
	if (-1 != connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))  
	{  
		ret = 1; // ���ӳɹ�  
	}  
	else  
	{  
		fd_set set;  
		FD_ZERO(&set);  
		FD_SET(sockClient, &set);  

		if (select(-1, NULL, &set, NULL, &tm) <= 0)  
		{  
			ret = -1; // �д���(select������߳�ʱ)  
		}  
		else  
		{  
			int error = -1;  
			int optLen = sizeof(int);  
			getsockopt(sockClient, SOL_SOCKET, SO_ERROR, (char*)&error, &optLen);   

			// ֮��������ĳ���д����Ŀ���������ʽ�� ��Ϊ�˸�ֱ�ۣ� ����ע��  
			if (0 != error)  
			{  
				ret = -1; // �д���  
			}  
			else  
			{  
				ret = 1;  // �޴���  
			}  
		}  
	}  

	// ���Ϊ����socket  
	iMode = 0;  
	ioctlsocket(sockClient, FIONBIO, (u_long FAR*)&iMode); //����Ϊ����ģʽ 

	// connect״̬  
	printf("ret is %d\n", ret);  

	// �������ݵ�����˲�������  
	if(1 == ret)  
	{  
		send(sockClient, "hello world", strlen("hello world") + 1, 0);  
	}  

	// �ͷ���������  
	closesocket(sockClient);  
	WSACleanup();  

	return 0;  
}

int NoBlockServer()  
{  
	WORD wVersionRequested;  // ˫�ֽڣ�winsock��İ汾  
	WSADATA wsaData;         // winsock��汾�������Ϣ  

	wVersionRequested = MAKEWORD(1, 1); // 0x0101 ��:257  


	// ����winsock�Ⲣȷ��winsock�汾��ϵͳ�����������wsaData��  
	WSAStartup( wVersionRequested, &wsaData );  


	// AF_INET ��ʾ����TCP/IPЭ����  
	// SOCK_STREAM ��ʾ����TCPЭ��  
	// 0��ͨ����Ĭ�����  
	unsigned int sockSrv = socket(AF_INET, SOCK_STREAM, 0);  

	SOCKADDR_IN addrSrv;  

	addrSrv.sin_family = AF_INET; // TCP/IPЭ����  
	addrSrv.sin_addr.S_un.S_addr = inet_addr("0.0.0.0"); // socket��Ӧ��IP��ַ  
	addrSrv.sin_port = htons(8888); // socket��Ӧ�Ķ˿�  

	// ��socket�󶨵�ĳ��IP�Ͷ˿ڣ�IP��ʶ�������˿ڱ�ʶͨ�Ž��̣�  
	bind(sockSrv,(SOCKADDR*)&addrSrv, sizeof(SOCKADDR));  

	// ��socket����Ϊ����ģʽ��5��ʾ�ȴ����Ӷ��е���󳤶�  
	listen(sockSrv, 5);  

	SOCKADDR_IN addrClient;  
	int len = sizeof(SOCKADDR);  
	unsigned int sockConn = accept(sockSrv,(SOCKADDR*)&addrClient, &len);  

	printf("To receive...\n");  
	char recvBuf[100] = {0};  
	recv(sockConn, recvBuf, 100, 0); // ���տͻ������ݣ����һ������һ������Ϊ0  
	printf("recv is %s\n", recvBuf);  

	while(1);  

	closesocket(sockConn);    
	closesocket(sockSrv);  
	WSACleanup();  

	return 0;  
}  
