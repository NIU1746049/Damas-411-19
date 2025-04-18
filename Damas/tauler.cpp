using namespace std;
#include <iostream>
#include "string"

#include "tauler.h"

void Tauler::inicialitza(const string& nomFitxer)
{
	if (nomFitxer != "null")
	{
		llegeixTauler(nomFitxer, m_taulerEnChars);
	}
	else
	{
		m_nBlanques = 12;
		m_nNegres = 12;
		for (int fila = 0; fila < N_FILES; fila++)
		{
			for (int col = 0; col < N_COLUMNES; col++)
			{
				if (fila <= 3) // Si estan arriba
				{
					if ((col + fila) % 2 == 1) // Es negra
					{
						m_taulerEnChars[fila][col] = 'X';
					}
					else
					{
						m_taulerEnChars[fila][col] = '_';
					}
				}
				else if (fila >= 4) // Si estan abajo
				{
					if ((col + fila) % 2 == 1) // Es blanca
					{
						m_taulerEnChars[fila][col] = 'O';
					}
					else
					{
						m_taulerEnChars[fila][col] = '_';
					}
				}
			}
		}
	}

	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			m_tauler[fila][col].setColorITipusFitxa(m_taulerEnChars[fila][col]);
			////////////////////////// IMPLEMENTAR setNumFichasNegras y blancas //////////////////////////////////////////
		}
	}
}

//Normal
bool Tauler::normalMoure(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const
{
	bool valid = false;
	int incrementVertical;
	if (m_tauler[posicioActual.getFila()][posicioActual.getColumna()].getColorFitxa() == COLOR_BLANC) {
		incrementVertical = 1;
		
	}
	else {
		incrementVertical = -1;

	}
	for (int i = -1;i < 2;i++) {
		if(((posicioActual.getFila()+incrementVertical)<N_FILES)&& ((posicioActual.getColumna() + i) < N_COLUMNES) && (i != 0)) {//Parentesis ben posats???????????
			if ((m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getFila() + i].getTipusFitxa() == TIPUS_EMPTY)) {
				//movimentsValids[nMovimentsValids] = m_tauler[posicioActual.getFila() + 1][posicioActual.getFila() + i]

				TipusMoviment tM = NORMAL_NO_MATAR;
				Posicio posicions[2] = { posicioActual,m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getFila() + i].getPosicio() };
				Moviment nouMoviment(tM, posicions, 2);
				valid = true;
				nMovimentsValids++;
			}
		}
	}
	return valid;
	
}


bool Tauler::normalMatar(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const {

	bool valid = false;
	int incrementVertical;
	if (m_tauler[posicioActual.getFila()][posicioActual.getColumna()].getColorFitxa() == COLOR_BLANC) {
		incrementVertical = 1;

	}
	else {
		incrementVertical = -1;

	}
	for (int i = 0; i < 2;i++) {


		if (((posicioActual.getFila() + incrementVertical) < N_FILES) && ((posicioActual.getColumna() + i) < N_COLUMNES) &&
			((posicioActual.getFila() + 2 * incrementVertical) < N_FILES) && ((posicioActual.getColumna() + 2 * i) < N_COLUMNES) &&
			(i != 0)) {//Parentesis ben posats???????????

			if ((m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getFila() + i].getTipusFitxa() == TIPUS_NORMAL) &&
				(m_tauler[posicioActual.getFila() + 2 * incrementVertical][posicioActual.getFila() + 2 * i].getTipusFitxa() == TIPUS_EMPTY) &&
				(m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getFila() + i].getColorFitxa() != m_tauler[posicioActual.getFila()][posicioActual.getFila()].getColorFitxa())) {
				//Fotre el moviment aqui
				TipusMoviment tM = NORMAL_MATAR;
				Posicio posicions[3] = { posicioActual,
					m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getFila() + i].getPosicio(),
					m_tauler[posicioActual.getFila() + 2*incrementVertical][posicioActual.getFila() + 2*i].getPosicio()
				};
				Moviment nouMoviment(tM, posicions, 3);
				valid = true;
				nMovimentsValids++;

			}
		}
	}
	return valid;
}

