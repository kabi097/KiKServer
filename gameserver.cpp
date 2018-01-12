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
        send->type = Gra::PLANSZA;
        send->dane.mojaMapa.plansza = nowa_gra->pokazPlansze();
        send->length = sizeof(bajty);
        client->write(bajty, send->length);
        if (nowa_gra->rezultat_gry() != Gra::REMIS) {
            send->type = Gra::POTWIERDZENIE;
            send->dane.potwierdzenie.rezultat = (uint8_t)nowa_gra->rezultat_gry();
            send->length = sizeof(bajty);
            client->write(bajty, send->length);
        }
        qDebug() << "X: " << wiad->dane.ruch.x;
        qDebug() << "Y: " << wiad->dane.ruch.y;
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
