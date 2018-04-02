#pragma once
#include<WinSock2.h>
#include "OutPut.h"
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define GROUP_PORT_LOCAL /*9160*/5150
#define GROUP_IP_LOCAL /*"233.31.1.2"*/"233.0.0.1"
#define GROUP_PORT_REMOTE 9162
#define GROUP_IP_REMOTE "233.31.11.162"

#define _flagRemoteOn 1
#define _CommLen_ 1000

class CRemoteConnUDP
{

public:
	CRemoteConnUDP()
	{
		hSendEven = CreateEvent(NULL,FALSE,TRUE,_T("COMM_SendEvent"));//第一次可使用，谁使用完谁解放，保证独占性

		NetStartUp();
	}

	~CRemoteConnUDP()
	{
		WSACleanup();

		if (hSendEven != NULL)
		{
			CloseHandle(hSendEven);
			hSendEven = NULL;
		}
	}

public:
	int bNetOn;//网络是否连接上，0未连接，1连接
	int bGroup;//是否组播方式，1为组播，0为点播

public:
	struct ip_mreq mreq;//组播使用
	struct sockaddr_in server_addr,client_addr;//服务器Ip和本地Ip
	int client_addr_length;//客户端地址长度，本地为客户端
	int server_addr_length;//服务端地址长度
	int client_socketfd;//Socket客户号
	int client_socketbind;//Socket接收绑定号
	int server_socketfd;//Socket服务号

	HANDLE hSendEven;//保证发送独占性，通过事件处理保证独占性

	
	string ipAdress;//本地IP获取
public:
	//客户端
	//网络启动时必须先打开Start
	int NetStartUp()
	{
		DWORD dwIP;

		char sHostName[256];
		WSADATA wsadata;	//此处代码不可缺失，否则读取不到主机名

		WORD sockVersion=MAKEWORD(2,2);

		if (WSAStartup(sockVersion, &wsadata) != 0)
		{
			printf("socket error!");
			return 0;
	
		}		

		memset(sHostName, 0, 256);
		gethostname(sHostName, 127);//

		//根据本机主机名得到本机ip 
		hostent*   hn;
		hn = gethostbyname(sHostName);

		ipAdress= inet_ntoa(*(struct   in_addr   *)hn->h_addr_list[0]);//把ip换成字符串形式

		dwIP=ntohl(inet_addr(ipAdress.c_str()));//获取全局Ipdiz

		return 1;
	}
	
	//原理，组播发送类似创建服务器
	//组播接收类似创建客户端
	int InitMultiUDP()
	{	

		if ((client_socketfd=(int)socket(AF_INET,SOCK_DGRAM,0)) < 0)
		{    
			g_pMainWnd->WarnLog("创建组播Socket失败");		
			return -1;
		}else{
			g_pMainWnd->InfoLog("创建组播Socket成功");
		}

		unsigned int yes = 1;
		if (setsockopt(client_socketfd,SOL_SOCKET,SO_REUSEADDR,(char *)&yes,sizeof(yes)) < 0) 
		{   
			g_pMainWnd->WarnLog("组播socket重用失败");
			return -1;
		} else{
			g_pMainWnd->InfoLog("组播socket重用成功");
		}

		//set up destination address  
		client_addr_length=sizeof(client_addr);
		memset(&client_addr,0,sizeof(client_addr));
		client_addr.sin_family=AF_INET;
		client_addr.sin_addr.s_addr=htonl(INADDR_ANY);
		client_addr.sin_port=htons(GROUP_PORT_LOCAL);	

		int client_socketbind=bind(client_socketfd,(struct sockaddr*)&client_addr,sizeof(client_addr));
		if(client_socketbind<0)
		{
			g_pMainWnd->WarnLog("组播绑定Ip失败");
			int n =GetLastError();
			return -1;
		}else{
			g_pMainWnd->InfoLog("组播绑定Ip成功");
		}

		mreq.imr_multiaddr.s_addr=inet_addr(GROUP_IP_LOCAL);
		mreq.imr_interface.s_addr=htonl(INADDR_ANY);
		if (setsockopt(client_socketfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *)&mreq,sizeof(mreq)) < 0)
		{
			g_pMainWnd->WarnLog("加入组播群失败");
			return -1;
		}else{
			g_pMainWnd->InfoLog("加入组播群成功");
		}

		//服务器地址
		if ((server_socketfd=(int)socket(AF_INET,SOCK_DGRAM,0)) < 0)
		{    
			g_pMainWnd->WarnLog("创建服务器组播Socket失败");		
			return -1;
		}else{
			g_pMainWnd->InfoLog("创建服务器组播Socket成功");
		}

