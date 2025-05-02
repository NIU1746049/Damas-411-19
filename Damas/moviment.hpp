#pragma once

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
		m_nPosicions = 0;
		m_nMorts = 0;
	};
	Moviment(TipusMoviment tipus, Posicio posicions[N_FILES * N_COLUMNES], int nPosicions, int nMorts, Posicio morts[MAX_MORTS]) {
		m_tipus = tipus;
		m_nPosicions = nPosicions;
		for (int i = 0; i < nPosicions; i++) {
			m_posicions[i] = posicions[i];
		}
		m_nMorts = nMorts;
		for (int i = 0;i < nMorts;i++) {
			m_morts[i] = morts[i];
		}
	}
	
	//getters
	int getNPosicions() { return m_nPosicions; }
	Posicio getPosicioPos(int index) { return m_posicions[index]; }
	TipusMoviment getTipus() { return m_tipus; }
	int getNMorts() { return m_nMorts; }
	Posicio getMortsPos(int index) { return m_morts[index]; }
	
	//setters
	void setPosicioPos(int index, Posicio p) { m_posicions[index] = p; }
	void setNPosicions(int n) { m_nPosicions = n; }
	void setNMorts(int n) { m_nMorts = n; }
	void addMort(Posicio victima) { m_morts[m_nMorts] = victima; m_nMorts++; }
	void setMortsPos(int index, Posicio pos) { m_morts[index] = pos; }

private:
	TipusMoviment m_tipus;
	Posicio m_posicions[MAX_POSICIONS];//Inclou la posicio d'origen
	int m_nPosicions;
	Posicio m_morts[MAX_MORTS];
	int m_nMorts;
	

};
