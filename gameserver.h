#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "gra.h"

class GameServer : public QObject
{
Q_OBJECT

public:
    GameServer(QObject *parent = Q_NULLPTR);
    ~GameServer();

public slots:
    void acceptConnection();
    void readyRead();

private:
    QTcpServer *serwer;
    QTcpSocket *client;
    Gra *nowa_gra;
};

#endif // GAMESERVER_H
