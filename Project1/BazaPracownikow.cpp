
#include "BazaPracownikow.h"
#include <iomanip>
#include <exception>
#include <sstream>
#define PUSTYSTRING ""
bool wczytane = false;
bool dodano = false;
void BazaPracownikow::resetujTablicePracownikow()
{
	liczbaPracownikow = 0;
	idPracownika = 0;
	delete[] Pracownicy;
	Pracownicy = nullptr;
}
const Pracownik& BazaPracownikow::szukajPoId(int Id) const
{

	for (size_t i = 0; i < liczbaPracownikowGet(); i++)
	{
		if (Pracownicy[i].pobierzID() == Id)
			return Pracownicy[i];
	}
}
bool BazaPracownikow::czyJestDyrektor()
{
	for (size_t i = 0; i < liczbaPracownikowGet(); i++)
	{
		if (Pracownicy[i].pobierzPozycje() == "Dyrektor")
			return true;
	}

	return false;
}
void BazaPracownikow::dodajDyrektora(const Dyrektor & dyrektor)
{
	dyrektor_ = dyrektor;

}
BazaPracownikow::BazaPracownikow()
{
	liczbaPracownikow = 0;
}

# pragma region Realokacja
void BazaPracownikow::realokujTabliceUsuwam(Pracownik& p)
{
	--idPracownika;
	//bo jednego "usuwam" z tablicy dlatego n-1 ze stanem wejsciowym
	size_t iluSkopiowac = liczbaPracownikowGet() - 1;
	if (iluSkopiowac == 0)
	{
		delete[] Pracownicy;
		--liczbaPracownikow;
		Pracownicy = nullptr;
	}
	else
	{
		Pracownik *temp = new Pracownik[iluSkopiowac];


		//zmienna pomocnicza j, bo continue "gubi" jedna wartosc po pominieciu danego pracownika
		for (size_t i = 0, j = 0; i <= iluSkopiowac; i++)
		{
			if (Pracownicy[i] == p)
			{
				//w sumie to niepotrzebne zastapic zmienna iluSkopiowac
				--liczbaPracownikow;
				continue;
			}
			temp[j++] = Pracownicy[i];
		}
		////resetuje wskaznik jesli wczesniej nie byl pusty i zwalnia pamiec aby moc zaoolokowac wieksza tablice
		if (Pracownicy != nullptr)
		{
			delete[]Pracownicy;
			Pracownicy = nullptr;
		}
		Pracownicy = new Pracownik[liczbaPracownikowGet()];
		for (size_t i = 0; i <liczbaPracownikowGet(); i++)
		{
			Pracownicy[i] = temp[i];
		}
		//-1 bo indeksowane w tablicy elementy sa od zera
		delete[]temp;
		//niby dobry zwyczaj programistyczny
		temp = nullptr;
	}
	//i na koniec popraw dane w pliku
	//czyli po prostu zapisz/edyt



}
void BazaPracownikow::realokujTablice(Pracownik& p, bool& failed)
{
	try
	{
		if (liczbaPracownikowGet() > 1)
		{
			////do tymczasowej tablicy kopiuje n-1 pracownikow(nie biore pod uwage nowo dodanego bo jego dodam do nowej tablicy
			Pracownik *temp = new Pracownik[liczbaPracownikowGet() - 1];



			for (size_t i = 0; i < liczbaPracownikowGet() - 1; i++)
			{
				temp[i] = Pracownicy[i];
			}
			////resetuje wskaznik jesli wczesniej nie byl pusty i zwalnia pamiec aby moc zaoolokowac wieksza tablice
			if (Pracownicy != nullptr)
			{
				delete[]Pracownicy;
				Pracownicy = nullptr;
			}
			////alokuje pamiec dla starych + dla nowego
			Pracownicy = new Pracownik[liczbaPracownikowGet()];
			//przypisujemy stare elementy do <n-1, bo n-1 element jest zarezerwowany dla nowego
			for (size_t i = 0; i < liczbaPracownikowGet() - 1; i++)
			{
				Pracownicy[i] = temp[i];
			}
			//-1 bo indeksowane w tablicy elementy sa od zera
			Pracownicy[liczbaPracownikowGet() - 1] = p;
			delete[]temp;
			//niby dobry zwyczaj programistyczny
			temp = nullptr;
		}
		//jest pierwszym pracownikiem
		else
		{
			Pracownicy = new Pracownik[1];
			Pracownicy[0] = p;
		}
	}
	catch (std::bad_alloc&e)
	{
		std::cerr << std::endl << "Blad z alokacja pamieci!";
		failed = true;
	}
	catch (std::exception& e)
	{
		failed = true;
	}


}
#pragma endregion Realokacja 

void BazaPracownikow::dodajPracownikaTablica(Pracownik & p, bool& failed)
{

	//jesli wczytujemy z pliku przy uruchamianiu programu to pomin sprawdzanie, bo wywali blad ze po prawej stronie stoi nullptr
	if (wczytane)
	{
		for (size_t i = 0; i < liczbaPracownikowGet(); i++)
		{
			if (p == Pracownicy[i])
			{
				std::cout << "\nPracownik o podanych danych juz istnieje. Moze chcesz uaktualnic jego dane?\n";
				std::string wybor = "";
				std::cin >> wybor;
				return;
			}
		}
	}
	++liczbaPracownikow;
	dodano = true;
	realokujTablice(p, failed);
}






int BazaPracownikow::sumaZarobkowPracownikow()
{
	int wynik = 0;
	for (size_t i = 0; i < liczbaPracownikowGet(); i++)
	{
		wynik += Pracownicy[i].pobierzZarobki();
	}

	return wynik;
}
//jak dodam nowych pracownikow i zapisze to pasuje skopiowac do nowego pliku i skasowac zeby nie tworzyly sie kopie


