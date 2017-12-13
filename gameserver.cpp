#include "gameserver.h"

GameServer::GameServer(QObject *parent) : QObject(parent)
{
    serwer = new QTcpServer(this);
    serwer->listen(QHostAddress::Any,2222);
    if (serwer->isListening()) {
        qDebug() << "Serwer działa.";
    }
    connect(serwer,SIGNAL(newConnection()),this, SLOT(acceptConnection()));
}

void GameServer::acceptConnection()
{
    client = serwer->nextPendingConnection();
    nowa_gra = new Gra;
    connect(client,SIGNAL(readyRead()),this, SLOT(readyRead()));
}

void GameServer::readyRead()
{
    QByteArray dane;
    dane = client->readAll();
    int input = int(dane.at(0))-48;
    if (input>=0 && input<=8) {
        nowa_gra->wybranoPole(input);
    }
    client->write(nowa_gra->pokazPlansze());
    qDebug() << input;
}

GameServer::~GameServer()
{
    client->abort();
    serwer->disconnect();
}
