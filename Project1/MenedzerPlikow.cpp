#include <iostream>
#include <experimental/filesystem>
#include <Windows.h>
#include <sys/stat.h>
#include <string.h>
#include "MenedzerPlikow.h"
#include "Komunikat.h"

MenedzerPlikow::MenedzerPlikow(std::string nazwaPliku, bool czyDodano, bool czyUsunieto) : dodanoPracownika(czyDodano), usunietoPracownika(czyUsunieto), nazwaPliku(nazwaPliku + ".txt")
{
	liczbaPlikow = 0;

	sciezka = std::experimental::filesystem::current_path().string();
	size_t dlugoscSciezki = sciezka.length();
	//std::wstring pelnaSciezkawString(sciezka.begin(), sciezka.end());
	if (czySciezkaIstnieje(sciezka, nazwaPliku + ".txt"))
	{
		Komunikat::powiadomUzytkownika("Plik o podanej nazwie juz istnieje! Wczytuje zatem ten plik");
	}
	else
	{
		std::ofstream plik(nazwaPliku + ".txt");
		if (!plik)
		{
			Komunikat::powiadomUzytkownika("Problem przy tworzeniu pliku!");
		}
		else
		{
			Komunikat::powiadomUzytkownika("Plik utworzono poprawnie!");
			Komunikat::powiadomUzytkownika("Twoj plik z baza pracownikow znajdziesz pod sciezka: ");
		    Komunikat::powiadomUzytkownika(std::string(sciezka + "\\" + nazwaPliku + ".txt").c_str());
			plik.close();
		}
	}



}

void MenedzerPlikow::zapiszNazwePlikuDoTablicy(std::string & nazwaPliku2)
{
	//wlasne alokatory
	//try
	//{
	//	//jesli w tablicy juz cos bylo
	//	if (liczbaPlikow > 1)
	//	{
	//		std::string* tablicaTemp = new std::string[liczbaPlikow - 1];
	//		for (size_t i = 0; i < liczbaPlikow - 1; i++)
	//		{
	//			tablicaTemp[i] = tablicaPlikow[i];
	//		}
	//		if (tablicaPlikow != nullptr)
	//		{
	//			delete[] tablicaPlikow;
	//			tablicaPlikow = nullptr;
	//		}
	//		tablicaPlikow = new std::string[liczbaPlikow];
	//		for (size_t i = 0; i < liczbaPlikow - 1; i++)
	//		{
	//			tablicaPlikow[i] = tablicaTemp[i];
	//		}
	//		tablicaPlikow[liczbaPlikow - 1] = nazwaPliku2;
	//		delete[] tablicaTemp;
	//		tablicaTemp = nullptr;

	//	}
	//	//jesli nic w niej nie bylo
	//	else
	//	{
	//		tablicaPlikow = new std::string[1];
	//		tablicaPlikow[0] = nazwaPliku2;
	//	}
	//}
	//catch (std::bad_alloc&)
	//{
	//	Komunikat::powiadomUzytkownika("Blad przy alokacji pamieci dla tablicy plikow!\n");
	//}
	//catch (std::exception& ex)
	//{
	//	Komunikat::powiadomUzytkownika("Wystapil inny blad: \n");
	//	Komunikat::powiadomUzytkownika(ex.what());
	//}

	pliki.push_back(nazwaPliku2);

}
//przycina sciezke do pliku do nazwy samego pliku

void MenedzerPlikow::przytnijSciezke(std::string& sciezka, size_t dlugoscSciezki)
{
	std::string nazwaPliku = sciezka.substr(dlugoscSciezki + 1);
	size_t dlugoscNazwyPliku = nazwaPliku.length();
	//szukam tylko plikow txt
	if (nazwaPliku[dlugoscNazwyPliku - 1] == 't' && nazwaPliku[dlugoscNazwyPliku - 2] == 'x' &&  nazwaPliku[dlugoscNazwyPliku - 3] == 't')
	{
		++liczbaPlikow;
		std::cout << std::endl << nazwaPliku;
		zapiszNazwePlikuDoTablicy(nazwaPliku);
	}
}

