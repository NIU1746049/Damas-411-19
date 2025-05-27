//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"

void Joc::inicialitza(const string nomFitxer)
{
	m_tauler.inicialitza(nomFitxer);
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus) 
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
	
	if (m_tauler.getTornBlanques() != m_tornAnteriorBlanques)
	{
		m_tauler.actualitzaMovimentsValids();
	}

	if ((mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
		(mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
		(mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
		(mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
	{
		m_columnaRatoli = (mousePosX - (POS_X_TAULER + CASELLA_INICIAL_X)) / AMPLADA_CASELLA;
		m_filaRatoli = (mousePosY - (POS_Y_TAULER + CASELLA_INICIAL_Y)) / ALCADA_CASELLA;
		cout << "Fitxa seleciconada = " << m_fitxaSeleccionada << endl;

		if (mouseStatus && !m_mouseStatusAnterior)
		{
			if (m_fitxaSeleccionada == false)
			{
				if (m_tauler.getPtrTauler()[m_filaRatoli][m_columnaRatoli] != nullptr && m_tauler.getTornBlanques() == m_tauler.getPtrTauler()[m_filaRatoli][m_columnaRatoli]->getColorFitxa() - 1) //COLOR_NEGRE = 1 y COLOR_BLANC = 2, por eso el "-1"
				{
					m_colFitxaSeleccionada = m_columnaRatoli;
					m_filaFitxaSeleccionada = m_filaRatoli;
					m_fitxaSeleccionada = true;
				}
			}
			else if (m_fitxaSeleccionada == true)
			{
				if (m_tauler.getPtrTauler()[m_filaRatoli][m_columnaRatoli] != nullptr && m_tauler.getTornBlanques() == m_tauler.getPtrTauler()[m_filaRatoli][m_columnaRatoli]->getColorFitxa() - 1) //COLOR_NEGRE = 1 y COLOR_BLANC = 2, por eso el "-1"
				{
					//Si se selecciona otra ficha del mismo color: iguie habiendo una ficha seleccionada, solo cambio cual
					m_colFitxaSeleccionada = m_columnaRatoli;
					m_filaFitxaSeleccionada = m_filaRatoli;
				}
				//else if()
				//{
				//	//Si se selecciona una cassilla valida: se mueve y se desselecciona la ficha


				//	m_fitxaSeleccionada = false;
				//}
			}
		}
	}

	visualitzaJoc(POS_X_TAULER + CASELLA_INICIAL_X, POS_Y_TAULER + CASELLA_INICIAL_Y, AMPLADA_CASELLA, ALCADA_CASELLA);

	int posTextX = POS_X_TAULER;
	int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 120;
	string text = "PosX: " + to_string(m_columnaRatoli) + "\nPosY: " + to_string(m_filaRatoli);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, text);



	//1) Seleccionar fichas (tener en cuenta el color, IMPORTANTE)
	//2) Iluminar los movimientos posibles que tiene esa ficha
	//3) Seleccionar un movimiento: si el movimiento es posible: A. Si no: B. Si se ha seleccionado otra ficha: C.
	//4A) Ejecutar el movimiento e ir a 1)
	//4B) Desseleccionar la ficha e ir a 1)
	//4C) Ir a 2)

	
	m_tornAnteriorBlanques = m_tauler.getTornBlanques();
	m_mouseStatusAnterior = mouseStatus;
	return false;
}


void Joc::visualitzaJoc(int zeroDeX, int zeroDeY, int ampladaX, int alcadaY)
{
	m_tauler.visualitzaTauler(zeroDeX, zeroDeY, ampladaX, alcadaY);

	if (m_fitxaSeleccionada == true)
	{
		m_tauler.getPtrTauler()[m_colFitxaSeleccionada][m_filaFitxaSeleccionada]->visualitzaMoviments(zeroDeX, zeroDeY, ampladaX, alcadaY);
	}
}

