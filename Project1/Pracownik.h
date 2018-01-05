#pragma once
#include <string>
#include <iostream>
class Pracownik
{
private:
	std::string imie_;
	std::string nazwisko_;
	int zarobki_;
	int id_;
	std::string pozycja_;
public:
	int pobierzID() const;
	Pracownik();
	std::string pobierzPozycje()const { return pozycja_; }
	Pracownik(std::string imie, std::string nazwisko, int zarobki, int id, std::string pozycja = "Pracownik Fizyczny");
	Pracownik(const Pracownik&p);
	//metody do pobierania dlugosci Imienia Nazwiska w celu prawidlowego sformatowania wyswietlenia tabeli
	size_t imieLength() const { return imie_.length(); }
	size_t nazwiskoLength() { return nazwisko_.length(); }
	Pracownik& operator=(const Pracownik&p);
	const std::string& pobierzImie() const { return imie_; }
	void ustawImie(std::string& noweImie) { imie_ = noweImie; }
	const std::string& pobierzNazwisko()const { return nazwisko_; }
	const int pobierzZarobki() const { return zarobki_; }
	std::string pobierzPozycje() { return pozycja_; }
	friend std::ostream& operator <<(std::ostream&os, const Pracownik & p);
	bool operator==(const Pracownik&p)const;
	virtual ~Pracownik();

};


