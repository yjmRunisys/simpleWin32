#ifndef CTCPSOCKET_H
#define CTCPSOCKET_H

#include <winsock2.h>
#include "string"

#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define LOCAL_IPADRESS ("127.0.0.1")

enum EnumTcpFail{
    /******return values of init socket*****/
    SUCCESS = 0,
    INIT_BEFORE = 1,
    SOCKET_ERR=-1,
    BIND_ERR=-2,
    ACCEPT_ERR=-3,
    CONNECT_ERR=-4,
    SETSOCKOPT_ERR=-5,
    RECV_ERR = -6,
    SEND_ERR = -7
};

enum EnumTcpType{
    TCP_SERVER = 0,
    TCP_CLIENT = 1,
};

typedef int socklen_t;

class CTcpSocket
{
public:
    CTcpSocket();
    ~CTcpSocket();

public:
    int InitServer(std::string strIp,unsigned short port,unsigned int len,int transMode);
    int InitClient(std::string strServerIp,unsigned short serverPort,unsigned int len,
		double speed,int transMode,string localIp = "127.0.0.1");
    int Recv(unsigned char* recvBuf,int nLen);
    int Send(unsigned char* sendBuf,int nLen);
    int CloseSocket();//关了之后才能重新开始Init

    static int NetStartUp();//网络启动时必须先打开Start
    static int bNetStart;

public:
    bool bInit;

protected:
    std::string m_strServerIp;//ip地址
    unsigned short m_usServerPort;//串口
	string m_localIp;//本地ip
    unsigned int m_unFrameLen;//接收时buf长
    int m_nTransMode;//传输方式
    double m_dSpeed;//速度设置
    int m_sockServerfd;//accept sock
    int m_sockClientfd;//client sock
    int *m_pUseFd;//在用的fd
    unsigned long long m_ullDataAmountRecv;//总接收长度，字节数

    struct sockaddr_in m_serveraddr;//发送时的目标地址

    EnumTcpType m_type;
};

#endif // CTCPSOCKET_H
