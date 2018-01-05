
#include "KlasaPomocnicza.h"

using namespace std;
KlasaPomocnicza::KlasaPomocnicza()
{
}


void KlasaPomocnicza::wprowadzDane(string& imie, string& nazwisko, string& zarobki)
{

	std::cout << endl << "Podaj imie: ";
	std::cin >> imie;
	while (!walidatorStringow(imie))
	{
		cout << "Wprowadzono niepoprawne znaki!\n";
		cout << "\nPodaj imie pracownika: ";
		cin >> imie;
	}
	std::cout << endl << "Podaj nazwisko: ";
	std::cin >> nazwisko;
	while (!walidatorStringow(nazwisko))
	{
		cout << "Wprowadzono niepoprawne znaki!\n";
		cout << "\nPodaj nazwisko pracownika: ";
		cin >> nazwisko;
	}
	std::cout << endl << "Podaj zarobki pracownika: ";
	std::cin >> zarobki;
	while (!walidatorStringNaInt(zarobki))
	{
		cout << endl << "Wprowadz prawidlowa liczbe calkowita: ";
		cin >> zarobki;
	}

}

void KlasaPomocnicza::sprawdzanieWyboruUzytkownika(int& integer, bool& czySukces, int zakres)
{

	string pomocnik = "";

	try
	{
		(cin >> pomocnik).get();
		integer = stoi(pomocnik);

		if (integer >0 && integer <= zakres)
		{
			czySukces = true;
		}
		else
		{
			throw out_of_range("");

		}
	}
	catch (out_of_range& ex)
	{
		czySukces = false;
		std::cout << endl << "Nie ma takiej opcji menu!" << endl << "Dostepne sa: 1-" << to_string(zakres) << endl;
		sprawdzanieWyboruUzytkownika(integer, czySukces, zakres);
	}
	catch (exception const &e)//zla praktyka przechwytywania klasy bazowe, trace dokladniejsze dane o bledzie przez to
	{
		czySukces = false;
		std::cout << endl << "Wprowadzono niepoprawny znak!" << endl;
		std::cout << "Wprowadz 1- " << to_string(zakres) << endl;
		sprawdzanieWyboruUzytkownika(integer, czySukces, zakres);

	}


}

bool KlasaPomocnicza::walidatorStringNaInt(string zarobki)
{
	for (size_t i = 0; i < zarobki.length(); i++)
	{
		if (!isdigit(zarobki[i]))
			return false;
	}
	try
	{
		int wynik = stoi(zarobki);
	}
	catch (out_of_range& exception)
	{
		cout << endl << "Wprowadzona liczba jest za duza na ten program!";
		return false;
	}
	catch (invalid_argument& arg)
	{
		cout << endl << "Wprowadzono niepoprawny znak!";
	}
	return true;
}

bool KlasaPomocnicza::czyPoprawnaNazwa(string & nazwa)
{
	for (size_t i = 0; i < nazwa.length(); i++)
	{
		if (!isalpha(nazwa[i]))
		{
			cout << endl << "Wprowadzono niedozwolony znak: ";
			cout << nazwa[i];
			cout << endl << "Dostepne sa tylko litery a-z A-Z bez polskich znakow\n";
			return false;
		}
	}
	return true;
}


bool KlasaPomocnicza::walidatorStringow(string& s)
{
	for (size_t i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]) || (!isalpha(s[i])))
			return false;
	}
	return true;
}

KlasaPomocnicza::~KlasaPomocnicza()
{
}