bool Tauler::normalMatarMultiples(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const {
	//For de mentres sigui true el normalMatar
	return true;
}



//dama
bool Tauler::damaMoure(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const
{
	return true;
}

bool Tauler::damaMatar(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const {
	return true;
}

bool Tauler::damaMatarMultiples(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const {
	return true;
}



// Esto no tendria que estar en fitxa???????????????????????????????????????????????????????????????????????????????????
void esborraMoviments(Fitxa fitxa) {
	for (int i = 0;i < fitxa.getNMoviments();i++) {
		Moviment m;
		fitxa.setMovimentPos(i, m);
	}
}


void Tauler::actualitzaMovimentsValids()//Es important que sigui const?
{
	for (int fila = 0; fila < N_FILES; fila++) 
	{
		for (int col = 0; col < N_COLUMNES; col++) 
		{
			esborraMoviments(m_tauler[fila][col]);


			Moviment mv[100] = {};
			int nMv = 0;



			if (m_tauler[fila][col].getTipusFitxa() == TIPUS_NORMAL) 
			{
				Posicio pos = m_tauler[fila][col].getPosicio();
				

				normalMoure(pos, mv, nMv);
				
				if (normalMatar(pos, mv, nMv)) {
					normalMatarMultiples(pos, mv, nMv);
				}

			}
			else {
				if (m_tauler[fila][col].getTipusFitxa() == TIPUS_DAMA) 
				{
					Posicio pos = m_tauler[fila][col].getPosicio();


					damaMoure(pos, mv, nMv);

					if (damaMatar(pos, mv, nMv)) {
						damaMatarMultiples(pos, mv, nMv);
					}
				}
			}
			for (int j = 0; j < nMv; j++) 
			{
				m_tauler[fila][col].setMovimentPos(j,mv[j]);//Li fot moviments a la fitxa visitada en el bucle for
				m_tauler[fila][col].setNMovimentsValids(nMv);
			}

		}
	}
}


void Tauler::transportar(const Posicio& origen, const Posicio& desti) {//El fet concret de moure d'un lloc a l'altre

	
	Fitxa fitxaAuxiliar = m_tauler[desti.getFila()][desti.getColumna()];//podriem fer std::swap i ens estalviavem aixo. Pero ns si esta permes per tema deteccio de  IA com als seminaris de MD.

	m_tauler[desti.getFila()][desti.getColumna()] = m_tauler[origen.getFila()][origen.getColumna()];
	m_tauler[origen.getFila()][origen.getColumna()] = fitxaAuxiliar;

	m_tauler[desti.getFila()][desti.getColumna()].setPosicio(desti);
	m_tauler[origen.getFila()][origen.getColumna()].setPosicio(origen);

	
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	return false;
}

string Tauler::toString() const 
{
	string taula = "";
	for (int fila = 0; fila < N_FILES; fila++)
	{
		taula = taula + to_string(8 - fila) + ":";
		for (int col = 0; col < N_COLUMNES; col++)
		{
			taula = taula + m_taulerEnChars[fila][col] + " ";
		}
		taula = taula + "\n";
	}

	taula = taula + "  ";
	for (int i = 0; i < N_FILES; i++)
	{
		taula = taula + (char)('A' + i) + " ";
	}

	return taula;
}



void Tauler::llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]) const
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			tauler[i][j] = '_';
		}
	}

	ifstream fitxer;
	fitxer.open(nomFitxer);

	Posicio posicions[32];
	char fitxes[32];

	if (fitxer.is_open())
	{
		int i = 0;
		while (fitxer.eof() == false)
		{
			fitxer >> fitxes[i];
			fitxer >> posicions[i];

			tauler[posicions[i].getFila()][posicions[i].getColumna()] = fitxes[i];

			i++;
		}
	}
	fitxer.close();
}
