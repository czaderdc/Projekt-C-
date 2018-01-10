// ProjektCNaZaliczenie.cpp : Defines the entry point for the console application.
//
//Twórca: Konrad Czado
//Listopad 2017 rok projekt zaliczeniowy C++
//bez u¿ycia STL, opieraj¹c siê na standardziej C++0x z uzyciem kilku udogodnien z nowszych bibliotek
//np filesystem do latwego odnajdywania sciezki pod ktora zlokalizowane sa pliki

#include "BazaPracownikow.h"
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <exception>
#include <Windows.h>
#include "MenedzerPlikow.h"
#include "Dyrektor.h"
#include "Fizyczny.h"
#include "Pracownik.h"





using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void menu();
static bool walidatorStringNaInt(string& zarobki);
void PetlaGlownaProgramou(int &wybor, int &dodatkoweOpcje, BazaPracownikow &bazaDanych, MenedzerPlikow& menedzer);
static void wprowadzDane(std::string& imie, std::string& nazwisko, std::string& zarobki);
static bool walidatorStringow(string& s);
static void sprawdzanieWyboruUzytkownika(int& integer, bool& czySukces, int zakres);
bool czyPoprawnaNazwa(string& nazwa);
//tryb 'o' odczyt hasla z pliku 'z' zapis hasla do pliku
bool hasloPanelDyrektora(string& haslo, char tryb);
//jesli operacja sie powiodla to wyswietl powiadomienie uzytkownikowi
void sukces();
void porazka();
void powiadomienie(const char*);
bool pierwszeUruchomienie = true;
bool czySukces = false;
bool czyKomunikaty = false;

int main()
{
	//system("color F0");


	int wybor = 0;
	std::cout << "Czy wejsc w tryb pelnego ekranu?\n[1]TAK\n[2]NIE\n";
	sprawdzanieWyboruUzytkownika(wybor, czySukces, 2);
	if (wybor == 1)
	{
		::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	}
	//Pe³ny ekran::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	cout << "Podaj nazwe pliku bazy danych, albo nazwe pliku ktory utworzyles wczesniej: ";
	string nazwaPliku;
	cin >> nazwaPliku;
	while (!czyPoprawnaNazwa(nazwaPliku))
	{
		cout << endl << "Podaj nazwe pliku bazy danych: ";
		cin >> nazwaPliku;
	}
	MenedzerPlikow menedzerPlikow(nazwaPliku);
	BazaPracownikow bazaDanych;
	int dodatkoweOpcje = 0;
	bool czyDzialamy = true;
	//flaga uzyta do zapobiegniecia niepotrzebnego resetowania tekstu w konsoli i nadmiarowego powielaniu sie wyswietlania menu
	bool failed = false;
	cout << "Witaj w programie Baza Pracownikow Firmy X" << endl;
	PetlaGlownaProgramou(wybor, dodatkoweOpcje, bazaDanych, menedzerPlikow);
	CloseHandle(h);
	system("pause");
}

