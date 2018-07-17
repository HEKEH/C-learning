#ifndef UDP_H
#define UDP_H

#ifdef MYLINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#else
#include <winsock2.h>
#endif

class myudp
{
private:
    SOCKET st;
public:
    myudp();
    ~myudp();
    int socket_send(const char *IP, int port, char *buf);
    int socket_recv(char *buf, int len, char *srcIP);
    int socket_bind(int port);
};

#endif // UDP_H
