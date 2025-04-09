#pragma once
#include <string>
using namespace std;

#include "fitxes.h"


class Tauler
{
public:
	Tauler() {
		m_tornBlanques = true;
		m_filaFitxaSeleccionada = 0;
		m_colFitxaSeleccionada = 0;

		/*
		for (int i = 0; i < N_FILES;i++) {
			for (int j = 0; j < N_COLUMNES;j++) {
				Fitxa f;

			}
		}
		*/
	}
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();// Recorre todas las Fitxes y actualiza su variable Moviment con todos los movimientos validos
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;

	
	void seleccionaFitxa(const string& posFitxa);
	void mouFitxa(int filaFitxa, int colFitxa);

	void transportar(const Posicio& origen, const Posicio& desti);//fitxa1<->fitxa2 pos1<->pos2 (notis que al swapejar les fitxes ja hi ha hagut un canvi en les posicions per tant un segons canvi les deixa com estaven originalment.)

	//Comprovar moviments
	bool normalMoure(Posicio posicioActual, Moviment movimentsValids[100], int& nMovimentsValids)const;
	bool normalMatar(Posicio posicioActual, Moviment movimentsValids[100], int& nMovimentsValids)const;
	bool normalMatarMultiples(Posicio posicioActual, Moviment movimentsValids[100], int& nMovimentsValids)const;

	bool damaMoure(Posicio posicioActual, Moviment movimentsValids[100], int& nMovimentsValids)const;
	bool damaMatar(Posicio posicioActual, Moviment movimentsValids[100], int& nMovimentsValids)const;
	bool damaMatarMultiples(Posicio posicioActual, Moviment movimentsValids[100], int& nMovimentsValids)const;





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