void PetlaGlownaProgramou(int &wybor, int &dodatkoweOpcje, BazaPracownikow &bazaDanych, MenedzerPlikow& menedzer)
{
	while (true)
	{
		if (pierwszeUruchomienie)
		{
			menedzer.wczytajDanezPliku(bazaDanych, czySukces);
			if (bazaDanych.liczbaPracownikowGet() == 0)
				powiadomienie("Wczytany plik jest pusty, nie zawiera rekordow z pracownikami!");
		}


		menu();
		pierwszeUruchomienie = false;

		sprawdzanieWyboruUzytkownika(wybor, czySukces, 12);
		switch (wybor)
		{


			case 1:
			{
				czyKomunikaty = true;
				std::string imie, nazwisko, zarobki;
				cout << "[1]Dodaj Dyrektora\n[2]Dodaj Pracownika Fizycznego" << endl;
				sprawdzanieWyboruUzytkownika(dodatkoweOpcje, czySukces, 3);
				switch (dodatkoweOpcje)
				{
					case 1:
					{
						if (!bazaDanych.czyJestDyrektor())
						{
							wprowadzDane(imie, nazwisko, zarobki);
							Dyrektor dyrektor(imie, nazwisko, stoi(zarobki), bazaDanych.nadajID());
							bazaDanych.dodajPracownikaTablica(dyrektor, czySukces);
							cout << endl << "Podaj haslo do dostepu dla panelu dyrektora: ";
							string haslo;
							cin >> haslo;
							czySukces = hasloPanelDyrektora(haslo, 'z');
						}
						else
						{
							powiadomienie("Mamy juz dyrektora!");
							czySukces = false;
						}
						
						break;
					}
					case 2:
					{
						wprowadzDane(imie, nazwisko, zarobki);
						Fizyczny pracownikFizyczny(imie, nazwisko, stoi(zarobki), bazaDanych.nadajID());
						bazaDanych.dodajPracownikaTablica(pracownikFizyczny, czySukces);
						break;
					}
				}
				break;
			}
			case 2:
			{
					czyKomunikaty = true;
					cout << endl << "Oto lista pracownikow: " << endl;
					bazaDanych.wyswietlPracownikowTablica();
				    cout << "\nPodaj ID pracownika: ";
					
					string id;
					cin >> id;
					while (!walidatorStringNaInt(id))
					{
						powiadomienie("Widocznie wprowadziles niepoprawny znak / zle ID\nPodaj ID pracownika : ");
						cin >> id;
						
					}
					
					if (bazaDanych[stoi(id)] == PUSTYSTRING)
					{
						czySukces = false;
						powiadomienie("Nie ma pracownika o takim id!!");
						break;
					}
					else
					{

						cout << "\nCzy na pewno chcesz nadpisac dane: ";
						cout << bazaDanych.szukajPoId(wybor)->pobierzImie() + " " + bazaDanych.szukajPoId(wybor)->pobierzNazwisko() << endl << "[1]TAK\n[2]NIE" << endl;
						int idPracownikaEdytowanego = wybor;
						sprawdzanieWyboruUzytkownika(wybor, czySukces, 2);


						if (wybor == 1)
						{
							bazaDanych.usunPracownika(idPracownikaEdytowanego);
							string imie, nazwisko, zarobki, pozycja;
							cout << endl << "Wprowadz nowe dane dla tego pracownika:";
							wprowadzDane(imie, nazwisko, zarobki);
							Pracownik zedytowany(imie, nazwisko, stoi(zarobki), bazaDanych.nadajID());
							bazaDanych.dodajPracownikaTablica(zedytowany, czySukces);
						}
						else if (wybor == 2)
						{
							break;
						}


						


						break;
					}

			}
			case 3:
			{
				czyKomunikaty = true;
				if (bazaDanych.liczbaPracownikowGet() == 0)
				{
					cout << endl << "Baza pracownikow jest pusta!" << endl;
					czySukces = false;
				}
				cout << endl << "Podaj ID pracownika ktorego chcesz usunac: ";
				string id;
				cin >> id;
				while (!walidatorStringNaInt(id))
				{
					powiadomienie("Widocznie wprowadziles niepoprawny znak/zle ID\nPodaj ID pracownika ktorego chcesz usunac: ");
					cin >> id;
				}

				if (bazaDanych[stoi(id)] == PUSTYSTRING)
				{
					czySukces = false;
					powiadomienie("Nie ma pracownika o takim id!!");
					break;
				}
				else
				{
					cout << endl << "Czy na pewno chcesz usunac: " + bazaDanych.szukajPoId(stoi(id))->pobierzImie() + " "+ bazaDanych.szukajPoId(stoi(id))->pobierzNazwisko() + " ?" << std::endl;
					cout << "\n[1]TAK\n[2]NIE\n";
					sprawdzanieWyboruUzytkownika(wybor, czySukces, 2);
					if (wybor == 1)
					{
						bazaDanych.usunPracownika(stoi(id));
					}
					else
					{
						break;
					}
					
					break;
				}
			}
			case 4:
			{
				cout << "\n[1]Wyszukiwanie za pomoca ID\n[2]Wyszukiwanie za pomoca nazwiska\n";
				sprawdzanieWyboruUzytkownika(wybor, czySukces, 2);
				int id = 0;
				string nazwisko = "";
				string wynik = "";
				if (wybor == 1)
				{
					cout << "\nPodaj ID Pracownika: ";
					sprawdzanieWyboruUzytkownika(id, czySukces, bazaDanych.aktualneID());
					wynik = bazaDanych[id];
					if (wynik == "") {
						powiadomienie("\nNie ma w bazie uzytkownika o takim ID!\n");
						czySukces = false;
					}
					else
					{
						czySukces = true;
						powiadomienie((bazaDanych.szukajPoId(id)->pobierzImie() + " " + bazaDanych.szukajPoId(id)->pobierzNazwisko() + " zarabia: " + to_string(bazaDanych.szukajPoId(id)->pobierzZarobki())).c_str());
					}
				}
				else if (wybor == 2)
				{
					cout << "\nPodaj nazwisko pracownika: ";
					cin >> nazwisko;
					

					while (!walidatorStringow(nazwisko))
					{
						powiadomienie("Wprowadzono niepoprawne znaki!\n");
						cout << "\nPodaj nazwisko pracownika: ";
						cin >> nazwisko;
					}

					wynik = bazaDanych[nazwisko];
					if (wynik == "") {
						powiadomienie("\nNie ma w bazie uzytkownika o takim nazwisku!\n");
						czySukces = false;
					}
					else
					{
						cout << wynik << endl;
						czySukces = true;
						cout << endl << wynik << endl;
					}

				}
				czyKomunikaty = true;
				break;

			}
			case 5:
			{
				system("cls");
				czyKomunikaty = false;
				break;
			}
			case 6:
			{
				bazaDanych.wyswietlPracownikowTablica();
				czyKomunikaty = false;
				break;
			}
			case 7:
			{
				if (bazaDanych.liczbaPracownikowGet() == 0)
				{
					powiadomienie("\nNie ma zadnych pracownikow w bazie!");
				}
				int laczneZarobki = bazaDanych.sumaZarobkowPracownikow();
				cout << "\nLaczne zarobki pracownikow:" << laczneZarobki << "PLN" <<endl;
				czyKomunikaty = false;

				break;
			}
			case 8:
			{
				menedzer.zapiszDoPliku(czySukces, bazaDanych);
				czyKomunikaty = true;
				break;
			}
			case 9:
			{
				menedzer.wczytajDanezPliku(bazaDanych, czySukces);
				czyKomunikaty = false;
				break;
			}
			case 10:
			{
				string nazwaPliku;
				menedzer.wczytajWybranyPlikBazdyDanych(nazwaPliku, bazaDanych, czySukces);
				czyKomunikaty = false;
				break;
			}
			case 11:
			{
				czyKomunikaty = true;
				if (!bazaDanych.czyJestDyrektor())
				{
					powiadomienie("W bazie nie ma zadnego dyrektora! Aby dostac sie do panelu dyrektora musisz najpierw dodac dyrektora do bazy!");
					czySukces = false;
					break;
				}
			
				
				string haslo;
				powiadomienie("Aby dostac sie do panelu dyrektora musisz podac haslo.");
				cout <<endl<< "Wpisz haslo: ";
				cin >> haslo;
				bool wynik = hasloPanelDyrektora(haslo, 'o');
				if (wynik)
				{
					
					cout << endl << "[1]Wyswietl liste podleglych pracownikow\n[2]Zwolnij pracownika\n[3]Dodaj podleglego pracownika"<<endl;
					int wybor;
					cin >> wybor;
					if (wybor == 1)
					{
						bazaDanych.pobierzDyrektora().wyswietlPodleglychPracownikow();
					}
					else if (wybor == 2)
					{
						cout << endl << "Podaj id pracownika ktorego chcesz zwolnic :";
						string id;
						cin >> id;
						while (!walidatorStringNaInt(id))
						{
							powiadomienie("Widocznie wprowadziles niepoprawny znak / zle ID\nPodaj id pracownika ktorego chcesz zwolnic :");
							cin >> id;
						}

						if (bazaDanych.szukajPoId(stoi(id)) == nullptr)
						{
							powiadomienie("Nie ma pracownika o podanym id!");
							czySukces = false;
						}
						else
						{
							if (bazaDanych.szukajPoId(stoi(id))->pobierzPozycje() == "Dyrektor")
							{
								powiadomienie("Dyrektor nie moze usunac samego siebie :)");
								czySukces = false;
								break;
							}
							bazaDanych.usunPracownika(stoi(id));
							bazaDanych.pobierzDyrektora().usunPodleglegoPracownika(stoi(id));
							czySukces = true;
						}

					}
					else if (wybor == 3)
					{
						cout << endl << "Podaj ID pracownika ktorego chcesz byc przelozonym: ";
						string id;
						cin >> id;
						while (!walidatorStringNaInt(id))
						{
							powiadomienie("Widocznie wprowadziles niepoprawny znak / zle ID\nPodaj ID pracownika ktorego chcesz byc przelozonym: ");
							cin >> id;
						}
						const Pracownik* poddany = bazaDanych.szukajPoId(stoi(id));
						if (poddany == nullptr)
						{
							powiadomienie("Nie ma pracownika o podanym id!");
							czySukces = false;
						}
						else
						{
							bazaDanych.pobierzDyrektora().dodajPodleglegoPracownika(*poddany);
							czySukces = true;
						}

					}
				}
				else
				{
					powiadomienie("Wprowadzone haslo jest nieprawidlowe!");
					czySukces = false;
				}
				break;
			}
			case 12:
			{
				czyKomunikaty = false;
				cout << endl << "Czy przed opuszczeniem programu chcesz zapisac dokonane zmiany?\n[1]TAK\n[2]NIE\n";
				int wybor;

				cin >> wybor;
				if (wybor == 1)
				{
					menedzer.zapiszDoPliku(czySukces, bazaDanych);
				}

				if (bazaDanych.pobierzPracownikow() != nullptr)
				{
					bazaDanych.~BazaPracownikow();
				}
				exit(0);

				break;
			}

			}

			if (czySukces && czyKomunikaty)
			{
				sukces();
			}
			else if (!czySukces && czyKomunikaty)
			{
				porazka();
			}
		}

	
}

