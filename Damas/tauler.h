#pragma once
#include <string>
using namespace std;

#include "fitxes.h"


class Tauler
{
public:
	Tauler() : m_tornBlanques(true), m_filaFitxaSeleccionada(0), m_colFitxaSeleccionada(0) {}
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids() const; // Recorre todas las Fitxes y actualiza su variable Moviment con todos los movimientos validos
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;

	
	void seleccionaFitxa(const string& posFitxa);
	void mouFitxa(int filaFitxa, int colFitxa);

private:
	int m_filaFitxaSeleccionada;
	int m_colFitxaSeleccionada;
	Fitxa m_tauler[N_FILES][N_COLUMNES];
	char m_taulerEnChars[N_FILES][N_COLUMNES];
	bool m_tornBlanques;

	//inicialitza
	void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]) const;
	//actualitzaMovimentsValids

};
