#include "Pracownik.h"

int Pracownik::pobierzID()const
{
	return id_;
}
Pracownik::Pracownik()
{

}

Pracownik::Pracownik(std::string imie, std::string nazwisko, int zarobki, int id, std::string pozycja) : imie_(imie), nazwisko_(nazwisko), zarobki_(zarobki), id_(id), pozycja_(pozycja)
{
	id++;
}

Pracownik::Pracownik(const Pracownik & p) : imie_(p.imie_), nazwisko_(p.nazwisko_), zarobki_(p.zarobki_), id_(p.id_), pozycja_(p.pozycja_)
{
}


Pracownik & Pracownik::operator=(const Pracownik & p)
{
	if (*this == p)
		return *this;
	imie_ = p.imie_;
	zarobki_ = p.zarobki_;
	nazwisko_ = p.nazwisko_;
	id_ = p.id_;
	pozycja_ = p.pozycja_;
	return *this;
}


bool Pracownik::operator==(const Pracownik & p) const
{
	if (imie_ == p.imie_ && nazwisko_ == p.nazwisko_ )
		return true;
	return false;
}



Pracownik::~Pracownik()
{


}

std::ostream & operator<<(std::ostream & os, const Pracownik & p)
{
	return os << "ID: " << p.pobierzID() << std::endl <<
		"Imie pracownika: " << p.pobierzImie() << std::endl <<
		"Nazwisko pracownika: " << p.pobierzNazwisko() << std::endl <<
		"Zarobki pracownika: " << p.pobierzZarobki() << std::endl <<
		"Pozycja pracownika: " << p.pobierzPozycje() << std::endl;




}
