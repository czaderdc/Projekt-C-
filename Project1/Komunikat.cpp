#include "Komunikat.h"
#include <iostream>

HANDLE Komunikat::ekranHandle = GetStdHandle(STD_OUTPUT_HANDLE);



void Komunikat::powiadomUzytkownika(const char* wiadomosc)
{
	SetConsoleTextAttribute(ekranHandle, FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout << std::endl << wiadomosc << std::endl;
}


Komunikat::~Komunikat()
{
	CloseHandle(ekranHandle);
}
