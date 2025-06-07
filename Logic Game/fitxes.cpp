using namespace std;
#include <string>
#include "string"

#include <iostream>
#include "fitxes.hpp"

void Fitxa::setColorITipusFitxa(char fitxa)
{
	switch (fitxa)
	{
	case 'O':
		m_tipusFitxa = TIPUS_NORMAL;
		m_colorFitxa = COLOR_BLANC;
		break;
	case 'X':
		m_tipusFitxa = TIPUS_NORMAL;
		m_colorFitxa = COLOR_NEGRE;
		break;
	case 'D':
		m_tipusFitxa = TIPUS_DAMA;
		m_colorFitxa = COLOR_BLANC;
		break;
	case 'R':
		m_tipusFitxa = TIPUS_DAMA;
		m_colorFitxa = COLOR_NEGRE;
		break;
	}
}


void Fitxa::esborraMoviments() 
{
	//for (int i = 0;i < getNMoviments();i++) 
	//{
	//	m_moviments.pop_back();
	//}	
	m_moviments.resize(0);
}

void Fitxa::visualitzaFitxa(int zeroDeX, int zeroDeY, int ampladaX, int alcadaY)
{
	if (m_tipusFitxa == TIPUS_NORMAL)
	{
		if (m_colorFitxa == COLOR_BLANC)
		{
			GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, zeroDeX + m_posicio.getColumna() * ampladaX, zeroDeY + m_posicio.getFila() * alcadaY);
		}
		else if (m_colorFitxa == COLOR_NEGRE)
		{
			GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_NEGRA, zeroDeX + m_posicio.getColumna() * ampladaX, zeroDeY + m_posicio.getFila() * alcadaY);
		}
	}
	else if (m_tipusFitxa == TIPUS_DAMA)
	{
		if (m_colorFitxa == COLOR_BLANC)
		{
			GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_BLANCA, zeroDeX + m_posicio.getColumna() * ampladaX, zeroDeY + m_posicio.getFila() * alcadaY);
		}
		else if (m_colorFitxa == COLOR_NEGRE)
		{
			GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_NEGRA, zeroDeX + m_posicio.getColumna() * ampladaX, zeroDeY + m_posicio.getFila() * alcadaY);
		}
	}
}

void Fitxa::visualitzaMoviments(int zeroDeX, int zeroDeY, int ampladaX, int alcadaY)
{
	for (int i = 0; i < m_moviments.size(); i++)
	{
		int ultimaPos = m_moviments[i].getNPosicions() - 1;
		GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, zeroDeX + m_moviments[i].getPosicioPos(ultimaPos).getColumna() * ampladaX, zeroDeY + m_moviments[i].getPosicioPos(ultimaPos).getFila() * alcadaY);
	}
}