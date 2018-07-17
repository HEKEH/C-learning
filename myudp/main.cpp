#include <iostream>
#include <string.h>
#include "udp.h"

using namespace std;

int main(int argc, char *args[])
{
    myudp udp;
    int port = 8080;

    if (argc > 1)
    {
        char buf[1024] = {0};
        while(1)
        {
            memset(buf, 0, sizeof(buf));
            cin >> buf;
            udp.socket_send(args[1], port, buf);
            if (strcmp(buf, "exit") == 0)
                break;
        }
    } else
    {
        if (udp.socket_bind(port)> -1)
        {
            char buf[1024] = {0};
            int len =sizeof(buf);
            char ip[100] = {0};
            while(1)
            {
                memset(buf, 0, sizeof(buf));
                memset(ip, 0, sizeof(ip));
                udp.socket_recv(buf, len, ip);
                if (strcmp(buf, "exit") == 0)
                    break;
                cout << ip << ": " << buf << endl;
            }
        }
    }
    cout <<  "Over!" << endl;
    return 0;
}
