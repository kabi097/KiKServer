#include "gameserver.h"

GameServer::GameServer(QObject *parent) : QObject(parent)
{
    serwer = new QTcpServer(this);
    serwer->listen(QHostAddress::Any,2222);
    if (serwer->isListening()) {
        qDebug() << "Serwer działa.";
    } else {
        qDebug() << "Błąd: Serwer się nie uruchomił!";
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
    QByteArray dane = client->read(120);
    //odczytałem dane.length();
    qDebug() << dane;
    const char *tmp = dane.constData();

    struct Gra::wiadomosc *wiad = (struct Gra::wiadomosc *) tmp; //dane.constData();

    switch (wiad->type) {
    case Gra::POTWIERDZENIE:

        break;
    case Gra::WIAD_TEKST:
        qDebug() << wiad->dane.czat.napis;
        break;
    case Gra::RUCH:
        qDebug() << wiad->dane.ruch.x;
        qDebug() << wiad->dane.ruch.y;
        break;
    case Gra::PODDAJ:
        qDebug() << "Poddałem sie";
        qDebug() << wiad->dane.poddanie.poddalSie;
        break;
    default:
        qDebug() << "Nie można odczytać";
        break;
    }

//    int input = int(dane.at(0))-1;
//    qDebug() << input;
//    if (input>=0 && input<=8) {
//        nowa_gra->wybranoPole(input);
//    }
//    client->write(nowa_gra->pokazPlansze());
//    qDebug() << input;
}

GameServer::~GameServer()
{
    client->abort();
    serwer->disconnect();
}
