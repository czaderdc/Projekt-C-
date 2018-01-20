#pragma once
#include "Pracownik.h"
#include "Dyrektor.h"
#include "Komunikat.h"
class Fizyczny : public Pracownik
{

private:
	Dyrektor przelozony_;
	int ileZmian_;
public:
	Fizyczny(std::string imie, std::string nazwisko, int zarobki, int id, std::string pozycja = "Pracownik Fizyczny");
	Fizyczny(const Fizyczny& fizyczny);
	Fizyczny& operator=(const Fizyczny& fizyczny);
	void nadajPrzelozonego(Dyrektor& przelozony);
	void zapiszNaDanySystemzmianowy(int ileZmian);
	virtual ~Fizyczny();
};

