#ifndef SERVER_H
#define SERVER_H

#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

signals:

public slots:
    void acceptConncetion();

private:
    QTcpServer *serwer;
};

#endif // SERVER_H
