#ifndef NAGRODA_H
#define NAGRODA_H
#include "przedmiot.h"
#include "gra.h"	 //dlaczego przy wstawieniu przed przedmiot nie działa?
#include <QList>

class Nagroda
{
public:
	Nagroda(quint8 reputacja[], quint16 zloto, quint16 doswiadczenie, quint8 ileLosowych, QList<Przedmiot*> konkrety);

	quint8* getReputacja();
	quint16 getZloto();
	quint16 getDoswiadczenie();
	quint8 getIleLosowych();
	QList<Przedmiot*>* getKonkretnePrzedmioty();

private:
	quint8 reputacja[LICZBA_KROLESTW];
	quint16 zloto;
	quint16 doswiadczenie;
	quint8 ileLosowych;
	QList<Przedmiot*> konkretnePrzedmioty;
};

#endif // NAGRODA_H