std::string BazaPracownikow::przytnijOpis(std::string opis, std::string liniaTekstu, size_t& pozycja)
{
	pozycja = 0;
	std::string wynik = "";
	if (liniaTekstu == "" || opis[1] != liniaTekstu[1])
		return "";
	pozycja = liniaTekstu.find(opis);
	if (pozycja != std::string::npos)
	{
		liniaTekstu = liniaTekstu.substr(pozycja = pozycja + opis.length());
		wynik = liniaTekstu;
	}
	return wynik;
}



void BazaPracownikow::usunPracownika(int IDpracownika)
{
	for (size_t i = 0; i < liczbaPracownikowGet(); i++)
	{
		if (Pracownicy[i].pobierzID() == IDpracownika)
		{
			realokujTabliceUsuwam(Pracownicy[i]);
		}
	}
}
int BazaPracownikow::sumaZarobkowPracownikow() const
{
	int sumaZarobkow = 0;
	for (size_t i = 0; i < liczbaPracownikowGet(); i++)
	{
		sumaZarobkow += Pracownicy[i].pobierzZarobki();
	}
	return sumaZarobkow;
}
//moze przeciazyc dla samego nazwiska?
std::string BazaPracownikow::operator[](int id)
{

	if (liczbaPracownikowGet() == 0)
		return PUSTYSTRING;
	for (size_t i = 0; i < liczbaPracownikowGet(); i++)
	{
		if (Pracownicy[i].pobierzID() == id)
		{
			return Pracownicy[i].pobierzNazwisko();
		}
	}
	return PUSTYSTRING;


}


std::string BazaPracownikow::operator[](std::string nazwisko)
{
	if (liczbaPracownikowGet() == 0)
		return PUSTYSTRING;
	else
	{
		for (size_t i = 0; i < liczbaPracownikowGet(); i++)
		{
			if (Pracownicy[i].pobierzNazwisko() == nazwisko)
			{
				return nazwisko;
			}
		}

		return PUSTYSTRING;
	}
}


//trzeba pozmieniac spora czesc programu, zeby osobno licznik na temat ilosci posiadanych pracownikow posiadal kontener vector a osobno tablica
//podczas dodawania pracownika
void BazaPracownikow::wyswietlPracownikowTablica()
{
	if (liczbaPracownikowGet() == 0 || Pracownicy == nullptr)
	{
		std::cout << "\nW tablicy nie ma zapisanych zadnych pracownikow!\n";
	}
	else
	{
		size_t kolumnaImie = 20;
		size_t kolumnaNazwisko = 20;
		size_t kolumnaZarobki = 20;
		size_t kolumnaPozycja = 20;
		for (size_t i = 0; i < liczbaPracownikowGet(); i++)
		{
			if (Pracownicy[i].imieLength() > kolumnaImie)
			{
				kolumnaImie = Pracownicy[i].imieLength();
			}
			if (Pracownicy[i].nazwiskoLength() > kolumnaNazwisko)
			{
				kolumnaNazwisko = Pracownicy[i].nazwiskoLength();
			}
			if (Pracownicy[i].pobierzPozycje().length() > kolumnaZarobki)
			{
				kolumnaZarobki = Pracownicy[i].pobierzPozycje().length();
			}
		}

		for (size_t i = 0; i < liczbaPracownikowGet(); i++)
		{
			if (std::to_string(Pracownicy[i].pobierzZarobki()).length() + 4 > kolumnaZarobki)
				kolumnaZarobki = std::to_string((Pracownicy[i].pobierzZarobki())).length() + 4; //+4 dla napisu PLN
		}

		std::string linia = "";
		//zastosowa stream format w celu wyrownania linii tekstu
		for (size_t i = 0; i < (kolumnaImie + kolumnaNazwisko + kolumnaZarobki + (std::string("Imie")).length() + (std::string("Nazwisko")).length() + (std::string("Zarobki")).length()) + (std::string("Pozycja")).length(); i++)
		{
			linia += "-";
		}
		std::cout << "Dane pracownikow: " << std::endl;
		std::cout << linia << std::endl;
		std::cout << " |";
		std::cout.width(kolumnaImie);
		std::cout << std::left << "Imie";
		std::cout << " |";
		std::cout.width(kolumnaNazwisko);
		std::cout << " Nazwisko";
		std::cout << " |";
		std::cout.width(kolumnaPozycja);
		std::cout << std::left << " Pozycja" << " |";
		std::cout.width(kolumnaZarobki);
		std::cout << std::left << " Zarobki" << " |" << std::endl;
		std::cout << linia << std::endl;


		/*if (kolumnaNazwisko < (((std::string)"Nazwisko").length() + 1))
		{
		kolumnaNazwisko = ((std::string)"Nazwisko").length() + 1;
		}*/
		for (size_t i = 0; i < liczbaPracownikowGet(); i++)
		{
			std::cout << " |";
			std::cout.width(kolumnaImie);
			std::cout << std::left << Pracownicy[i].pobierzImie();
			std::cout << " |";
			std::cout.width(kolumnaNazwisko);
			std::cout << std::left << Pracownicy[i].pobierzNazwisko();
			std::cout << " |";
			std::cout.width(kolumnaPozycja);
			std::cout << std::left << Pracownicy[i].pobierzPozycje();
			std::cout << " |";
			std::cout.width(kolumnaZarobki);
			std::cout << std::to_string(Pracownicy[i].pobierzZarobki()) + " PLN";
			std::cout << " |" << std::endl;
			std::cout << linia << std::endl;

		}
	}
}


BazaPracownikow::~BazaPracownikow()
{
	delete[] Pracownicy;
	Pracownicy = nullptr;
}
