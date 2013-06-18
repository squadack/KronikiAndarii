﻿#include "oknogracza.h"

OknoGracza::OknoGracza(QFrame* rama)
{
	layoutGlowny = new QVBoxLayout();
	rama->setLayout(layoutGlowny);
//------------------------------
	pierwszaLinijka = new QLabel();
//------------------------------
	opisPrzedZdrowiem = new QLabel("Zdrowie:");
	wskaznikZdrowia = new MojPasek(0, 0, Qt::red, Qt::green);
	opisPoZdrowiu = new QLabel("_/_");
//	regeneracja = new QLabel();
//	regeneracjaIkona = new QLabel();
//	regeneracjaIkona->setPixmap(QString(IKONKA_REGENERACJA));

	linijkaZdrowia = new QHBoxLayout();
	linijkaZdrowia->addWidget(opisPrzedZdrowiem);
	linijkaZdrowia->addWidget(wskaznikZdrowia);
	linijkaZdrowia->addWidget(opisPoZdrowiu);
//	linijkaZdrowia->addWidget(regeneracjaIkona);
//	linijkaZdrowia->addWidget(regeneracja);
//------------------------------
	opisPrzedDoswiadczeniem = new QLabel("Poziom: _");
	wskaznikDoswiadczenia = new MojPasek(0, Qt::blue);
	opisPoDoswiadczeniu = new QLabel("_/_");
	linijkaDoswiadczenia = new QHBoxLayout();
	linijkaDoswiadczenia->addWidget(opisPrzedDoswiadczeniem);
	linijkaDoswiadczenia->addWidget(wskaznikDoswiadczenia);
	linijkaDoswiadczenia->addWidget(opisPoDoswiadczeniu);
//------------------------------
	reputacja = new QHBoxLayout();
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
	{
		slupkiLayouts[i] = new QVBoxLayout();
		slupki[i] = new MojPasek(MAX_REPUTACJA, 0, Qt::yellow);
		podpisy[i] = new QLabel(KROLESTWA[i]);
		slupkiLayouts[i]->addWidget(slupki[i]);
		slupkiLayouts[i]->addWidget(podpisy[i]);

		reputacja->addLayout(slupkiLayouts[i]);
	}
//------------------------------
	obronaIkona = new QLabel();
	obronaIkona->setPixmap(IKONKA_OBRONA);
	obrona = new QLabel();
	percepcjaIkona = new QLabel();
	percepcjaIkona->setPixmap(IKONKA_PERCEPCJA);
	percepcja = new QLabel();
	ruchIkona = new QLabel();
	ruchIkona->setPixmap(IKONKA_RUCH);
	ruch = new QLabel();

	linijkaObrony = new QHBoxLayout();
	linijkaObrony->addWidget(obronaIkona);
	linijkaObrony->addWidget(obrona);
	linijkaObrony->addWidget(percepcjaIkona);
	linijkaObrony->addWidget(percepcja);
	linijkaObrony->addWidget(ruchIkona);
	linijkaObrony->addWidget(ruch);
//------------------------------
	wreczIkona = new QLabel();
	wreczIkona->setPixmap(IKONKA_WRECZ);
	wrecz = new QLabel();
	dystansIkona = new QLabel();
	dystansIkona->setPixmap(IKONKA_DYSTANSOWY);
	dystans = new QLabel();
	magiaIkona = new QLabel();
	magiaIkona->setPixmap(IKONKA_MAGICZNY);
	magia = new QLabel();

	linijkaAtakow = new QHBoxLayout();
	linijkaAtakow->addWidget(wreczIkona);
	linijkaAtakow->addWidget(wrecz);
	linijkaAtakow->addWidget(dystansIkona);
	linijkaAtakow->addWidget(dystans);
	linijkaAtakow->addWidget(magiaIkona);
	linijkaAtakow->addWidget(magia);
//------------------------------
	zlotoIkona = new QLabel();
	zlotoIkona->setPixmap(IKONKA_ZLOTO);
	zloto = new QLabel();

	linijkaZlota = new QHBoxLayout();
	linijkaZlota->addWidget(zlotoIkona);
	linijkaZlota->addWidget(zloto);
//------------------------------
	linijkaPrzyciskow = new QHBoxLayout();
	zadania = new QPushButton(QString::fromUtf8("Przejrzyj zadania"));
	ekwipunek = new QPushButton(QString::fromUtf8("Przejrzyj ekwipunek"));
	linijkaPrzyciskow->addWidget(ekwipunek);
	linijkaPrzyciskow->addWidget(zadania);

	connect(ekwipunek, SIGNAL(clicked()), this, SLOT(pokazEkwipunek()));
	connect(zadania, SIGNAL(clicked()), this, SLOT(pokazZadania()));

//------------------------------
	layoutGlowny->addWidget(pierwszaLinijka);
	layoutGlowny->addLayout(linijkaZdrowia);
	layoutGlowny->addLayout(linijkaDoswiadczenia);
	layoutGlowny->addLayout(reputacja);
	layoutGlowny->addLayout(linijkaObrony);
	layoutGlowny->addLayout(linijkaAtakow);
	layoutGlowny->addLayout(linijkaZlota);
	layoutGlowny->addLayout(linijkaPrzyciskow);
}