void MenedzerPlikow::wyswietlPlikiBazDanych()
{
	for (auto& s : std::experimental::filesystem::directory_iterator(sciezka))
	{
		std::string n = s.path().string();
		przytnijSciezke(n, sciezka.length());
	}
}

void MenedzerPlikow::wczytajWybranyPlikBazdyDanych(std::string& plik, BazaPracownikow& baza, bool& czySukces)
{
	Komunikat::powiadomUzytkownika("Oto lista dostepnych plikow z baza danych: ");
	wyswietlPlikiBazDanych();
	std::cout << std::endl << std::endl;
	Komunikat::powiadomUzytkownika("Ktory plik chcesz wczytac? Podaj nazwe bez \".txt: ");
	std::cin >> plik;

	for (auto i = pliki.begin(); i != pliki.end(); i++)
	{
		if (*i == plik + ".txt")
		{
			Komunikat::powiadomUzytkownika("Znalazlem ten plik: ");
			Komunikat::powiadomUzytkownika("Wczytuje....");
			zmienPlik(*i);
			wczytajDanezPliku(baza, czySukces);
			return;
			
		}
		czySukces = false;
	}
	//resetujTablicePlikow();
	Komunikat::powiadomUzytkownika("Plik o podanej nazwie nie istnieje! ");
	wczytajWybranyPlikBazdyDanych(nazwaPliku, baza, czySukces);
}

bool MenedzerPlikow::czyPlikIstnieje(const std::string& file) {
	struct stat buf;
	return (stat(file.c_str(), &buf) == 0);
}
void MenedzerPlikow::resetujTablicePlikow()
{
	liczbaPlikow = 0;
	delete[] tablicaPlikow;
	tablicaPlikow = nullptr;
}
void MenedzerPlikow::zmienPlik(std::string nowy)
{
	nazwaPliku = nowy;
}
//winapi C sprawdza czy pod obecna sciezka istnieje plik o podanej nazwie w celu zapobiegania nadawania takiej samej nazwy
//kolejnemu plikowi bazy danych po ponownym uruchomieniu programu
bool MenedzerPlikow::czySciezkaIstnieje(const std::string& sciezka, const std::string& nazwaPliku)
{
	
	DWORD check = GetFileAttributes(sciezka.c_str());
	if (check == INVALID_FILE_ATTRIBUTES)
		return false;
	if ((check & FILE_ATTRIBUTE_DIRECTORY) && czyPlikIstnieje(nazwaPliku))
		return true;
	else
		return false;

}

void MenedzerPlikow::zapiszDoPliku(bool & czySukces, BazaPracownikow& baza)
{
	std::ofstream plikZapis(nazwaPliku, std::ios::in | std::ios::app);
	//moze dodac warunek aby niepotrzebnie nie usuwac jak plik byl pusty

	if (!plikZapis)
	{
		Komunikat::powiadomUzytkownika("Nie odnaleziono pliku!");
		czySukces = false;
		return;

	}
	if (baza.liczbaPracownikowGet() == 0 || baza.pobierzPracownikow() == nullptr)
	{
		Komunikat::powiadomUzytkownika("\nNie ma czego zapisac do pliku!\n");
		czySukces = false;
		//usun ostatnia zawartosc pliku jesli z pamieci usunalem wszystkich pracownikow, bo inaczej ciagle bedzie jeden rekord w pliku
		//mimo usuniecia wsyztskich z pamieci bo pomijam zapisywanie pliku w przypadku gdy tablica pracownicy == nullptr
		plikZapis.close();
		remove(nazwaPliku.c_str());
		plikZapis.open(nazwaPliku);
		plikZapis.close();
		return;
	}
	//do 



	//zapisywanie

	for (size_t i = 0; i < baza.liczbaPracownikowGet(); i++)
	{
		plikZapis << baza.pobierzPracownikow()[i];
	}
	plikZapis.close();
	czySukces = true;
	//jesli dodano lub usunieto pracownika trzeba caly plik utworzyc na nowo, w sumie najprostszy sposob

	//zamknij przed usunieciem
	plikZapis.close();
	remove((nazwaPliku).c_str());
	std::ofstream plikTemp("bazaPracownikowtemp.txt", std::ios::in | std::ios::app);
	for (size_t i = 0; i < baza.liczbaPracownikowGet(); i++)
	{
		plikTemp << baza.pobierzPracownikow()[i];
	}
	plikTemp.close();
	rename("bazaPracownikowtemp.txt", (nazwaPliku).c_str());
	czySukces = true;



}

