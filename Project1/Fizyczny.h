#pragma once
#include "Pracownik.h"
class Fizyczny : public Pracownik
{
public:
	Fizyczny(std::string imie, std::string nazwisko, int zarobki, int id, std::string pozycja = "Pracownik Fizyczny");
	virtual ~Fizyczny();
};

