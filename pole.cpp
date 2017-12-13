#include "pole.h"

Pole::Pole(int nr, QObject *parent) : QObject(parent)
{
    nrPola = nr;
    aktualna_wartosc = BRAK;
}

bool Pole::zaznacz_ruch(Pole::ruch_t nowa_wartosc)
{
    if (aktualna_wartosc != BRAK) {
      return false;
    } else {
        if (nowa_wartosc == KRZYZYK) {
            //setText("X");
        } else {
            //setText("O");
        }
        aktualna_wartosc = nowa_wartosc;
        return true;
    }
}

//void Pole::mouseReleaseEvent(QMouseEvent *e)
//{
//    emit wybrano(nrPola);
//    //QAbstractButton::mouseReleaseEvent(e);
//}

void Pole::resetuj()
{
    aktualna_wartosc = BRAK;
    //setText("");
}
