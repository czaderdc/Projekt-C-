#include "Dyrektor.h"





Dyrektor::Dyrektor(std::string imie, std::string nazwisko, int zarobki, int id, std::string pozycja) : Pracownik(imie, nazwisko, zarobki, id, pozycja)
{

}
Dyrektor::Dyrektor()
{

}

void Dyrektor::wyswietlPodleglychPracownikow() const
{
	if (podleglipracownicy.empty())
	{
		std::cout << std::endl<<"Ten dyrektor nie ma zadnych podleglych pracownikow!"<<std::endl;
		return;
	}

	std::cout << std::endl << "Podlegli pracownicy: " << std::endl;
	for (auto i = podleglipracownicy.begin(); i != podleglipracownicy.end(); i++)
	{
		std::cout << std::endl << i->pobierzImie() << " " << i->pobierzNazwisko() <<std::endl;
	}
}

Dyrektor::Dyrektor(const Dyrektor & dyrektor) : Pracownik(dyrektor)
{
}

void Dyrektor::dodajPodleglegoPracownika(const Pracownik& pracownik)
{
	podleglipracownicy.push_back(pracownik);
}

void Dyrektor::usunPodleglegoPracownika(int idPracownika)
{
	for (auto i = podleglipracownicy.begin(); i!= podleglipracownicy.end(); i++)
	{
		if (i->pobierzID() == idPracownika)
		{
			podleglipracownicy.erase(i);
		}
	}
}


Dyrektor::~Dyrektor()
{
}