void MenedzerPlikow::wczytajDanezPliku(BazaPracownikow& baza, bool& failed)
{
	baza.resetujTablicePracownikow();
	std::ifstream plikOdczyt(nazwaPliku, std::ios::out);
	if (!plikOdczyt)
	{
		Komunikat::powiadomUzytkownika("Problem z odczytem pliku!");
	}
	if (plikOdczyt.peek() == std::ifstream::traits_type::eof())
	{
		Komunikat::powiadomUzytkownika("Plik z baza danych jest pusty!");
	}
	//czytanie jesli plik wczesniej zawieral Pracownikow
	std::string liniaTekstu = "";
	std::size_t pozycja;
	bool czyID = false, czyImie = false, czyNazwisko = false, czyZarobki = false, czyPozycja = false, czyDyrektor = false;
	std::string imie, nazwisko, pozycjaPracownika;
	int zarobki, id;
	int licznik = 0;
	while (getline(plikOdczyt, liniaTekstu))
	{
		//dane zajmuja 4 linjki, jak czytanie minie 4 linijki, to resetuj flagi, zeby nie zapisywac tego samego pracownika kilka razy
		if (licznik % 5 == 0)
		{
			czyID = false, czyImie = false, czyNazwisko = false, czyZarobki = false, czyPozycja = false;
		}
		pozycja = liniaTekstu.find("ID: ");
		if (pozycja != std::string::npos)
		{
			liniaTekstu = liniaTekstu.substr(pozycja + ((std::string("ID: ").length())), 1);
			id = std::stoi(liniaTekstu);
			czyID = true;
		}
		pozycja = liniaTekstu.find("Imie pracownika: ");
		if (pozycja != std::string::npos)
		{
			liniaTekstu = liniaTekstu.substr(pozycja + ((std::string("Imie pracownika: ").length())));
			imie = liniaTekstu;
			czyImie = true;
		}
		pozycja = liniaTekstu.find("Nazwisko pracownika: ");
		if (pozycja != std::string::npos)
		{
			liniaTekstu = liniaTekstu.substr(pozycja + ((std::string("Nazwisko pracownika: ").length())));
			nazwisko = liniaTekstu;
			czyNazwisko = true;
		}
		pozycja = liniaTekstu.find("Zarobki pracownika: ");
		if (pozycja != std::string::npos)
		{
			liniaTekstu = liniaTekstu.substr(pozycja + ((std::string("Zarobki pracownika: ").length())));
			zarobki = std::stoi(liniaTekstu);
			czyZarobki = true;
		}
		pozycja = liniaTekstu.find("Pozycja pracownika: ");
		if (pozycja != std::string::npos)
		{
			liniaTekstu = liniaTekstu.substr(pozycja + ((std::string("Pozycja pracownika: ").length())));
			pozycjaPracownika = liniaTekstu;
			if (pozycjaPracownika == "Dyrektor")
			{
				czyDyrektor = true;
			}
			czyPozycja = true;
		}

		if (czyID && czyImie && czyNazwisko && czyZarobki && czyPozycja)
		{
			if (czyDyrektor)
			{
				Dyrektor odczyt(imie, nazwisko, zarobki, id, pozycjaPracownika);
				baza.dodajPracownikaTablica(odczyt, failed);
				baza.dodajDyrektora(odczyt);
				baza.aktualizujId(id);
			}
			else
			{
				Pracownik odczyt(imie, nazwisko, zarobki, id, pozycjaPracownika);
				baza.dodajPracownikaTablica(odczyt, failed);
				baza.aktualizujId(id);
			}
			
		}
		++licznik;
	}
	plikOdczyt.close();
}

MenedzerPlikow::~MenedzerPlikow()
{
	delete[] tablicaPlikow;
}
