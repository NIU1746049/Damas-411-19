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
	inicialitza(nomFitxer);
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus) 
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
	
	if ((mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
		(mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
		(mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
		(mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
	{
		m_columnaRatoli = (mousePosX - (POS_X_TAULER + CASELLA_INICIAL_X)) / AMPLADA_CASELLA;
		m_filaRatoli = (mousePosY - (POS_Y_TAULER + CASELLA_INICIAL_Y)) / ALCADA_CASELLA;
		if (mouseStatus && !m_mouseStatusAnterior)
		{
			m_columnaPeca = POS_X_TAULER + CASELLA_INICIAL_X + (m_columnaRatoli * AMPLADA_CASELLA);
			m_filaPeca = POS_Y_TAULER + CASELLA_INICIAL_Y + (m_filaRatoli * ALCADA_CASELLA);
			m_dibuixaFitxa = true;
		}
	}

	if(m_dibuixaFitxa)
	{
		GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, m_columnaPeca, m_filaPeca);
	}

	int posTextX = POS_X_TAULER;
	int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 120;
	string text = "PosX: " + to_string(m_columnaRatoli) + "\nPosY: " + to_string(m_filaRatoli);
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, text);

	m_mouseStatusAnterior = mouseStatus;

        
        
    // TODO 3: Imprimir text per pantalla
    //------------------------------------------
    // TODO 3.1: Mostrar la posició actual del ratolí a sota del tauler



	return false;
}




