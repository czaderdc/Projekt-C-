#include "Dyrektor.h"





Dyrektor::Dyrektor(std::string imie, std::string nazwisko, int zarobki, int id, std::string pozycja) : Pracownik(imie, nazwisko, zarobki, id, pozycja)
{

}
Dyrektor::Dyrektor()
{

}

void Dyrektor::wyswietlPodleglychPracownikow() const
{
	if (podlegliPracownicy.empty())
	{
		std::cout << std::endl<<"Ten dyrektor nie ma zadnych podleglych pracownikow!"<<std::endl;
		return;
	}

	std::cout << std::endl << "Podlegli pracownicy: " << std::endl;
	for (auto i = podlegliPracownicy.begin(); i != podlegliPracownicy.end(); i++)
	{
		std::cout << std::endl << i->pobierzImie() << " " << i->pobierzNazwisko() <<std::endl;
	}
}

Dyrektor::Dyrektor(const Dyrektor & dyrektor) : Pracownik(dyrektor)
{
}

void Dyrektor::dodajPodleglegoPracownika(const Pracownik& pracownik)
{
	podlegliPracownicy.push_back(pracownik);
}


Dyrektor::~Dyrektor()
{
}
