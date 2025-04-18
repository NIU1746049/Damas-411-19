#pragma once

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
		m_nPosicions = 0;
		m_nMorts = 0;

	};
	Moviment(TipusMoviment tipus, Posicio posicions[N_FILES * N_COLUMNES], int nPosicions) {
		m_tipus = tipus;
		m_nPosicions = nPosicions;
		for (int i = 0; i < nPosicions; i++) {
			m_posicions[i] = posicions[i];
		}
	}
	

	int getNPosicions() { return m_nPosicions; }


private:
	TipusMoviment m_tipus;
	Posicio m_posicions[12];//Inclou la posicio d'origen
	int m_nPosicions;
	int m_nMorts;
};
