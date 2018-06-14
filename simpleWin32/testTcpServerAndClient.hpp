#pragma once
#include "stdafx.h"
#include "time.h"
#include "TcpSocket.h"

#define DATA_LEN 8*1024*1024
#define TEST_TIMES 100000
#define TIME_MINIMNUM 5*60//至少测试300s
#define CONNECT_IP "192.168.0.150"
#define CONNECT_PORT 10015
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
			{//间隔时间大于1000ms则刷新

				//显示速度
				//平均速度
				//mbreceived = dwCount /(1024*1024.0);  //已接收到的字节，单位为MB
				//secs = (t1 - tIni)/1000.0;//间隔毫秒
				//mbsec = mbreceived/ secs;

				//瞬时速度
				double mbreceived1 = (dwCount - dwCount0) /(1024*1024.0);  //已接收到的字节，单位为MB
				double mbsec =  mbreceived1 * 1000 / (t1 - t0);				

				//更新系统状态	
				double readRate1 = mbsec;	
				double timePlayOnce1 = (t1 - tIni)/1000.0;

				printf("已测试时间%.3f s,发送数据量%lld Byte,速度 %.3f M/s\n",timePlayOnce1,dwCount,mbsec);

				//更新统计量
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
			{//间隔时间大于1000ms则刷新

				//显示速度
				//平均速度
				//mbreceived = dwCount /(1024*1024.0);  //已接收到的字节，单位为MB
				//secs = (t1 - tIni)/1000.0;//间隔毫秒
				//mbsec = mbreceived/ secs;

				//瞬时速度
				double mbreceived1 = (dwCount - dwCount0) /(1024*1024.0);  //已接收到的字节，单位为MB
				double mbsec =  mbreceived1 * 1000 / (t1 - t0);				

				//更新系统状态	
				double readRate1 = mbsec;	
				double timePlayOnce1 = (t1 - tIni)/1000.0;

				printf("已测试时间%.3f s,接收数据量%lld Byte,速度 %.3f MB/s\n",timePlayOnce1,dwCount,mbsec);			

				//更新统计量
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

	//开始监听
	if (listen(slisten,5) == SOCKET_ERROR)
	{
		printf("listen error!\n");
		return 0;
	}

	//循环接收数据
	SOCKET sclient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	while(true)
	{
		printf("等待连接...\n");
		sclient = accept(slisten,(SOCKADDR*)&remoteAddr,&nAddrlen);
		if (sclient == INVALID_SOCKET)
		{
			printf("accept error!");
			continue;
		}
		printf("接受到一个连接：%s\r\n",inet_ntoa(remoteAddr.sin_addr));

		//发送数据
// 		char *sendData0 = new char[1024*1024];
// 		for (int i = 0;i<100000000;i++)
// 		{
// 			send(sclient,sendData0,1024,0);
// 		}
// 		delete[] sendData0;

		//接收数据
		int ret = recv(sclient,revData,255,0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			printf(revData);
		}

		//发送数据
		char *sendData = "你好，TCP客户端!\n";
		send(sclient,sendData,strlen(sendData),0);
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
	char *sendData = "你好，TCP服务器，我是客户端！\n";
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