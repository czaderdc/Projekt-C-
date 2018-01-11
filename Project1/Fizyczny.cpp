
#include "Fizyczny.h"





Fizyczny::Fizyczny(std::string imie, std::string nazwisko, int zarobki, int id, std::string pozycja) : Pracownik(imie, nazwisko, zarobki, id, pozycja)
{
}

void Fizyczny::nadajPrzelozonego(Dyrektor& przelozony)
{
	przelozony_ = przelozony;
}

void Fizyczny::zapiszNaDanySystemzmianowy(int ileZmian)
{
	ileZmian = ileZmian;
}


Fizyczny::~Fizyczny()
{
}