void menu()
{

	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << endl << "Menu programu wyglada nastepujaco: " << endl;
	cout << "[1]Dodaj Pracownika do bazy\n"
		"[2]Edytuj dane pracownika\n"
		"[3]Usun pracownika\n"
		"[4]Wyszukaj pracownika\n"
		"[5]Czysc ekran\n"
		"[6]Wyswietl wszystkich pracownikow\n"
		"[7]Ile oni zarabiaja\n"
		"[8]Zapisz Pracownikow do pliku\n"
		"[9]Wczytaj dane z pliku\n"
		"[10]Wczytaj wybrany plik bazy danych\n"
		"[11]Panel Dyrektora\n"
		"[12]Zakoncz Program\n";
}
bool hasloPanelDyrektora(string& haslo, char tryb)
{
	if (tryb == 'z')
	{
		ofstream plik("panelDyrektora.txt");
		if (!plik)
		{
			cout << endl << "Problem przy tworzeniu pliku Panelu Dyrektora" << endl;
			return false;
		}
		else
		{
			plik << haslo;
			cout << endl << "Plik dla Panelu Dyrektora zostal utworzony poprawnie" << endl;
			plik.close();
			return true;
		}
	}
	else if (tryb == 'o')
	{
		ifstream plik("panelDyrektora.txt");
		string hasloPlik;
		getline(plik, hasloPlik);
		if (haslo == hasloPlik)
			return true;
		else
			return false;
	}
	else
	{
		cout << endl << "Nie ma takiej opcji w tej funkcji!" << endl;
	}
	return false;
}
void wprowadzDane(string& imie, string& nazwisko, string& zarobki)
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
void sprawdzanieWyboruUzytkownika(int& integer, bool& czySukces, int zakres)
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
	catch (const out_of_range&)
	{
		czySukces = false;
		std::cout << endl << "Nie ma takiej opcji menu!" << endl << "Dostepne sa: 1-" << to_string(zakres) << endl;
		sprawdzanieWyboruUzytkownika(integer, czySukces, zakres);
	}
	catch (const exception&)
	{
		czySukces = false;
		std::cout << endl << "Wprowadzono niepoprawny znak!" << endl;
		std::cout << "Wprowadz 1- " << to_string(zakres) << endl;
		sprawdzanieWyboruUzytkownika(integer, czySukces, zakres);

	}


}
bool walidatorStringNaInt(string& zarobki)
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
	catch (const out_of_range&)
	{
		cout << endl << "Wprowadzona liczba jest za duza na ten program!";
		return false;
	}
	catch (const invalid_argument&)
	{
		cout << endl << "Wprowadzono niepoprawny znak!";
		return false;
	}
	return true;
}
bool czyPoprawnaNazwa(string & nazwa)
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
bool walidatorStringow(string& s)
{
	for (size_t i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]) || (!isalpha(s[i])))
			return false;
	}
	return true;
}
void sukces()
{
	SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	cout << "POPRZEDNIA OPERACJA ZAKONCZYLA SIE SUKCESEM!" << endl;
	cout << "  |    |    |    |    |    |    |" << endl;
	cout << "  |    |    |    |    |    |    |" << endl;
	cout << "  |    |    |    |    |    |    |" << endl;
}

void porazka()
{
	SetConsoleTextAttribute(h, FOREGROUND_RED);
	cout << "UWAGA: POPRZEDNIA OPERACJA ZAKONCZYLA SIE PORAZKA!!!" << endl;
	cout << "  |    |    |    |    |    |    |" << endl;
	cout << "  |    |    |    |    |    |    |" << endl;
	cout << "  |    |    |    |    |    |    |" << endl;

}

void powiadomienie(const char* pow)
{
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << endl << pow << endl;
}



