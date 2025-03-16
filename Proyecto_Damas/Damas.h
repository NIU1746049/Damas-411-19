#pragma once
#include <string>
using namespace std;

class Tauler
{
public:
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;
};

class Posicio
{
public:

private:

};

class Fitxa
{
public:

private:
	typedef enum
	{
		TIPUS_NORMAL,
		TIPUS_DAMA,
		TIPUS_EMPTY
	}TipusFitxa;

	typedef enum
	{
		COLOR_NEGRE,
		COLOR_BLANC,
	} ColorFitxa;
};


class Fitxa
{
public:

private:

};

class Moviment
{
public:

private:

};