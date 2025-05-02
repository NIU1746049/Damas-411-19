#include <string>
//#include <iostream>
using namespace std;

#include "posicio.hpp"

string Posicio::toString() const 
{
	string pos = "a1";
	pos[0] = 'a' + m_columna;
	pos[1] = '1' + (N_FILES - 1) - m_fila;
	return pos;
}

void Posicio::fromString(const string& pos) 
{
	m_fila = (N_FILES - 1) - (pos[1] - '1');
	m_columna = pos[0] - 'a';
}

bool Posicio::operator==(const Posicio& posicio) const
{
	if (m_fila == posicio.m_fila && m_columna == posicio.m_columna)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ifstream& operator>>(ifstream& fitxer, Posicio& posicio)
{
	string pos = "a1";
	fitxer >> pos;
	posicio.fromString(pos);
	return fitxer;
}

ostream& operator<<(ostream& fitxer, const Posicio& posicio) 
{
	string pos = posicio.toString();
	fitxer << pos;
	return fitxer;
}

void llegeixFitxa(const string& nomFitxer, char& tipusFitxa, Posicio& posicio) 
{ //A llegeixFitxa le entra una posicion? Esta funcion esta en el enunciado?
	ifstream fitxer;
	fitxer.open(nomFitxer);
	fitxer >> tipusFitxa;
	fitxer >> posicio;
	fitxer.close();
}

void escriuFitxa(const string& nomFitxer, char tipusFitxa, const Posicio& posicio) 
{ //A escriuFitxa le entra una posicion? Esta funcion esta en el enunciado?
	ofstream fitxer(nomFitxer);
	fitxer << tipusFitxa << ' ';
	fitxer << posicio;
	fitxer.close();
}