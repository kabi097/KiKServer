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
//    QByteArray output = client->read(sizeof(int));
//    QDataStream out(&output, QIODevice::ReadOnly);
//    char text[80];
//    Gra::type_t type;
//    out >> size;
//    out >> type;
//    if (client->bytesAvailable()>0) {

//    }

//    qint32 *s = sizes.value(socket);
//    qint32 size = *s;
//    while (socket->bytesAvailable() > 0)
//    {
//        buffer->append(socket->readAll());
//        while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) //While can process data, process it
//        {
//            if (size == 0 && buffer->size() >= 4) //if size of data has received completely, then store it on our global variable
//            {
//                size = ArrayToInt(buffer->mid(0, 4));
//                *s = size;
//                buffer->remove(0, 4);
//            }
//            if (size > 0 && buffer->size() >= size) // If data has received completely, then emit our SIGNAL with the data
//            {
//                QByteArray data = buffer->mid(0, size);
//                buffer->remove(0, size);
//                size = 0;
//                *s = size;
//                emit dataReceived(data);
//            }
//        }
//    }
    QByteArray dane = client->readAll();
    //odczytałem dane.length();
    const char *tmp = dane.constData();

    struct Gra::wiadomosc *wiad = (struct Gra::wiadomosc *) tmp; //dane.constData();

    qDebug()<<"Typ wiadomości = " << wiad->type<<"\n";

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
