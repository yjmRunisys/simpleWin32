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
		hSendEven = CreateEvent(NULL,FALSE,TRUE,_T("COMM_SendEvent"));//��һ�ο�ʹ�ã�˭ʹ����˭��ţ���֤��ռ��

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
	int bNetOn;//�����Ƿ������ϣ�0δ���ӣ�1����
	int bGroup;//�Ƿ��鲥��ʽ��1Ϊ�鲥��0Ϊ�㲥

public:
	struct ip_mreq mreq;//�鲥ʹ��
	struct sockaddr_in server_addr,client_addr;//������Ip�ͱ���Ip
	int client_addr_length;//�ͻ��˵�ַ���ȣ�����Ϊ�ͻ���
	int server_addr_length;//����˵�ַ����
	int client_socketfd;//Socket�ͻ���
	int client_socketbind;//Socket���հ󶨺�
	int server_socketfd;//Socket�����

	HANDLE hSendEven;//��֤���Ͷ�ռ�ԣ�ͨ���¼�����֤��ռ��

	
	string ipAdress;//����IP��ȡ
public:
	//�ͻ���
	//��������ʱ�����ȴ�Start
	int NetStartUp()
	{
		DWORD dwIP;

		char sHostName[256];
		WSADATA wsadata;	//�˴����벻��ȱʧ�������ȡ����������

		WORD sockVersion=MAKEWORD(2,2);

		if (WSAStartup(sockVersion, &wsadata) != 0)
		{
			printf("socket error!");
			return 0;
	
		}		

		memset(sHostName, 0, 256);
		gethostname(sHostName, 127);//

		//���ݱ����������õ�����ip 
		hostent*   hn;
		hn = gethostbyname(sHostName);

		ipAdress= inet_ntoa(*(struct   in_addr   *)hn->h_addr_list[0]);//��ip�����ַ�����ʽ

		dwIP=ntohl(inet_addr(ipAdress.c_str()));//��ȡȫ��Ipdiz

		return 1;
	}
	
	//ԭ���鲥�������ƴ���������
	//�鲥�������ƴ����ͻ���
	int InitMultiUDP()
	{	

		if ((client_socketfd=(int)socket(AF_INET,SOCK_DGRAM,0)) < 0)
		{    
			g_pMainWnd->WarnLog("�����鲥Socketʧ��");		
			return -1;
		}else{
			g_pMainWnd->InfoLog("�����鲥Socket�ɹ�");
		}

		unsigned int yes = 1;
		if (setsockopt(client_socketfd,SOL_SOCKET,SO_REUSEADDR,(char *)&yes,sizeof(yes)) < 0) 
		{   
			g_pMainWnd->WarnLog("�鲥socket����ʧ��");
			return -1;
		} else{
			g_pMainWnd->InfoLog("�鲥socket���óɹ�");
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
			g_pMainWnd->WarnLog("�鲥��Ipʧ��");
			int n =GetLastError();
			return -1;
		}else{
			g_pMainWnd->InfoLog("�鲥��Ip�ɹ�");
		}

		mreq.imr_multiaddr.s_addr=inet_addr(GROUP_IP_LOCAL);
		mreq.imr_interface.s_addr=htonl(INADDR_ANY);
		if (setsockopt(client_socketfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *)&mreq,sizeof(mreq)) < 0)
		{
			g_pMainWnd->WarnLog("�����鲥Ⱥʧ��");
			return -1;
		}else{
			g_pMainWnd->InfoLog("�����鲥Ⱥ�ɹ�");
		}

		//��������ַ
		if ((server_socketfd=(int)socket(AF_INET,SOCK_DGRAM,0)) < 0)
		{    
			g_pMainWnd->WarnLog("�����������鲥Socketʧ��");		
			return -1;
		}else{
			g_pMainWnd->InfoLog("�����������鲥Socket�ɹ�");
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

		bNetOn = 1;//�����
		bGroup = 1;

		return 1;
	}

	//�ر�Socket
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
			//��֤�յ�Դ�ǲ�������Ip���鲥ʱ��Ip��ַ�ȶԣ������������
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
		//��������
		int sendLen;//���ͳ���		

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

	//��֤��ϢԴͷ�Ƿ�Ϊ������IP����
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
	//������
	SOCKET serSocket;//������Socket
	sockaddr_in serAddr;//��������ַ
	ip_mreq multiCast;//�鲥��
	sockaddr_in clientAddr;//�鲥���յĵ�ַ
