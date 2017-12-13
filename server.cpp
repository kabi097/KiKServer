#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    qDebug() << "Hello world!";
    serwer = new QTcpServer(this);
    if (serwer->listen(QHostAddress::Any,2222)==true) {
        qDebug() << "Server started";
    } else {
        qDebug() << "Error";
    }
    connect(serwer,SIGNAL(newConnection()),this,SLOT(acceptConncetion()));
}

Server::~Server()
{
    serwer->close();
    qDebug() << "Zakończono";
}

void Server::acceptConncetion()
{
    qDebug() << "New connection coming...";
    QTcpSocket *newsocket = serwer->nextPendingConnection();
    newsocket->write("z");
    newsocket->flush();
    newsocket->close();
}
