using namespace std;
#include <string>
#include "string"

#include <iostream>
#include "fitxes.hpp"

void Fitxa::setColorITipusFitxa(char fitxa)
{
	switch (fitxa) // Posar aquest codi en Fitxa
	{
	//case '_':
		//m_tipusFitxa = TIPUS_EMPTY;
		//m_colorFitxa = COLOR_UNDEFINED; //ja no te sentit perque un estat de no-fitxa ja no es representa dins la fitxa sino per nullptr
		
		break;
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
	cout << "mida de larray de moviments valids actuals: " << m_moviments.size()<<endl;
	//m_moviments.resize(0);
	
}