public:
	int InitMutltiServer()
	{

// 		WSADATA WSAData;
// 		WORD sockVersion=MAKEWORD(2,2);
// 		if(WSAStartup(sockVersion,&WSAData)!=0)
// 			return 0;
// 
// 		SOCKET serSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);  //����������socket
// 		if(INVALID_SOCKET==serSocket)
// 		{
// 			cout<<"socket error!";
// 			return 0;
// 		}
// 
// 		//���ô���Э�顢�˿��Լ�Ŀ�ĵ�ַ 
// 		sockaddr_in serAddr;
// 		serAddr.sin_family=AF_INET;
// 		serAddr.sin_port=htons(8888);
// 		serAddr.sin_addr.S_un.S_addr=INADDR_ANY;
// 
// 		if(bind(serSocket,(sockaddr*)&serAddr,sizeof(serAddr))==SOCKET_ERROR)    //��socket�󶨵�ַ 
// 		{
// 			cout<<"bind error";
// 			closesocket(serSocket);
// 			return 0;
// 		}
// 
// 	/* ip_mreq�Ķ���
// 	typedef struct ip_mreq {
// 		IN_ADDR imr_multiaddr;  // IP multicast address of group.
// 		IN_ADDR imr_interface;  // Local IP address of interface.
// 	} IP_MREQ, *PIP_MREQ;
// 	*/
// 		//�����鲥��
// 		ip_mreq multiCast;
// 		multiCast.imr_interface.S_un.S_addr=INADDR_ANY;     //����ĳһ�����豸�ӿڵ�IP��ַ��
// 		multiCast.imr_multiaddr.S_un.S_addr=inet_addr("234.2.2.2"); //�鲥���IP��ַ��
// 		setsockopt(serSocket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&multiCast,sizeof(multiCast));
// 
// 		sockaddr_in clientAddr;
// 		int iAddrlen=sizeof(clientAddr);
// 		char buff[1024];    //�������ջ����ֽ����� 
// 		while(true)
// 		{
// 			memset(buff,0,1024);    //��ս��ջ�������
// 			//��ʼ�������� 
// 			int len=recvfrom(serSocket,buff,1024,0,(sockaddr*)&clientAddr,&iAddrlen);
// 			if(len>0)
// 			{
// 				cout<<"�ͻ��˵�ַ��"<<inet_ntoa(clientAddr.sin_addr)<<endl;
// 				cout<<buff;
// 
// 			//  sendto(serSocket,buff,1024,0,(sockaddr*)&clientAddr,iAddrlen);
// 			}
// 		}
// 
// 		closesocket(serSocket);     //�ر�socket 
// 		WSACleanup();
// 
// 		return 0;




// 		serSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);  //����������socket
// 		if(INVALID_SOCKET==serSocket)
// 		{
// 			cout<<"socket error!\n";
// 			return 0;
// 		}else{
// 			cout<<"�����鲥�������ɹ�\n";
// 		}
// 		
// 		serAddr.sin_family=AF_INET;
// 		serAddr.sin_port=htons(8888/*GROUP_PORT_LOCAL*/);
// 		serAddr.sin_addr.S_un.S_addr=INADDR_ANY;
// 		if(bind(serSocket,(sockaddr*)&serAddr,sizeof(serAddr))==SOCKET_ERROR) //��socket�󶨵�ַ 
// 		{
// 			cout<<"bind error\n";
// 			closesocket(serSocket);
// 			return 0;
// 		}else{
// 			cout<<"�鲥�˿ڼ����ɹ�\n";
// 		}
// 
// 		/* ip_mreq�Ķ���
// typedef struct ip_mreq {
//     IN_ADDR imr_multiaddr;  // IP multicast address of group.
//     IN_ADDR imr_interface;  // Local IP address of interface.
// } IP_MREQ, *PIP_MREQ;
// */
// 		//�����鲥��		
// 		multiCast.imr_interface.S_un.S_addr=INADDR_ANY;     //����ĳһ�����豸�ӿڵ�IP��ַ��
// 		multiCast.imr_multiaddr.S_un.S_addr=inet_addr("234.2.2.2"/*GROUP_IP_LOCAL*/); //�鲥���IP��ַ��
// 		setsockopt(serSocket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&multiCast,sizeof(multiCast));
// 	
// 	
// 		int iAddrlen=sizeof(clientAddr);
// 		char buff[1024];    //�������ջ����ֽ����� 
// 		while(true)
// 		{
// 			memset(buff,0,1024);    //��ս��ջ�������
// 			//��ʼ�������� 
// 			int len=recvfrom(serSocket,buff,1024,0,(sockaddr*)&clientAddr,&iAddrlen);
// 			if(len>0)
// 			{
// 				cout<<"�ͻ��˵�ַ��"<<inet_ntoa(clientAddr.sin_addr)<<endl;
// 				cout<<buff;
// 
// 				//  sendto(serSocket,buff,1024,0,(sockaddr*)&clientAddr,iAddrlen);
// 			}
// 		}
// 
// 		closesocket(serSocket);     //�ر�socket 
// 		WSACleanup();
// 
 		return 0;
	
	}

	int InitMutltiServer2()
	{
#define MCASTADDR "234.2.2.2" //����ʹ�õĶಥ���ַ�� 
#define MCASTPORT 8888 //�󶨵ı��ض˿ںš�		 
#define BUFSIZE 1024 //�������ݻ����С��
		WSADATA wsaData;  
		WSAStartup(MAKEWORD(2, 2), &wsaData);  

		SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);  

		sockaddr_in addr;  
		addr.sin_family = AF_INET;  
		addr.sin_addr.S_un.S_addr = INADDR_ANY;  
		addr.sin_port = htons(MCASTPORT);

		bind(sock, (sockaddr*)&addr, sizeof(addr));  

		// �����鲥��  
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

			const char* sendData="���Կͻ��˵����ݰ���";

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
			//��ʼ��WinSock2.2
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
			//����ಥ��
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
			
			//���Ͷಥ���ݣ����û��ڿ���̨����"QUIT"ʱ�˳���
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

CRemoteConnUDP mRemoteConnUDP;//��ʹ�õ�����

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


