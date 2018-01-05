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
	//czy aby na pewno powienienem to trzymac na stercie?
	//std::vector<Pracownik>* ListaPracownikow;
	int idPracownika;
	size_t liczbaPracownikow;
	//	stdLL
public:
	Dyrektor dyrektor_;
	Dyrektor& pobierzDyrektora() { return dyrektor_; }
	void resetujTablicePracownikow();
	const Pracownik& szukajPoId (int Id)const;
	bool czyJestDyrektor();
	void dodajDyrektora(const Dyrektor& dyrektor);
	int nadajID() { return ++idPracownika; }
	BazaPracownikow();
	size_t liczbaPracownikowGet() const { return liczbaPracownikow; }
	Pracownik* Pracownicy = nullptr;
	const Pracownik* pobierzPracownikow()const { return Pracownicy; }
	int sumaZarobkowPracownikow();
	//referencje przekazuje aby sledzic ID pracownika, co swiadczy o ilosc pracownikow aby zarezerwowac na biezaco odpowiednia ilosc pamieci
	void realokujTablice(Pracownik&p, bool& failed);
	void dodajPracownikaTablica(Pracownik &p, bool& failed);
	std::string przytnijOpis(std::string opis, std::string liniaTekstu, size_t& pozycja);
	void usunPracownika(int IDpracownika);
	int sumaZarobkowPracownikow() const;
	void realokujTabliceUsuwam(Pracownik& p);
	std::string operator[](int id);
	std::string operator[](std::string nazwisko);
	void wyswietlPracownikowTablica();
	~BazaPracownikow();
};

