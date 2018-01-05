#pragma once
#include "BazaPracownikow.h"
class MenedzerPlikow
{
private:

	//jw
	MenedzerPlikow(const MenedzerPlikow&);
	//jw
	MenedzerPlikow& operator=(MenedzerPlikow&);
	int liczbaPlikow;
	bool dodanoPracownika;
	bool usunietoPracownika;
	std::string nazwaPliku;
	std::string sciezka;
	std::string* tablicaPlikow = nullptr;
	void zapiszNazwePlikuDoTablicy(std::string& nazwaPliku);
	void przytnijSciezke(std::string& sciezka, size_t dlugoscSciezki);
	bool czySciezkaIstnieje(const std::string& sciezka, const std::string& nazwaPliku);
	bool czyPlikIstnieje(const std::string& file);
	void resetujTablicePlikow();
public:
	MenedzerPlikow(std::string nazwaPliku, bool czyDodano = false, bool czyUsunieto = false);
	void zapiszDoPliku(bool& czySukces, BazaPracownikow& baza);
	void wczytajDanezPliku(BazaPracownikow& baza, bool& failed);
	void wyswietlPlikiBazDanych();
	void wczytajWybranyPlikBazdyDanych(std::string& nazwaPliku, BazaPracownikow& baza, bool& failed);
	~MenedzerPlikow();
};

