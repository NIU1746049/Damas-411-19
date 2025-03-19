#pragma once
#include <string>
using namespace std;


int N_FILES = 8;
int N_COLUMNES = 8;

class Posicio
{
public:
	//Posicio(); <--No crec que sigui necessari una constructor per defecte pero ho deixo x recordar que segons el campus virtual hi ha d ser.
	Posicio(int fila, int columna) 
	{ 
		m_fila = fila;
		m_columna = columna; 
	};
	int getFila() const 
	{
		return m_fila;
	};

	int getColumna() const 
	{
		return m_columna;
	};
	string toString() const;
	void fromString(const string& pos);
private:
	int m_fila, m_columna;
};
