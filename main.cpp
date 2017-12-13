#include <QCoreApplication>
#include "gra.h"
#include "gameserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GameServer serwer;
    return a.exec();
}
