using namespace std;
#include <iostream>
#include "string"

#include "tauler.h"

void Tauler::inicialitza(const string& nomFitxer)
{
	//Implementar: if nomFitxer == null -> empieza de 0 ///////////////////////////////////
	llegeixTauler(nomFitxer, m_taulerEnChars);

	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			switch (m_taulerEnChars[fila][col])
			{
			case '_':
				m_tauler[fila][col].setTipusFitxa(TIPUS_EMPTY);
				break;
			case 'O':
				m_tauler[fila][col].setTipusFitxa(TIPUS_NORMAL);
				m_tauler[fila][col].setColorFitxa(COLOR_BLANC);
				break;
			case 'X':
				m_tauler[fila][col].setTipusFitxa(TIPUS_NORMAL);
				m_tauler[fila][col].setColorFitxa(COLOR_NEGRE);
				break;
			case 'D':
				m_tauler[fila][col].setTipusFitxa(TIPUS_DAMA);
				m_tauler[fila][col].setColorFitxa(COLOR_BLANC);
				break;
			case 'R':
				m_tauler[fila][col].setTipusFitxa(TIPUS_DAMA);
				m_tauler[fila][col].setColorFitxa(COLOR_NEGRE);
				break;
			}
		}
	}
}

void Tauler::actualitzaMovimentsValids() const
{

}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{

}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) // Esto hace que la array Fitxes y la matri
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
