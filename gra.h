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
        POTWIERDZENIE,
        WIAD_TEKST,
        RUCH,
        PODDAJ,
        PLANSZA
    } type_t;

    typedef struct {
        Pole::ruch_t ruchy[9];
    } plansza_t;

    struct wiadomosc
    {
        uint8_t sync;
        uint8_t type;
        uint8_t length;
        union
        {
            struct
            {
                uint8_t poddalSie;
            } poddanie;

            struct
            {
                int rezultat;
            } potwierdzenie;

            struct
            {
                char napis[80];
            } czat;

            struct
            {
                uint8_t x;
                uint8_t y;
            } ruch;

            struct {
                plansza_t plansza;
            } mojaMapa;
        } dane;
    }  __attribute__ ((packed));

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

    int rezultat_gry();
    //int ocen_rezultat();
    void zmien_gracza();
    void czysc_plansze();
    plansza_t pokazPlansze();

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
