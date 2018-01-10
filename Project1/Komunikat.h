#pragma once
#include <Windows.h>
class Komunikat
{
private:
	static HANDLE ekranHandle;
	Komunikat(const Komunikat&);
	Komunikat();
public:
	static void powiadomUzytkownika(const char* wiadomosc);

	~Komunikat();
};