/**
 * @brief OknoGracza::wyswietlGracz	Wyświetla dane podanego gracza.
 * @param gracz
 */
void OknoGracza::wyswietlGracza(Gracz *gracz)
{
	aktualnyGracz = gracz;
	pierwszaLinijka->setText(gracz->getNazwa() + ", " + RASY[gracz->getRasa()] + ", " + KLASY[gracz->getKlasa()]);
//------------------------------
	wskaznikZdrowia->wypelnijPierwszy((qreal)gracz->getZdrowieAktualne() / gracz->getZdrowieMaks());
	wskaznikZdrowia->wypelnijDrugi((qreal)gracz->getRegeneracja() / gracz->getZdrowieMaks());
	opisPoZdrowiu->setText(QString::number(gracz->getZdrowieAktualne()) + QString("/") + QString::number(gracz ->getZdrowieMaks())
				+ QString(" (") + QString::number(gracz->getRegeneracja()) + QString(")") );
//	regeneracja ->setText(QString::number(gracz->getRegeneracja()) + QString::fromUtf8("/turę"));
//------------------------------
	opisPrzedDoswiadczeniem->setText(QString("Poziom: ") + QString::number(gracz->getPoziom()));
	int ileDoswNaAktualnyPoziom = GRANICE_POZIOMOW[gracz->getPoziom()] - GRANICE_POZIOMOW[gracz->getPoziom() - 1];
	int ileDoswZebranoNaAktPoziomie = gracz->getDoswiadczenie() - GRANICE_POZIOMOW[gracz->getPoziom() - 1];
	wskaznikDoswiadczenia->wypelnij((qreal)ileDoswZebranoNaAktPoziomie / ileDoswNaAktualnyPoziom );
	opisPoDoswiadczeniu->setText(QString::number(ileDoswZebranoNaAktPoziomie) + QString("/") + QString::number(ileDoswNaAktualnyPoziom));
//------------------------------
	for(int i = 0; i < LICZBA_KROLESTW; ++i)
		slupki[i]->ustaw(gracz->getReputacja()[i]);
//------------------------------
	obrona->setText(QString::number(gracz->getObrona()));
	percepcja->setText(QString::number(gracz->getPercepcja()));
	ruch->setText(QString::number(gracz->getPunktyRuchu()));
//------------------------------
	wrecz->setText(QString::number(gracz->getAtakWrecz()));
	dystans->setText(QString::number(gracz->getAtakDystansowy()));
	magia->setText(QString::number(gracz->getAtakMagiczny()));
//------------------------------
	zloto->setText(QString::number(gracz->getZloto()) + odmiana(gracz->getZloto()));
//------------------------------

	if(gracz->getCzyAI())
	{
		zadania->setEnabled(false);
		ekwipunek->setEnabled(false);
	}
	else
	{
		zadania->setEnabled(true);
		ekwipunek->setEnabled(true);
	}

	qDebug() <<"Okno Gracza wyswietlilo dane: " <<gracz->getNazwa();
}

/**
 * @brief OknoGracza::uaktualnijInformacje	Odświeża dane i powiadamia o zmianie
 */
void OknoGracza::uaktualnijInformacje()
{
	mistrz->poinformujPlansze();
	wyswietlGracza(aktualnyGracz);
}

void OknoGracza::setMistrzGry(MistrzGry *mistrz)
{
	this->mistrz = mistrz;
}

/**
 * @brief OknoGracza::odmiana Odmienia słowo "sztuka" zależnie od liczby sztuk złota
 * @param n ile sztuk
 * @return
 */
QString OknoGracza::odmiana(int n)
{
	if(n == 1)
		return QString(" sztuka");
	if(n > 1 && n < 5)
		return QString(" sztuki");
	return QString(" sztuk");
}

/**
 * @brief OknoGracza::pokazEkwipunek Wywołuje Okno Ekwipunek
 */
void OknoGracza::pokazEkwipunek()
{
	oknoEkwipunek = new OknoEkwipunek(aktualnyGracz, this);
	oknoEkwipunek->setAttribute(Qt::WA_DeleteOnClose);
	oknoEkwipunek->show();
}

/**
 * @brief OknoGracza::pokazZadania	Wywołuje Okno Zadania
 */
void OknoGracza::pokazZadania()
{
	oknoZadania = new OknoZadania(aktualnyGracz, mistrz->getPlansza());
	oknoZadania->setAttribute(Qt::WA_DeleteOnClose);
	oknoZadania->show();
}
