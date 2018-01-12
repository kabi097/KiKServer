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
    QByteArray dane = client->readAll();
    //odczytałem dane.length();
    const char *tmp = dane.constData();
    struct Gra::wiadomosc *wiad = (struct Gra::wiadomosc *) tmp; //dane.constData();
    char bajty[120];
    struct Gra::wiadomosc *send = (struct Gra::wiadomosc *) bajty;

    switch (wiad->type) {
    case Gra::POTWIERDZENIE:

        break;
    case Gra::WIAD_TEKST:
        qDebug() << wiad->dane.czat.napis;
        strcpy(send->dane.czat.napis,"No siema");
        send->type = Gra::WIAD_TEKST;
        send->length = sizeof(bajty);
        client->write(bajty, send->length);
        break;
    case Gra::RUCH:
        nowa_gra->wybranoPole(3*wiad->dane.ruch.x+wiad->dane.ruch.y);
        if (nowa_gra->rezultat_gry() == Gra::NIEROZSTRZYGNIETA) {
            send->type = Gra::PLANSZA;
            send->dane.mojaMapa.plansza = nowa_gra->pokazPlansze();
            send->length = sizeof(bajty);
        } else {
            send->type = Gra::POTWIERDZENIE;
            send->dane.potwierdzenie.rezultat = nowa_gra->rezultat_gry();
            qDebug() << nowa_gra->rezultat_gry();
            send->length = sizeof(bajty);
            nowa_gra->czysc_plansze();
        }
        client->write(bajty, send->length);
        qDebug() << "X:" << wiad->dane.ruch.x << " Y:" << wiad->dane.ruch.y;
        break;
    case Gra::PODDAJ:
        qDebug() << "Poddałem sie";
        qDebug() << wiad->dane.poddanie.poddalSie;
        break;
    default:
        qDebug() << "Nie można odczytać";
        break;
    }
}

GameServer::~GameServer()
{
    client->abort();
    serwer->disconnect();
}