		server_addr_length=sizeof(server_addr);
		memset(&server_addr,0,sizeof(server_addr));
		server_addr.sin_family=AF_INET;
		server_addr.sin_addr.s_addr=inet_addr(GROUP_IP_REMOTE);
		server_addr.sin_port=htons(GROUP_PORT_REMOTE);

		// 	int lenSend;
		// 	char *sendData = "the record";
		// 	lenSend = sendto(server_socketfd,(char*)sendData,strlen(sendData),0,(struct sockaddr*)&server_addr,server_addr_length);
		// 
		// 	int lenCommand;
		// 	char chRecvBuf[1000];
		// 	lenCommand = recvfrom(client_socketfd,chRecvBuf,1000,0,(sockaddr*)&client_addr,&client_addr_length);
		// 	if(lenCommand<=0)
		// 	{
		// 		return GetLastError();
		// 	}

		bNetOn = 1;//网络绑定
		bGroup = 1;

		return 1;
	}

	//关闭Socket
	int CloseSocket()
	{
		if (client_socketfd != NULL)
		{
			closesocket(client_socketfd);
			client_socketfd = NULL;
		}

		if (server_socketfd != NULL)
		{
			closesocket(server_socketfd);
			server_socketfd = NULL;
		}
		return 1;
	}

	int GetMsg(char *msg)
	{	
		CRemoteConnUDP *pDlg = this;

#if _flagRemoteOn

		int msgLen = _CommLen_;
		//int server_len = sizeof(pDlg->server_addr);
		int getLen =recvfrom(pDlg->client_socketfd,(char*)msg,msgLen,0,(struct sockaddr*)&pDlg->client_addr,&pDlg->client_addr_length);

		if(getLen > 34)
		{
			int yjm = 1;
		}
		if (getLen > 0)
		{
			//验证收的源是不是设置Ip，组播时与Ip地址比对，这是有问题的
			if (pDlg->bGroup)
			{
				return getLen;
			}else{
				if (pDlg->VerifyMsgSrc(pDlg->client_addr,pDlg->server_addr.sin_addr.s_addr))
				{
					return getLen;
				}else{
					return -2;
				}
			}	

		}else{
			return 0;
		}
#else
		return 1;
#endif

	}

	int SendMsg(char *msg,unsigned int msgLen)
	{
		CRemoteConnUDP *pDlg = this;
		//网络连接
		int sendLen;//发送长度		

#if _flagRemoteOn		

		DWORD dw = WaitForSingleObject (pDlg->hSendEven,INFINITE);
		sendLen=sendto(pDlg->server_socketfd,(const char*)msg,msgLen,0,(struct sockaddr*)&pDlg->server_addr,pDlg->server_addr_length);
		SetEvent(pDlg->hSendEven);

		if (sendLen == msgLen)
		{
			return 1;
		}else{
			return 0;
		}
#else
		return 1;
#endif

	}

	//验证消息源头是否为所设置IP所发
	int VerifyMsgSrc(sockaddr_in server_addr_Src,ULONG ulAddrSet)
	{
		//ULONG ulAddrSet = inet_addr(g_runPara.mNetConfig.iMCS_IPAddress);
		if (ulAddrSet == server_addr_Src.sin_addr.s_addr)
		{
			return 1;
		}else{
			return 0;
		}
	}
public:
	//服务器
	SOCKET serSocket;//服务器Socket
	sockaddr_in serAddr;//服务器地址
	ip_mreq multiCast;//组播组
	sockaddr_in clientAddr;//组播接收的地址
