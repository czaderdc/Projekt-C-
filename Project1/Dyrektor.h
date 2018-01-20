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
	Dyrektor& operator=(const Dyrektor& dyrektor);
	void wyswietlPodleglychPracownikow()const;
	void dodajPodleglegoPracownika(const Pracownik& pracownik);
	void usunPodleglegoPracownika(int idPracownika);
	virtual ~Dyrektor();
private:
	std::vector<Pracownik> podleglipracownicy;
};

