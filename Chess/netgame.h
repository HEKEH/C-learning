#ifndef NETGAME_H
#define NETGAME_H
#include "Board.h"
#include <QTcpServer>
#include <QTcpSocket>

class NetGame : public Board
{
    Q_OBJECT
public:
    explicit NetGame(bool server, QWidget *parent = nullptr);
    QTcpServer* _server;
    QTcpSocket* _socket;
    bool _bServer;

    void initFromNet(QByteArray ba);
    void click(int id, int row, int col);
    void clickFromNet(QByteArray ba);
    void backFromNet();

public slots:
    void slotNewconnection();
    void slotDataArrive();
    void slotBack();
};

#endif // NETGAME_H