public:
	int InitMutltiServer()
	{

// 		WSADATA WSAData;
// 		WORD sockVersion=MAKEWORD(2,2);
// 		if(WSAStartup(sockVersion,&WSAData)!=0)
// 			return 0;
// 
// 		SOCKET serSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);  //创建服务器socket
// 		if(INVALID_SOCKET==serSocket)
// 		{
// 			cout<<"socket error!";
// 			return 0;
// 		}
// 
// 		//设置传输协议、端口以及目的地址 
// 		sockaddr_in serAddr;
// 		serAddr.sin_family=AF_INET;
// 		serAddr.sin_port=htons(8888);
// 		serAddr.sin_addr.S_un.S_addr=INADDR_ANY;
// 
// 		if(bind(serSocket,(sockaddr*)&serAddr,sizeof(serAddr))==SOCKET_ERROR)    //将socket绑定地址 
// 		{
// 			cout<<"bind error";
// 			closesocket(serSocket);
// 			return 0;
// 		}
// 
// 	/* ip_mreq的定义
// 	typedef struct ip_mreq {
// 		IN_ADDR imr_multiaddr;  // IP multicast address of group.
// 		IN_ADDR imr_interface;  // Local IP address of interface.
// 	} IP_MREQ, *PIP_MREQ;
// 	*/
// 		//加入组播组
// 		ip_mreq multiCast;
// 		multiCast.imr_interface.S_un.S_addr=INADDR_ANY;     //本地某一网络设备接口的IP地址。
// 		multiCast.imr_multiaddr.S_un.S_addr=inet_addr("234.2.2.2"); //组播组的IP地址。
// 		setsockopt(serSocket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&multiCast,sizeof(multiCast));
// 
// 		sockaddr_in clientAddr;
// 		int iAddrlen=sizeof(clientAddr);
// 		char buff[1024];    //建立接收缓存字节数组 
// 		while(true)
// 		{
// 			memset(buff,0,1024);    //清空接收缓存数组
// 			//开始接收数据 
// 			int len=recvfrom(serSocket,buff,1024,0,(sockaddr*)&clientAddr,&iAddrlen);
// 			if(len>0)
// 			{
// 				cout<<"客户端地址："<<inet_ntoa(clientAddr.sin_addr)<<endl;
// 				cout<<buff;
// 
// 			//  sendto(serSocket,buff,1024,0,(sockaddr*)&clientAddr,iAddrlen);
// 			}
// 		}
// 
// 		closesocket(serSocket);     //关闭socket 
// 		WSACleanup();
// 
// 		return 0;




// 		serSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);  //创建服务器socket
// 		if(INVALID_SOCKET==serSocket)
// 		{
// 			cout<<"socket error!\n";
// 			return 0;
// 		}else{
// 			cout<<"建立组播服务器成功\n";
// 		}
// 		
// 		serAddr.sin_family=AF_INET;
// 		serAddr.sin_port=htons(8888/*GROUP_PORT_LOCAL*/);
// 		serAddr.sin_addr.S_un.S_addr=INADDR_ANY;
// 		if(bind(serSocket,(sockaddr*)&serAddr,sizeof(serAddr))==SOCKET_ERROR) //将socket绑定地址 
// 		{
// 			cout<<"bind error\n";
// 			closesocket(serSocket);
// 			return 0;
// 		}else{
// 			cout<<"组播端口监听成功\n";
// 		}
// 
// 		/* ip_mreq的定义
// typedef struct ip_mreq {
//     IN_ADDR imr_multiaddr;  // IP multicast address of group.
//     IN_ADDR imr_interface;  // Local IP address of interface.
// } IP_MREQ, *PIP_MREQ;
// */
// 		//加入组播组		
// 		multiCast.imr_interface.S_un.S_addr=INADDR_ANY;     //本地某一网络设备接口的IP地址。
// 		multiCast.imr_multiaddr.S_un.S_addr=inet_addr("234.2.2.2"/*GROUP_IP_LOCAL*/); //组播组的IP地址。
// 		setsockopt(serSocket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&multiCast,sizeof(multiCast));
// 	
// 	
// 		int iAddrlen=sizeof(clientAddr);
// 		char buff[1024];    //建立接收缓存字节数组 
// 		while(true)
// 		{
// 			memset(buff,0,1024);    //清空接收缓存数组
// 			//开始接收数据 
// 			int len=recvfrom(serSocket,buff,1024,0,(sockaddr*)&clientAddr,&iAddrlen);
// 			if(len>0)
// 			{
// 				cout<<"客户端地址："<<inet_ntoa(clientAddr.sin_addr)<<endl;
// 				cout<<buff;
// 
// 				//  sendto(serSocket,buff,1024,0,(sockaddr*)&clientAddr,iAddrlen);
// 			}
// 		}
// 
// 		closesocket(serSocket);     //关闭socket 
// 		WSACleanup();
// 
 		return 0;
	
	}

	int InitMutltiServer2()
	{
#define MCASTADDR "234.2.2.2" //本例使用的多播组地址。 
#define MCASTPORT 8888 //绑定的本地端口号。		 
#define BUFSIZE 1024 //接收数据缓冲大小。
		WSADATA wsaData;  
		WSAStartup(MAKEWORD(2, 2), &wsaData);  

		SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);  

		sockaddr_in addr;  
		addr.sin_family = AF_INET;  
		addr.sin_addr.S_un.S_addr = INADDR_ANY;  
		addr.sin_port = htons(MCASTPORT);

		bind(sock, (sockaddr*)&addr, sizeof(addr));  

		// 加入组播啦  
		ip_mreq multiCast;  
		multiCast.imr_interface.S_un.S_addr = INADDR_ANY;  
		multiCast.imr_multiaddr.S_un.S_addr = inet_addr(MCASTADDR);  
		setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast));  

		int len = sizeof(sockaddr);  
		while(true)  
		{     
			char buf[100] = {0};  
			recvfrom(sock, buf, sizeof(buf) - 1, 0, (sockaddr*)&addr, &len);  
			printf("%s\n",buf);  
		}  

		closesocket(sock);  
		WSACleanup();  
		return 0; 
	}

	public:
		int InitMultiCient()
		{
			WSADATA WSAData;
			WORD sockVersion=MAKEWORD(2,2);
			if(WSAStartup(sockVersion,&WSAData)!=0)
				return 0;

			SOCKET clientSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
			if(INVALID_SOCKET==clientSocket)
			{
				cout<<"socket error!";
				return 0;
			}

			sockaddr_in dstAddr;
			dstAddr.sin_family=AF_INET;
			dstAddr.sin_port=htons(GROUP_PORT_LOCAL);
			dstAddr.sin_addr.S_un.S_addr=inet_addr(GROUP_IP_LOCAL);

			const char* sendData="来自客户端的数据包。";

			sendto(clientSocket,sendData,strlen(sendData),0,(sockaddr*)&dstAddr,sizeof(dstAddr));

			closesocket(clientSocket);
			WSACleanup();

			return 1;
		}

		int InitMultiCient2()
		{
			//WSADATA wsd;
			struct sockaddr_in remote;
			SOCKET sock,sockM;
			TCHAR sendbuf[BUFSIZE];
			int len = sizeof( struct sockaddr_in);
			//初始化WinSock2.2
// 			if( WSAStartup( MAKEWORD(2,2),&wsd) != 0 )
// 			{
// 				printf("WSAStartup() failed\n");
// 				return -1;
// 			}
			if((sock=WSASocket(AF_INET,SOCK_DGRAM,0,NULL,0, WSA_FLAG_MULTIPOINT_C_LEAF|WSA_FLAG_MULTIPOINT_D_LEAF| WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
			{
				printf("socket failed with:%d\n",WSAGetLastError());
				WSACleanup();
				return -1;
			}
			//加入多播组
			remote.sin_family = AF_INET;
			remote.sin_port = htons(MCASTPORT);
			remote.sin_addr.s_addr = inet_addr( MCASTADDR );
			if(( sockM = WSAJoinLeaf(sock,(SOCKADDR*)&remote, sizeof(remote),NULL,NULL,NULL,NULL, JL_BOTH)) == INVALID_SOCKET)
			{
				printf("WSAJoinLeaf() failed:%d\n",WSAGetLastError());
				closesocket(sock);
				WSACleanup();
				return -1;
			}
			
			//发送多播数据，当用户在控制台输入"QUIT"时退出。
			while(1)
			{
				printf("SEND : ");
				scanf_s("%s",sendbuf);
				if( sendto(sockM,(char*)sendbuf,strlen(sendbuf),0,(struct sockaddr*) &remote,sizeof(remote))==SOCKET_ERROR)
				{
					printf("sendto failed with: %d\n",WSAGetLastError());
					closesocket(sockM);
					closesocket(sock);
					WSACleanup();
					return -1;
				}
				if(strcmp(sendbuf,"QUIT")==0)
					break;
				Sleep(500);
			}
			closesocket(sockM);
			closesocket(sock);
			WSACleanup();
			
			return 1;

		}

	


};

CRemoteConnUDP mRemoteConnUDP;//可使用的连接

void testUdpGroup()
{
	
	mRemoteConnUDP.InitMultiUDP();
	char* msgGet = new char[_CommLen_];
	memset(msgGet,0,_CommLen_);
	FILE *fp;
	fopen_s(&fp,"d:\\RemoteConnUDP.dat","a+");

	int ii = 0;
	while(1)
	{		
		int msgLen = mRemoteConnUDP.GetMsg(msgGet);
		if (msgLen > 0)
		{
			g_pMainWnd->InfoLog(msgGet);			
			fprintf(fp,"%s\n",msgGet);
		}
		

		memset(msgGet,0,_CommLen_);
		sprintf_s(msgGet,_CommLen_,"message send %d\n",ii);
		int isend = mRemoteConnUDP.SendMsg(msgGet,_CommLen_);
		if (isend > 0)
		{
			g_pMainWnd->InfoLog(msgGet);
			fprintf(fp,"%s\n",msgGet);
		}
		
	}

	fclose(fp);
	delete[] msgGet;
	
}

void testUdpGroupServer()
{	
	mRemoteConnUDP.InitMutltiServer2();
}

void testUdpGroupClient()
{
	mRemoteConnUDP.InitMultiCient2();
}


