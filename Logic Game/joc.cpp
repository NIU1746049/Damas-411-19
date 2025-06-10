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

	if ((mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
		(mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
		(mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
		(mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
	{
		m_columnaRatoli = (mousePosX - (POS_X_TAULER + CASELLA_INICIAL_X)) / AMPLADA_CASELLA;
		m_filaRatoli = (mousePosY - (POS_Y_TAULER + CASELLA_INICIAL_Y)) / ALCADA_CASELLA;

		if (mouseStatus && !m_mouseStatusAnterior)
		{
			switch (m_pantalla)
			{
			case PANTALLA_MENU:
				if (mousePosX > 300 && mousePosX < 450 && mousePosY > 310 && mousePosY < 365)
				{
					m_pantalla = PANTALLA_JOC;

					m_tauler.setModeReplay(false);
				}
				else if (mousePosX > 300 && mousePosX < 450 && mousePosY > 375 && mousePosY < 430)
				{
					m_pantalla = PANTALLA_REPLAY;

					m_tauler.inicialitzaPartidaReplay("historial_moviments28.txt");
					m_tauler.setModeReplay(true);
				}
				break;

			case PANTALLA_JOC:
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
						//Si se selecciona otra ficha del mismo color: siguie habiendo una ficha seleccionada, solo cambio cual
						m_colFitxaSeleccionada = m_columnaRatoli;
						m_filaFitxaSeleccionada = m_filaRatoli;
					}
					else
					{
						//Si se selecciona una cassilla valida: se mueve y se desselecciona la ficha
						Posicio posMovimentI;
						bool trobat = false;
						int indexMov = 0;
						while (!trobat && indexMov < m_tauler.getPtrTauler()[m_filaFitxaSeleccionada][m_colFitxaSeleccionada]->getNMoviments())
						{
							posMovimentI = m_tauler.getPtrTauler()[m_filaFitxaSeleccionada][m_colFitxaSeleccionada]->getMoviments()[indexMov].getUltimaPosicio();
							if (posMovimentI.getFila() == m_filaRatoli && posMovimentI.getColumna() == m_columnaRatoli)
							{
								trobat = true;
							}
							indexMov++;
						}

						if (trobat)
						{
							m_tauler.mouFitxa(Posicio(m_filaFitxaSeleccionada, m_colFitxaSeleccionada), Posicio(m_filaRatoli, m_columnaRatoli));
						}

						m_tauler.mouFitxa(Posicio(m_filaFitxaSeleccionada, m_colFitxaSeleccionada), Posicio(m_filaRatoli, m_columnaRatoli));
						m_fitxaSeleccionada = false;
					}
				}
				break;

			case PANTALLA_REPLAY:
				if (mousePosX < 250)
				{
					m_tauler.replayEndavant();
				}
				else
				{
					m_tauler.replayEndavant();
				}
				break;

			case PANTALLA_VICT_BLANQUES: 
				m_pantalla = PANTALLA_MENU;
				break;

			case PANTALLA_VICT_NEGRES:
				m_pantalla = PANTALLA_MENU;
				break;
			}
		}
	}


	int posTextX = POS_X_TAULER + 20;
	int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 120;
	switch (m_pantalla)
	{
	case PANTALLA_MENU:
		GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 300, 300, 1.5, "Play");
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 300, 360, 1.5, "Replay");

		//Para ver las coordenadas del raton y saber donde poner las imagenes
		//text = "Coordenada X: " + to_string(mousePosX) + "\nCoordenada Y: " + to_string(mousePosY);
		//GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 100, 100, 0.8, text);
		break;

	case PANTALLA_JOC:
		visualitzaJoc(POS_X_TAULER + CASELLA_INICIAL_X, POS_Y_TAULER + CASELLA_INICIAL_Y, AMPLADA_CASELLA, ALCADA_CASELLA);

		if(m_tauler.getTornBlanques())
		{
			GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, "Torn: Blanques");
		}
		else
		{
			GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, "Torn: Negres");
		}

		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, POS_Y_TAULER, 0.8, "Mode: Play");
		break;

	case PANTALLA_REPLAY:
		visualitzaJoc(POS_X_TAULER + CASELLA_INICIAL_X, POS_Y_TAULER + CASELLA_INICIAL_Y, AMPLADA_CASELLA, ALCADA_CASELLA);

		if (m_tauler.getTornBlanques())
		{
			GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, "Torn: Blanques");
		}
		else
		{
			GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, "Torn: Negres");
		}

		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, POS_Y_TAULER, 0.8, "Mode: Replay");
		break;

	case PANTALLA_VICT_BLANQUES:
		visualitzaJoc(POS_X_TAULER + CASELLA_INICIAL_X, POS_Y_TAULER + CASELLA_INICIAL_Y, AMPLADA_CASELLA, ALCADA_CASELLA);

		GraphicManager::getInstance()->drawFont(FONT_RED_30, 220, 250, 2, " VICTORIA\nBLANQUES");
		break;

	case PANTALLA_VICT_NEGRES:
		visualitzaJoc(POS_X_TAULER + CASELLA_INICIAL_X, POS_Y_TAULER + CASELLA_INICIAL_Y, AMPLADA_CASELLA, ALCADA_CASELLA);

		GraphicManager::getInstance()->drawFont(FONT_RED_30, 230, 250, 2, "VICTORIA\n NEGRES");
		break;
	}

	



	//1) Seleccionar fichas (tener en cuenta el color, IMPORTANTE)
	//2) Iluminar los movimientos posibles que tiene esa ficha
	//3) Seleccionar un movimiento: si el movimiento es posible: A. Si no: B. Si se ha seleccionado otra ficha: C.
	//4A) Ejecutar el movimiento e ir a 1)
	//4B) Desseleccionar la ficha e ir a 1)
	//4C) Ir a 2)

	if (m_tauler.getTornBlanques() != m_tauler.getTornFrameAnteriorBlanques())
	{
		m_tauler.actualitzaMovimentsValids();
	}
	
	m_tauler.setTornFrameAnteriorBlanques(m_tauler.getTornBlanques());
	m_mouseStatusAnterior = mouseStatus;

	if (m_tauler.getNNegres() == 0 || (!m_tauler.getTornBlanques() && m_tauler.getNMovNegres() == 0))
	{
		inicialitza("null");
		m_pantalla = PANTALLA_VICT_BLANQUES;
		return true;
	}
	else if (m_tauler.getNBlanques() == 0 || (m_tauler.getTornBlanques() && m_tauler.getNMovBlanques() == 0))
	{
		inicialitza("null");
		m_pantalla = PANTALLA_VICT_NEGRES;
		return true;
	}
	else
	{
		return false;
	}
}


void Joc::visualitzaJoc(int zeroDeX, int zeroDeY, int ampladaX, int alcadaY)
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

	m_tauler.visualitzaTauler(zeroDeX, zeroDeY, ampladaX, alcadaY);

	if (m_fitxaSeleccionada == true)
	{
		m_tauler.getPtrTauler()[m_filaFitxaSeleccionada][m_colFitxaSeleccionada]->visualitzaMoviments(zeroDeX, zeroDeY, ampladaX, alcadaY);
	}
}

