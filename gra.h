#ifndef GRA_H
#define GRA_H

#include <QDebug>
#include "pole.h"
#include <QByteArray>

class Gra : public QObject {

    friend class GameServer;
    Q_OBJECT

public:  
    typedef enum
    {
      G_KOLKO   = 0,
      G_KRZYZYK = 1
    } gracz_t;

    typedef enum
    {
      WYGRYWA_KOLKO     = -1,
      REMIS             =  0,
      WYGRYWA_KRZYZYK   =  1,
      NIEROZSTRZYGNIETA =  2
    } rezultat_t;

    explicit Gra(QObject *parent = nullptr);

    rezultat_t rezultat_gry();
    //int ocen_rezultat();
    void zmien_gracza();
    void czysc_plansze();
    QByteArray pokazPlansze();

    int nrPola;

    ~Gra();

private:
    Pole **pole;
    rezultat_t rezultat;
    gracz_t aktualny_gracz;

public slots:
    void wybranoPole(int i);
};

#endif // GRA_H
