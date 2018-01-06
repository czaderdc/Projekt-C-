#pragma once
#include "Pracownik.h"
#include <vector>
class Dyrektor :
	public Pracownik
{
public:
	Dyrektor(std::string imie, std::string nazwisko, int zarobki, int id, std::string pozycja = "Dyrektor");
	Dyrektor(const Dyrektor& dyrektor);
	Dyrektor();
	void wyswietlPodleglychPracownikow()const;
	void dodajPodleglegoPracownika(const Pracownik& pracownik);
	virtual ~Dyrektor();
private:
	std::vector<Pracownik> podleglipracownicy;
};

