#include "stdafx.h"
#include "TcpSocket.h"

int CTcpSocket::bNetStart = 0;

CTcpSocket::CTcpSocket()
{
    bInit = false;
    m_type = TCP_CLIENT;
    m_sockServerfd = 0;
	m_pUseFd = NULL;

    NetStartUp();
}

CTcpSocket::~CTcpSocket()
{
    CloseSocket();
    if(bNetStart)
    {
        WSACleanup();
    }
}

//网络启动时必须先打开Start
int CTcpSocket::NetStartUp()
{
    if(bNetStart)
        return 0;

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

    string ipAdress= inet_ntoa(*(struct   in_addr   *)hn->h_addr_list[0]);//把ip换成字符串形式
    dwIP=ntohl(inet_addr(ipAdress.c_str()));//获取全局Ipdiz

    bNetStart = 1;

    return 1;
}

int CTcpSocket::InitServer(std::string strServerIp,unsigned short serverPort,unsigned int len,int transMode)
{
    if(bInit)
        return INIT_BEFORE;

    m_strServerIp = strServerIp;
    m_usServerPort = serverPort;
    m_unFrameLen = len;
    m_nTransMode = transMode;

    struct sockaddr_in serveraddr,clientaddr;
    int clientaddr_len = (int)sizeof(clientaddr);
    int listenfd = (int)socket(AF_INET,SOCK_STREAM,0);
    if(listenfd < 0)
    {
        printf("create sock error:%d\r\n",errno);
        return SOCKET_ERR;
    }
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr((const char*)m_strServerIp.c_str());//htonl(m_unIp);
    serveraddr.sin_port = htons(m_usServerPort);

    int bindfd = bind(listenfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(bindfd < 0)
    {
        printf("bind error:%d\r\n",errno);
        closesocket(bindfd);
        return BIND_ERR;
    }
    printf("tcprecv bind success\r\n");

	//开始监听
    listen(listenfd,5);

    m_sockServerfd = (int)accept(listenfd,(struct sockaddr *)&clientaddr,&clientaddr_len);
    if(m_sockServerfd <= 0)
    {
        printf("accept sock error:%d\r\n",errno);
        closesocket(listenfd);
        return ACCEPT_ERR;
    }
    printf("accept success\r\n");
    int nBufLen = 1024*1024*1024;
    int rtset = setsockopt(m_sockServerfd,SOL_SOCKET,SO_RCVBUF,(char *)&nBufLen,sizeof(nBufLen));
    if(rtset < 0)
    {
        printf("set error:%d\r\n",errno);
        closesocket(m_sockServerfd);
        return SETSOCKOPT_ERR;
    }
    closesocket(listenfd);

    bInit = true;
    m_ullDataAmountRecv = 0;
    m_type = TCP_SERVER;
    m_pUseFd = &m_sockServerfd;
	printf("Server Init Success\n");

    return SUCCESS;

}

int CTcpSocket::InitClient(std::string strServerIp,unsigned short serverPort,unsigned int len,double speed,int transMode,string localIp)
{
    if(bInit)
        return INIT_BEFORE;

    m_strServerIp = strServerIp;
    m_usServerPort = serverPort;
    m_unFrameLen = len;
    m_dSpeed = speed;
    m_nTransMode = transMode;
	m_localIp = localIp;

    struct sockaddr_in clientaddr;
    socklen_t serveraddr_len = (socklen_t)sizeof(m_serveraddr);
    m_sockClientfd = (int)socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(m_sockClientfd <= 0)
    {
        printf("create socket error:%d\r\n",errno);
        return SOCKET_ERR;
    }

    memset(&clientaddr,0,sizeof(clientaddr));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr((const char*)m_localIp.c_str());//local ip

	int bindfd = bind(m_sockClientfd,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
	if(bindfd < 0)
	{
		printf("bind error:%d\r\n",errno);
		closesocket(m_sockClientfd);
		return BIND_ERR;
	}
	printf("tcpClient bind success\r\n");

    memset(&m_serveraddr,0,sizeof(m_serveraddr));
    m_serveraddr.sin_family = AF_INET;
    m_serveraddr.sin_addr.s_addr = inet_addr((const char*)m_strServerIp.c_str());//remote ip
    m_serveraddr.sin_port = htons(m_usServerPort);	
	int cnnfd = connect(m_sockClientfd,(struct sockaddr*)&m_serveraddr,serveraddr_len);
	if(cnnfd == SOCKET_ERROR)
	{
		printf("connect error:%d\r\n",GetLastError());
		closesocket(m_sockClientfd);
		return CONNECT_ERR;
	}
	printf("connect success\r\n");

    int nBufLen = 1024*1024*1024;
    int rtset = setsockopt(m_sockClientfd,SOL_SOCKET,SO_SNDBUF,(char *)&nBufLen,sizeof(nBufLen));
    if(rtset < 0)
    {
        printf("set error:%d\r\n",errno);
        closesocket(m_sockClientfd);
        return SETSOCKOPT_ERR;
    }

    bInit = true;
    m_ullDataAmountRecv = 0;
    m_type = TCP_CLIENT;
    m_pUseFd = &m_sockClientfd;

	printf("Client Init Success\n");

    return SUCCESS;
}

int CTcpSocket::CloseSocket()
{
    if(*m_pUseFd != 0)
    {
       closesocket(*m_pUseFd);
       *m_pUseFd = 0;
    }

    bInit = false;

    return 0;
}

int CTcpSocket::Recv(unsigned char* recvBuf,int nLen)
{
	if (m_pUseFd == NULL)
	{
		return RECV_ERR;
	}
    int recvLen = recv(*m_pUseFd,(char*)recvBuf,nLen,0);
    if(recvLen < 0)
    {
        return RECV_ERR;
    }

    m_ullDataAmountRecv += recvLen;

    return recvLen;
}

int CTcpSocket::Send(unsigned char* sendBuf,int nLen)
{
	if (m_pUseFd == NULL)
	{
		return RECV_ERR;
	}

    int sendLen = sendto(*m_pUseFd,(char*)sendBuf,nLen,0,
                         (struct sockaddr*)&m_serveraddr,sizeof(m_serveraddr));
    if(sendLen < 0)
    {
        return SEND_ERR;
    }
    return sendLen;
}
