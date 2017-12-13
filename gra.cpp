#include "gra.h"

Gra::Gra(QObject *parent) : QObject(parent)
{
    int col=0;
    pole = new Pole*[9];
    for (int i=0; i<9; i++) {
        pole[i] = new Pole(i);
        connect(pole[i],SIGNAL(wybrano(int)),this,SLOT(wybranoPole(int)));
        if (i%3==2) col++;
    }

    rezultat = NIEROZSTRZYGNIETA;
    aktualny_gracz = G_KOLKO;
}

Gra::rezultat_t Gra::rezultat_gry()
{
    //Sprawdzanie wierszy
    for (int y=0; y<3; y++)
    {
      if ((pole[3*y]->aktualna_wartosc == pole[3*y + 1]->aktualna_wartosc) && (pole[3*y]->aktualna_wartosc == pole[3*y + 2]->aktualna_wartosc))
      {
        if (pole[3*y]->aktualna_wartosc  == Pole::KOLKO)
          return WYGRYWA_KOLKO;
        if (pole[3*y]->aktualna_wartosc  == Pole::KRZYZYK)
          return WYGRYWA_KRZYZYK;
      }
    }
    //Sprawdzanie kolumn
    for (int x=0; x<3; x++)
    {
      if ((pole[x]->aktualna_wartosc == pole[x + 3]->aktualna_wartosc) && (pole[x]->aktualna_wartosc == pole[x + 6]->aktualna_wartosc))
      {
        if (pole[x]->aktualna_wartosc  == Pole::KOLKO)
          return WYGRYWA_KOLKO;
        if (pole[x]->aktualna_wartosc  == Pole::KRZYZYK)
          return WYGRYWA_KRZYZYK;
      }
    }
    //Sprawdzanie przekątnych
    if ((pole[0]->aktualna_wartosc == pole[4]->aktualna_wartosc) && (pole[0]->aktualna_wartosc == pole[8]->aktualna_wartosc))
    {
      if (pole[4]->aktualna_wartosc  == Pole::KOLKO)
        return WYGRYWA_KOLKO;
      if (pole[4]->aktualna_wartosc  == Pole::KRZYZYK)
        return WYGRYWA_KRZYZYK;
    }
    if ((pole[2]->aktualna_wartosc == pole[4]->aktualna_wartosc) && (pole[2]->aktualna_wartosc == pole[6]->aktualna_wartosc))
    {
      if (pole[4]->aktualna_wartosc  == Pole::KOLKO)
        return WYGRYWA_KOLKO;
      if (pole[4]->aktualna_wartosc  == Pole::KRZYZYK)
        return WYGRYWA_KRZYZYK;
    }
    //sprawdzanie możliwości wykonania ruchu

    for (int i=0; i<9; i++)
      if (pole[i]->aktualna_wartosc == Pole::BRAK)
        return NIEROZSTRZYGNIETA;

    return REMIS;
}

void Gra::zmien_gracza()
{
    if (aktualny_gracz == G_KOLKO) {
        aktualny_gracz = G_KRZYZYK;
    } else {
        aktualny_gracz = G_KOLKO;
    }
}

void Gra::czysc_plansze()
{
    for (int i=0; i<9; i++) {
        pole[i]->resetuj();
    }
}

QByteArray Gra::pokazPlansze()
{
    QByteArray plansza;
    for (int i=0; i<9; i++) {
        if (pole[i]->aktualna_wartosc == Pole::BRAK) plansza.append('0');
        if (pole[i]->aktualna_wartosc == Pole::KOLKO) plansza.append('1');
        if (pole[i]->aktualna_wartosc == Pole::KRZYZYK) plansza.append('2');
    }
    plansza.append('\0');
    return plansza;
}

Gra::~Gra()
{
}

void Gra::wybranoPole(int i)
{
    Pole::ruch_t ruch;
    if (aktualny_gracz==G_KOLKO) ruch = Pole::KOLKO;
    if (aktualny_gracz==G_KRZYZYK) ruch = Pole::KRZYZYK;
    if (pole[i]->zaznacz_ruch(ruch) == true) {
        if (rezultat_gry()!=NIEROZSTRZYGNIETA) {
            //KONIEC GRY
            if (rezultat_gry()==WYGRYWA_KOLKO) {
                //okno.setInformativeText("Wygrało kółko.");
            } else if (rezultat_gry()==WYGRYWA_KRZYZYK) {
                //okno.setInformativeText("Wygrał krzyżyk.");
            } else {
                //okno.setInformativeText("REMIS");
            }
            czysc_plansze();
        } else {
            zmien_gracza();
        }
    }
}
