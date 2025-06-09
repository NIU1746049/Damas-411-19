#pragma once
#include <string>
using namespace std;
#include <iostream>
#include "fitxes.hpp"

#include "posicio.hpp"

class Tauler
{
public:
	Tauler() {
		m_tornBlanques = true;
		m_tornFrameAnteriorBlanques = false;
		m_filaFitxaSeleccionada = 0;
		m_colFitxaSeleccionada = 0;
		m_nBlanques = 0;
		m_nNegres = 0;
		m_nMovBlanques = -1;
		m_nMovNegres = -1;


		m_tauler = new Fitxa**[N_FILES];
		for (int i = 0; i < N_FILES; i++)
		{
			m_tauler[i] = new Fitxa*[N_COLUMNES];
		}

		for (int i = 0;i < N_FILES;i++) {
			for (int j = 0;j < N_COLUMNES;j++) {
				m_tauler[i][j] = nullptr;
			}
		}


	}
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();// Recorre todas las Fitxes y actualiza su variable Moviment con todos los movimientos validos
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[MAX_POSICIONS]);

	bool mouFitxa(const Posicio& origen, const Posicio& desti);//Em diu que li foti una posicio mes que sino peta.

	string toString() const;


	//--- 
	//Comentades pero no eliminades perque potser ens serveixen en un futur:
	//bool seleccionaFitxa(); // Cambia col y filaSeleccionada (cout de "Introduce la ficha" y cin)
	//bool seleccionaDesti(Posicio& desti); //Fa les comprovacions adients tambe
	//---

	//int comptaNumeroMovimentsPossibles(const ColorFitxa color) const;
	bool comptaNumeroMovimentsPossibles(const ColorFitxa color) const;

	void convertirADama();
	bool bufar(const Posicio& posicioOrigen, Moviment& movimentFet);
	void eliminarFitxesMortes();
	bool gameOver();


	//Comprovar moviments
		//normal:
	bool normalMoure(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const;
	bool normalMatar(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const;
	//bool normalMatarMultiples(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const;
	bool normalMatarMultiples(Posicio posicioActual, vector <Moviment>& movimentsValids, Posicio fitxaQueEsMou)const;
		//dama:
	bool damaMoure(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const;
	bool damaMatar(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const;
	bool damaMatarMultiples(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const;
	

	//Auxiliar Moviments
	//void brancaNormal(Posicio posicioOrigen,vector <Moviment> &movimentsDefinitius, Posicio fitxaQueEsMou)const;
	void brancaNormal(Posicio posicioOrigen, Posicio mortBranca, Moviment movimentBranca, vector <Moviment>& movimentsDefinitius, vector <Moviment> tmpMoviments, Posicio fitxaQueEsMou)const;
	void brancaDama(Posicio posicioOrigen, vector <Moviment>& movimentsDefinitius, Posicio fitxaQueEsMou)const;


	//getters
	bool getModeReplay() const { return m_modeReplay; }
	int getNBlanques() const { return m_nBlanques; }
	int getNNegres() const { return m_nNegres; }
	int getNMovBlanques() const { return m_nMovBlanques; }
	int getNMovNegres() const { return m_nMovNegres; }
	bool getTornBlanques() const { return m_tornBlanques; }
	bool getTornFrameAnteriorBlanques() const { return m_tornFrameAnteriorBlanques; }
	Fitxa*** getPtrTauler() const { return m_tauler; }
	void getNPartida();

	//setters
	void setModeReplay(bool modeReplay) { m_modeReplay = modeReplay; }
	void setTornBlanques(bool tornBlanques) { m_tornBlanques = tornBlanques; }
	void setTornFrameAnteriorBlanques(bool tornAnteriorBlancques) { m_tornFrameAnteriorBlanques = tornAnteriorBlancques; }
	void actualitzaTaulerEnChars();

	void visualitzaTauler(int zeroDeX, int zeroDeY, int ampladaX, int alcadaY);
	void guardarMoviment(Moviment movimentFet, const string nomFitxer);
	void inicialitzaPartidaReplay(const string nomFitxer);

	void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]) const;
	void replayEndavant();
	void replayCapEnrere();
	void RecreaPartida(const string nomFitxer);
private:

	int m_filaFitxaSeleccionada;
	int m_colFitxaSeleccionada;
	Fitxa*** m_tauler;
	char m_taulerEnChars[N_FILES][N_COLUMNES];
	bool m_tornBlanques;
	bool m_tornFrameAnteriorBlanques;

	int m_nBlanques;
	int m_nNegres;
	int m_nMovBlanques;
	int m_nMovNegres;

	bool m_modeReplay;
	//inicialitza
	
	
	int m_nPartida;
	string m_nomFitxerPartida;
	int m_nMovimentsReplay;
	Posicio** m_partidaReplay;
	int m_contadorMovimentsReplay;
	Moviment movimentFet;//El moviment que ha fet en la iteracio actual del joc

};