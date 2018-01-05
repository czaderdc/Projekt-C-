#pragma once
#include<string>
#include<iostream>
class KlasaPomocnicza
{
private:
	KlasaPomocnicza();
	KlasaPomocnicza(const KlasaPomocnicza&);
	KlasaPomocnicza& operator=(KlasaPomocnicza&);
public:
	static void wprowadzDane(std::string& imie, std::string& nazwisko, std::string& zarobki);
	static bool walidatorStringow(string& s);
	static void sprawdzanieWyboruUzytkownika(int& integer, bool& czySukces, int zakres);
	static bool walidatorStringNaInt(string& zarobki);
	static bool czyPoprawnaNazwa(string& nazwa);
	~KlasaPomocnicza();
};

