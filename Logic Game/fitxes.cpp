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
	for (int i = 0;i < getNMoviments();i++) 
	{
		m_moviments.pop_back();
	}	
}