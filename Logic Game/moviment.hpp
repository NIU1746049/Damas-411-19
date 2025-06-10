#pragma once
#include <vector>
#include "posicio.hpp"
const int MAX_POSICIONS = 16;
const int MAX_MORTS = 8;

typedef enum//Aixi es podra comprovar despres mes facilment si hi havia algun moviment en el q podies matar
{
	EMPTY,
	NORMAL_NO_MATAR,
	NORMAL_MATAR,
	NORMAL_MATAR_MULTIPLES,
	DAMA_NO_MATAR,
	DAMA_MATAR,
	DAMA_MATAR_MULTIPLES,
}TipusMoviment;


class Moviment
{
public:
	Moviment() {
		m_tipus = EMPTY;
	};
	Moviment(TipusMoviment tipus, vector <Posicio> posicions, vector <Posicio> morts) {
		m_tipus = tipus;
		for (int i = 0; i < posicions.size(); i++) {
			m_posicions.push_back(posicions[i]);
		}
		for (int i = 0;i < morts.size();i++) {
			m_morts.push_back(morts[i]);
		}
		
	}
	
	
	//getters
	int getNPosicions() { return m_posicions.size(); }
	Posicio getPosicioPos(int index) { return m_posicions[index]; }
	Posicio getUltimaPosicio() { return m_posicions[m_posicions.size() - 1]; }
	TipusMoviment getTipus() { return m_tipus; }
	int getNMorts() { return m_morts.size(); }
	Posicio getMortsPos(int index) { return m_morts[index]; }
	
	//setters
	void afegirPosicio(Posicio p) { m_posicions.push_back(p); }
	void setNPosicions(int n) { m_posicions.resize(n); }
	void setNMorts(int n) { m_morts.resize(n); }
	void afegirMorts(Posicio pos) { m_morts.push_back(pos); }
	void setTipus(TipusMoviment tipus) { m_tipus = tipus; }


private:
	TipusMoviment m_tipus;
	vector <Posicio> m_posicions;
	vector <Posicio> m_morts;
	

};
