#include "NetGame.h"

NetGame::NetGame(bool server, QWidget *parent) : Board(parent)
{
    _server = NULL;
    _socket = NULL;
    _bServer = server;

    if(_bServer)
    {
        _server = new QTcpServer(this);
        _server->listen(QHostAddress::Any, 8088);
        connect(_server, SIGNAL(newConnection()), this, SLOT(slotNewconnection()));
    }
    else
    {
        _socket = new QTcpSocket(this);
        _socket->connectToHost("127.0.0.1", 8088);
        connect(_socket, SIGNAL(readyRead()), this, SLOT(slotDataArrive()));

    }


}

void NetGame::slotNewconnection()
{
    //qDebug() << "connect";
    if (_socket) return;
    _socket = _server->nextPendingConnection();
    connect(_socket, SIGNAL(readyRead()), this, SLOT(slotDataArrive()));

    bool bRedSide = true;
    init(bRedSide);
    char buf[2];
    buf[0] = 1;
    buf[1] = bRedSide?0:1;
    _socket->write(buf);
}

void NetGame::slotDataArrive()
{
    QByteArray ba = _socket->readAll();
    char cmd = ba[0];
    switch(cmd)
    {
        case 1:
        {
            initFromNet(ba);
            break;
        }
        case 2:
        {
            clickFromNet(ba);
            break;
        }
        case 3:
        {
            backFromNet();
            break;
        }
    }
}

void NetGame::initFromNet(QByteArray ba)
{
    char data = ba[1];
    init(data == 1);
}

void NetGame::click(int id, int row, int col)
{
    if(_redTurn != _bRedSide){
        return;
    }
    Board::click(id, row, col);
    QByteArray buf;
    buf[0] = 2;
    buf[1] = 9 - row;
    buf[2] = 8 - col;
    buf[3] = id;
    //qDebug() << id;
    _socket->write(buf);
}

void NetGame::clickFromNet(QByteArray ba)
{
    int row = ba[1];
    int col = ba[2];
    int id = ba[3];
    //qDebug() << ba[3];
    Board::click(id, row, col);
}

void NetGame::backFromNet()
{
    backOne();
    backOne();
}

void NetGame::slotBack()
{
    if(_redTurn != _bRedSide){
        return;
    }
    QByteArray buf;
    buf[0] = 3;
    _socket->write(buf);
    backOne();
    backOne();
}
