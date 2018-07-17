#include <string.h>
#include <iostream>
#include "udp.h"

myudp::myudp()
{
    #ifndef MYLINUX
    //初始化socket
    DWORD ver;
    WSADATA wsaData;
    ver = MAKEWORD(1, 1);
    WSAStartup(ver, &wsaData);//windows要求，只要用socket,第一步必须调用这个函数
    //初始化socket完成
    #endif

    st = socket(AF_INET, SOCK_DGRAM, 0);//AF_INET:TCP/IP协议; SOCK_DGRAM:udp;
}

myudp::~myudp()
{
    #ifndef MYLINUX
    closesocket(st);//使用完socket后关闭
    WSACleanup();//释放 win socket内部的相关资源
    #else
    close(st);//使用完socket后关闭
    #endif
}

int myudp::socket_send(const char *IP, int port, char *buf)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;//TCP/IP
    addr.sin_port = htons(port);//端口,htons:host to net short
    addr.sin_addr.s_addr = inet_addr(IP);//127.0.0.1代表给自己发信息

    size_t rc = 0;
    rc = sendto(st, buf, strlen(buf), 0, (struct sockaddr *)&addr, sizeof(addr));

    return rc;
}


int myudp::socket_recv(char *buf, int len, char *srcIP)
{
    struct sockaddr_in sendaddr;
    memset(&sendaddr, 0, sizeof(sendaddr));
    #ifndef MYLINUX
    int addrlen;
    #else
    socklen_t addrlen;
    #endif
    addrlen = sizeof(sendaddr);

    //接收udp数据

    int rc = recvfrom(st, buf, len, 0, (struct sockaddr *)&sendaddr, &addrlen);
    strcpy(srcIP,inet_ntoa(sendaddr.sin_addr));//这个函数是不可重入函数,将IP转化成字符串
    return rc;
}

int myudp::socket_bind(int port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;//TCP/IP
    addr.sin_port = htons(port);//端口,htons:host to net short
    addr.sin_addr.s_addr = htonl(INADDR_ANY);//htonl 将long转化成网络字节
    return bind(st, (struct sockaddr *)&addr, sizeof(addr));//将端口号和程序绑定，绑定失败返回-1
}


