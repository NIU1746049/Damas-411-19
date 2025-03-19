#include <string>
#include "posicio.h"
#include <iostream>
using namespace std;

string Posicio::toString() const {
	string pos = "a1";
	pos[0] = 'a' + m_columna;
	pos[1] = '1' + (N_FILES - 1) - m_fila;
	return pos;
}

void Posicio::fromString(const string& pos) {
	m_fila = (N_FILES - 1) - (pos[1] - '1');
	m_columna = pos[0] - 'a';
}


ifstream& operator>>(ifstream& fitxer, Posicio& posicio)
{
	string pos;
	fitxer >> pos;
	posicio.fromString(pos);
	return fitxer;

}
ofstream& operator<<(ofstream& fitxer, const Posicio& posicio) {
	string pos = posicio.toString();
	fitxer << pos;
	return fitxer;
}


void llegeixFitxa(const string& nomFitxer, char& tipusFitxa, Posicio& posicio) {
	ifstream fitxer(nomFitxer);
	fitxer >> tipusFitxa;
	fitxer >> posicio;
	fitxer.close();
}

void escriuFitxa(const string& nomFitxer, char tipusFitxa, const Posicio& posicio) {
	ofstream fitxer(nomFitxer);
	fitxer << ipusFitxa << ' ';
	fitxer << posicio;
	fitxer.close()
}