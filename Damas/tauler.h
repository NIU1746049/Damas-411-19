#pragma once
#include <string>
using namespace std;
#include <iostream>
#include "fitxes.h"


class Tauler
{
public:
	Tauler() {
		m_tornBlanques = true;
		m_filaFitxaSeleccionada = 0;
		m_colFitxaSeleccionada = 0;
		m_nBlanques = 0;
		m_nNegres = 0;
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
	//bool mouFitxa(const Posicio& origen, const Posicio& desti);

	bool mouFitxa(const Posicio& desti);

	string toString() const;

	bool seleccionaFitxa(); // Cambia col y filaSeleccionada (cout de "Introduce la ficha" y cin)
	bool seleccionaDesti(Posicio &desti); //Fa les comprovacions adients tambe


	//int comptaNumeroMovimentsPossibles(const ColorFitxa color) const;
	bool comptaNumeroMovimentsPossibles(const ColorFitxa color) const;

	void convertirADama();
	bool bufar();
	void eliminarFitxesMortes(); // Asignarlas como vivas despues de eliminarlas
	bool gameOver();

	//Comprovar moviments
	bool normalMoure(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const;
	bool normalMatar(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const;
	bool normalMatarMultiples(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const;

	bool damaMoure(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const;
	bool damaMatar(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const;
	bool damaMatarMultiples(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const;

	//getters
	int getNBlanques() const { return m_nBlanques; }
	int getNNegres() const { return m_nNegres; }
	bool getTornBlanques() const { return m_tornBlanques; }

	//setters
	void setTornBlanques(bool tornBlanques) { m_tornBlanques = tornBlanques; }

	void actualitzaTaulerEnChars();
	

private:

	int m_filaFitxaSeleccionada;
	int m_colFitxaSeleccionada;
	Fitxa m_tauler[N_FILES][N_COLUMNES];
	char m_taulerEnChars[N_FILES][N_COLUMNES];
	bool m_tornBlanques;

	int m_nBlanques;
	int m_nNegres;


	//inicialitza
	void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]) const;

	
	//actualitzaMovimentsValids

	Moviment movimentFet;//El moviment que ha fet en la iteracio actual del joc

};