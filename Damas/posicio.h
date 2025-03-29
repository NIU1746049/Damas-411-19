#pragma once
#include <string>
#include <fstream>
using namespace std;


const int N_FILES = 8;
const int N_COLUMNES = 8;

class Posicio
{
public:
	Posicio() : m_fila(0), m_columna(0) {}; //<--No crec que sigui necessari una constructor per defecte pero ho deixo x recordar que segons el campus virtual hi ha d ser.
	Posicio(const string& posicio) // Borra comentario cuando lo veas: los argumentos (int fila, int columna) tienen que ser (const string& posicio)
	{ 
		fromString(posicio);
		//m_fila = fila;
		//m_columna = columna; 
	};
	//getters
	int getFila() const { return m_fila; }
	int getColumna() const { return m_columna; }
	//setters
	void setFila(int fila) { m_fila = fila; }
	void setColumna(int columna) { m_columna = columna; }

	string toString() const;
	void fromString(const string& pos);
	bool operator==(const Posicio& posicio) const;


private:
	int m_fila, m_columna;
};

ifstream& operator>>(ifstream& fitxer, Posicio& posicio);
ofstream& operator<<(ofstream& fitxer, const Posicio& posicio);