
#include "Fizyczny.h"





Fizyczny::Fizyczny(std::string imie, std::string nazwisko, int zarobki, int id, std::string pozycja) : Pracownik(imie, nazwisko, zarobki, id, pozycja)
{
}

Fizyczny::Fizyczny(const Fizyczny & fizyczny) : Pracownik(fizyczny)
{
	przelozony_ = fizyczny.przelozony_;
	ileZmian_ = fizyczny.ileZmian_;
}

Fizyczny & Fizyczny::operator=(const Fizyczny & fizyczny)
{
	if (this == &fizyczny || *this == fizyczny)
		return *this;
	Pracownik::operator=(fizyczny);
	this->ileZmian_ = fizyczny.ileZmian_;
	return *this;
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
