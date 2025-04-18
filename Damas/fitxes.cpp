using namespace std;
#include <string>
#include "string"

#include "fitxes.h"

void Fitxa::setColorITipusFitxa(char fitxa)
{
	switch (fitxa) // Posar aquest codi en Fitxa
	{
	case '_':
		m_tipusFitxa = TIPUS_EMPTY;
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
