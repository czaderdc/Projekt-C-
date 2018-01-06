#pragma once//== #ifndef Pracownik #define Pracownik $endif
#include <vector>
#include "Pracownik.h"
#include <algorithm>
#include <fstream>
#define PUSTYSTRING ""
#include "Dyrektor.h"
class BazaPracownikow
{
private:
	int idPracownika;
	size_t liczbaPracownikow;
	Pracownik* pracownicy = nullptr;
public:
	BazaPracownikow();
	Dyrektor dyrektor_;
	void aktualizujId(int id) { idPracownika = id; }
	Dyrektor& pobierzDyrektora() { return dyrektor_; }
	void resetujTablicePracownikow();
	const Pracownik& szukajPoId (int Id)const;
	bool czyJestDyrektor();
	void dodajDyrektora(const Dyrektor& dyrektor);
	int nadajID() { return ++idPracownika; }	
	size_t liczbaPracownikowGet() const { return liczbaPracownikow; }
	const Pracownik* pobierzPracownikow()const { return pracownicy; }
	int sumaZarobkowPracownikow()const;
	void realokujTablice(Pracownik&p, bool& failed);
	void dodajPracownikaTablica(Pracownik &p, bool& failed);
	std::string przytnijOpis(std::string opis, std::string liniaTekstu, size_t& pozycja);
	void usunPracownika(int IDpracownika);
	int sumaZarobkowPracownikow();
	void realokujTabliceUsuwam(Pracownik& p);
	std::string operator[](int id)const;
	std::string operator[](std::string nazwisko)const;
	void wyswietlPracownikowTablica();
	~BazaPracownikow();
};

