#pragma once
#include "stdafx.h"
#include "time.h"
#include "TcpSocket.h"

#define DATA_LEN 8*1024*1024
#define TEST_TIMES 100000
#define TIME_MINIMNUM 5*60//至少测试300s
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
	printf("监控地址：%s\n",CONNECT_IP);
	printf("监控端口:%d\n",CONNECT_PORT);
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

typedef unsigned short uint16_t;
typedef unsigned int uint32t;
typedef int		int32_t;

bool NoBlockClient(const string& _host, uint16_t _port, uint32t _timeout, int32_t& _sockfd)
{

	// 网络初始化  
	WORD wVersionRequested;  
	WSADATA wsaData;  
	wVersionRequested = MAKEWORD(2, 2);  
	WSAStartup( wVersionRequested, &wsaData );  

	// 创建客户端socket(默认为是阻塞socket)  
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);  

	// 设置为非阻塞的socket  
	int iMode = 1;  
	ioctlsocket(sockClient, FIONBIO, (u_long FAR*)&iMode); 

	// 定义服务端  
	SOCKADDR_IN addrSrv;  
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  
	addrSrv.sin_family = AF_INET;  
	addrSrv.sin_port = htons(8888); 


	// 超时时间  
	struct timeval tm;  
	tm.tv_sec  = 5; //5秒连接 
	tm.tv_usec = 0;  
	int ret = -1;  

	// 尝试去连接服务端  
	if (-1 != connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)))  
	{  
		ret = 1; // 连接成功  
	}  
	else  
	{  
		fd_set set;  
		FD_ZERO(&set);  
		FD_SET(sockClient, &set);  

		if (select(-1, NULL, &set, NULL, &tm) <= 0)  
		{  
			ret = -1; // 有错误(select错误或者超时)  
		}  
		else  
		{  
			int error = -1;  
			int optLen = sizeof(int);  
			getsockopt(sockClient, SOL_SOCKET, SO_ERROR, (char*)&error, &optLen);   

			// 之所以下面的程序不写成三目运算符的形式， 是为了更直观， 便于注释  
			if (0 != error)  
			{  
				ret = -1; // 有错误  
			}  
			else  
			{  
				ret = 1;  // 无错误  
			}  
		}  
	}  

	// 设回为阻塞socket  
	iMode = 0;  
	ioctlsocket(sockClient, FIONBIO, (u_long FAR*)&iMode); //设置为阻塞模式 

	// connect状态  
	printf("ret is %d\n", ret);  

	// 发送数据到服务端测试以下  
	if(1 == ret)  
	{  
		send(sockClient, "hello world", strlen("hello world") + 1, 0);  
	}  

	// 释放网络连接  
	closesocket(sockClient);  
	WSACleanup();  

	return 0;  
}

int NoBlockServer()  
{  
	WORD wVersionRequested;  // 双字节，winsock库的版本  
	WSADATA wsaData;         // winsock库版本的相关信息  

	wVersionRequested = MAKEWORD(1, 1); // 0x0101 即:257  


	// 加载winsock库并确定winsock版本，系统会把数据填入wsaData中  
	WSAStartup( wVersionRequested, &wsaData );  


	// AF_INET 表示采用TCP/IP协议族  
	// SOCK_STREAM 表示采用TCP协议  
	// 0是通常的默认情况  
	unsigned int sockSrv = socket(AF_INET, SOCK_STREAM, 0);  

	SOCKADDR_IN addrSrv;  

	addrSrv.sin_family = AF_INET; // TCP/IP协议族  
	addrSrv.sin_addr.S_un.S_addr = inet_addr("0.0.0.0"); // socket对应的IP地址  
	addrSrv.sin_port = htons(8888); // socket对应的端口  

	// 将socket绑定到某个IP和端口（IP标识主机，端口标识通信进程）  
	bind(sockSrv,(SOCKADDR*)&addrSrv, sizeof(SOCKADDR));  

	// 将socket设置为监听模式，5表示等待连接队列的最大长度  
	listen(sockSrv, 5);  

	SOCKADDR_IN addrClient;  
	int len = sizeof(SOCKADDR);  
	unsigned int sockConn = accept(sockSrv,(SOCKADDR*)&addrClient, &len);  

	printf("To receive...\n");  
	char recvBuf[100] = {0};  
	recv(sockConn, recvBuf, 100, 0); // 接收客户端数据，最后一个参数一般设置为0  
	printf("recv is %s\n", recvBuf);  

	while(1);  

	closesocket(sockConn);    
	closesocket(sockSrv);  
	WSACleanup();  

	return 0;  
}  
