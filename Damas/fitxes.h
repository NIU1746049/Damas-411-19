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
	COLOR_UNDEFINED,//Les fitxes empty no tindran color
	COLOR_NEGRE,
	COLOR_BLANC
} ColorFitxa;


class Fitxa
{
public:
	/*Fitxa()
	{
		m_viva = true;
		for (int i = 0;i < 100;i++) {
			Moviment m
			m_moviments[i] = m;
		}
		
	
	
	}*/
	Fitxa() {
		m_colorFitxa = COLOR_UNDEFINED;
		m_tipusFitxa = TIPUS_EMPTY;
		m_viva = true;
	}
	Fitxa(TipusFitxa tipus, ColorFitxa color, Posicio pos) {
		m_posicio = pos;
		m_viva = true;
		m_tipusFitxa = tipus;
		if (tipus != TIPUS_EMPTY) {
			m_colorFitxa = color;

		}
		else {
			m_colorFitxa = COLOR_UNDEFINED;//Programacio defensiva. A part fara mes rapid el programa perque NO haure de
			//canviar el color per a cada fitxa que no sigui una fitxa (mentens?) dins de cada costat. Parteix taulell per la meitat i jasta.

		}
	}

	//getters
	TipusFitxa getTipusFitxa()const { return m_tipusFitxa; }
	ColorFitxa getColorFitxa() const{ return m_colorFitxa; }
	Posicio getPosicio()const { return m_posicio;}
	int getNMoviments()const { return m_nMoviments;}


	//setters
	void setTipusFitxa(TipusFitxa tipusFitxa) { m_tipusFitxa = tipusFitxa; }
	void setColorFitxa(ColorFitxa colorFitxa) { m_colorFitxa = colorFitxa; }
	void setPosicio(Posicio posicio) { m_posicio = posicio; }
	void setMovimentPos(int pos, Moviment m) { m_moviments[pos] = m; }
	void setNMovimentsValids(int nMv) { m_nMoviments = nMv; }
	
	
	
	
	//AQUEST PROBLEMATIC DE DALT
	
	
	
private:
	Posicio m_posicio;
	Moviment m_moviments[100];
	int m_nMoviments = 0;

	TipusFitxa m_tipusFitxa;
	ColorFitxa m_colorFitxa;
	bool m_viva;
};

