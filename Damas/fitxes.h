#pragma once
using namespace std;

#include "posicio.h"
#include "moviment.h"

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_DAMA,
	TIPUS_EMPTY
}TipusFitxa;

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC,
} ColorFitxa;

class Fitxa
{
public:
	Fitxa() : m_viva(true) {}
	//getters
	TipusFitxa getTipusFitxa() { return m_tipusFitxa; }
	ColorFitxa getColorFitxa() { return m_colorFitxa; }


	//setters
	void setTipusFitxa(TipusFitxa tipusFitxa) { m_tipusFitxa = tipusFitxa; }
	void setColorFitxa(ColorFitxa colorFitxa) { m_colorFitxa = colorFitxa; }

	//void moure(int Fw, int L, int steps); // 1 = Fw/L && 0 = Bw/R   // <-- Creo que no hace falta, pq el movimiento se decidira a partir de Moviment. Que da la posicion absoulta, no relativa (se puede hacer con un set)

private:
	Posicio m_posicio;//Borra comentario cuando lo veas
	Moviment m_moviments[100];
	TipusFitxa m_tipusFitxa;
	ColorFitxa m_colorFitxa;
	bool m_viva;
};

