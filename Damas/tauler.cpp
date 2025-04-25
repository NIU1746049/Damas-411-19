using namespace std;
#include <iostream>
#include "string"

#include "tauler.h"

void Tauler::inicialitza(const string& nomFitxer)
{
	if (nomFitxer != "null")
	{
		llegeixTauler(nomFitxer, m_taulerEnChars);
	}
	else
	{
		for (int fila = 0; fila < N_FILES; fila++)
		{
			for (int col = 0; col < N_COLUMNES; col++)
			{
				if (fila <= 3) // Si estan arriba
				{
					if ((col + fila) % 2 == 1) // Es negra
					{
						m_taulerEnChars[fila][col] = 'X';
					}
					else
					{
						m_taulerEnChars[fila][col] = '_';
					}
				}
				else if (fila >= 4) // Si estan abajo
				{
					if ((col + fila) % 2 == 1) // Es blanca
					{
						m_taulerEnChars[fila][col] = 'O';
					}
					else
					{
						m_taulerEnChars[fila][col] = '_';
					}
				}
			}
		}
	}

	m_nBlanques = 0;
	m_nNegres = 0;
	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			m_tauler[fila][col].setColorITipusFitxa(m_taulerEnChars[fila][col]);
			//Cuenta cuantas fichas de cada color hay
			if (m_tauler[fila][col].getColorFitxa() == COLOR_BLANC)
			{
				m_nBlanques++;
			}
			else if (m_tauler[fila][col].getColorFitxa() == COLOR_NEGRE)
			{
				m_nNegres++;
			}
		}
	}
}

//Normal
bool Tauler::normalMoure(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const
{
	bool valid = false;
	int incrementVertical;
	if (m_tauler[posicioActual.getFila()][posicioActual.getColumna()].getColorFitxa() == COLOR_BLANC) {
		incrementVertical = 1;

	}
	else {
		incrementVertical = -1;

	}
	for (int i = -1;i < 2;i++) {
		if (((posicioActual.getFila() + incrementVertical) < N_FILES) && ((posicioActual.getColumna() + i) < N_COLUMNES) && (i != 0)) {//Parentesis ben posats???????????
			if ((m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getFila() + i].getTipusFitxa() == TIPUS_EMPTY)) {
				//movimentsValids[nMovimentsValids] = m_tauler[posicioActual.getFila() + 1][posicioActual.getFila() + i]

				Posicio posicions[2] = { posicioActual,m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getFila() + i].getPosicio() };
				Moviment nouMoviment(NORMAL_NO_MATAR, posicions, 2, 0);
				valid = true;
				nMovimentsValids++;
			}
		}
	}
	return valid;

}


bool Tauler::normalMatar(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const {

	bool valid = false;
	int incrementVertical;
	if (m_tauler[posicioActual.getFila()][posicioActual.getColumna()].getColorFitxa() == COLOR_BLANC) {
		incrementVertical = 1;

	}
	else {
		incrementVertical = -1;

	}
	for (int i = 0; i < 2;i++) {


		if (((posicioActual.getFila() + incrementVertical) < N_FILES) && ((posicioActual.getColumna() + i) < N_COLUMNES) &&
			((posicioActual.getFila() + 2 * incrementVertical) < N_FILES) && ((posicioActual.getColumna() + 2 * i) < N_COLUMNES) &&
			(i != 0)) {//Parentesis ben posats???????????

			if ((m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getFila() + i].getTipusFitxa() == TIPUS_NORMAL) &&
				(m_tauler[posicioActual.getFila() + 2 * incrementVertical][posicioActual.getFila() + 2 * i].getTipusFitxa() == TIPUS_EMPTY) &&
				(m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getFila() + i].getColorFitxa() != m_tauler[posicioActual.getFila()][posicioActual.getFila()].getColorFitxa())) {
				//Fotre el moviment aqui
				Posicio posicions[3] = { posicioActual,
					m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getFila() + i].getPosicio(),
					m_tauler[posicioActual.getFila() + 2 * incrementVertical][posicioActual.getFila() + 2 * i].getPosicio()
				};
				Moviment nouMoviment(NORMAL_MATAR, posicions, 3, 1);
				valid = true;
				nMovimentsValids++;

			}
		}
	}
	return valid;
}

bool Tauler::normalMatarMultiples(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const {
	

	return true;
}



//dama
bool Tauler::damaMoure(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const
{
	int nMovimentsValidsInicial = nMovimentsValids;
	for (int incColumna = -1;incColumna < 2;incColumna++) {
		for (int incFila = -1;incFila < 2;incFila++)
		{
			if ((incColumna != 0) && (incFila != 0))
			{
				bool limitTrobat = false;//Ja sigui taulell o casella contraria
				int escalar = 1;
				Posicio posicions[32];
				posicions[0] = posicioActual;
				int nPosicions = 1;
				while (!limitTrobat) {//Iterar per una direccio possible de moviments fins que no sigui possible o be perque ja no estic al taulell o perque mhe trobat una altre fitxa.
					if (((posicioActual.getFila() + incFila * escalar) < N_FILES) && ((posicioActual.getColumna() + incColumna * escalar) < N_COLUMNES)) {//Evitant Stack Overflow, que no se surti del taulell
						if ((m_tauler[posicioActual.getFila() + incFila * escalar][posicioActual.getFila() + incColumna * escalar].getTipusFitxa() == TIPUS_EMPTY)) {//que no hi hagi una fitxa.............

							Posicio p((posicioActual.getFila() + incFila * escalar), (posicioActual.getColumna() + incColumna * escalar));
							posicions[nPosicions] = p;
							nPosicions++;
						}
						else {
							limitTrobat = true;
						}
					}
					else {
						limitTrobat = true;
					}
				}
				if (nPosicions > 1) {
					Moviment m(DAMA_NO_MATAR, posicions, nPosicions, 0);
					movimentsValids[nMovimentsValids] = m;
					nMovimentsValids++;
				}
			}
		}
	}
	int incrementMovimentsValids = nMovimentsValids - nMovimentsValidsInicial;
	if (incrementMovimentsValids > 0) {
		return true;
	}
	else {
		return false;
	}

}

bool Tauler::damaMatar(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const
{
	for (int incColumna = -1;incColumna < 2;incColumna++) {
		for (int incFila = -1;incFila < 2;incFila++)
		{
			if ((incColumna != 0) && (incFila != 0))
			{
				bool matada = false;
				bool limitTrobat = false;//Ja sigui taulell o casella contraria
				int escalar = 1;
				Posicio posicions[32];
				posicions[0] = posicioActual;
				int nPosicions = 1;
				while (!limitTrobat) {//Iterar per una direccio possible de moviments fins que no sigui possible o be perque ja no estic al taulell o perque mhe trobat una altre fitxa.
					if (((posicioActual.getFila() + incFila * escalar) < N_FILES) && ((posicioActual.getColumna() + incColumna * escalar) < N_COLUMNES)) {//Evitant Stack Overflow, que no se surti del taulell
						if ((m_tauler[posicioActual.getFila() + incFila * escalar][posicioActual.getFila() + incColumna * escalar].getTipusFitxa() == TIPUS_EMPTY)) {

							Posicio p((posicioActual.getFila() + incFila * escalar), (posicioActual.getColumna() + incColumna * escalar));
							posicions[nPosicions] = p;
							nPosicions++;



						}
						else {
							if ((m_tauler[posicioActual.getFila() + incFila * escalar][posicioActual.getFila() + incColumna * escalar].getColorFitxa() !=
								m_tauler[posicioActual.getFila()][posicioActual.getFila()].getColorFitxa()) &&
								(m_tauler[posicioActual.getFila() + incFila * escalar + incFila][posicioActual.getFila() + incColumna * escalar + incColumna].getTipusFitxa() == TIPUS_EMPTY)) {

								Posicio p((posicioActual.getFila() + incFila * escalar), (posicioActual.getColumna() + incColumna * escalar));
								posicions[nPosicions] = p;
								nPosicions++;
								Posicio p2((posicioActual.getFila() + incFila * escalar + incFila), (posicioActual.getColumna() + incColumna * escalar + incColumna));
								posicions[nPosicions] = p2;
								nPosicions++;
								matada = true;

							}
							limitTrobat = true;
						}



					}
					else {
						limitTrobat = true;
					}
					escalar++;
				}
				if (matada) {
					Moviment m(DAMA_MATAR, posicions, nPosicions, 1);
					movimentsValids[nMovimentsValids] = m;
					nMovimentsValids++;
				}
			}
		}
	}

	return false; //Return false para que no de error
}

bool Tauler::damaMatarMultiples(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const {
	return true;
}



// Esto no tendria que estar en fitxa???????????????????????????????????????????????????????????????????????????????????
void esborraMoviments(Fitxa fitxa) {
	for (int i = 0;i < fitxa.getNMoviments();i++) {
		Moviment m;
		fitxa.setMovimentPos(i, m);
	}
}


void Tauler::actualitzaMovimentsValids()
{
	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			esborraMoviments(m_tauler[fila][col]);


			Moviment mv[100] = {};
			int nMv = 0;



			if (m_tauler[fila][col].getTipusFitxa() == TIPUS_NORMAL)
			{
				Posicio pos = m_tauler[fila][col].getPosicio();


				normalMoure(pos, mv, nMv);

				if (normalMatar(pos, mv, nMv)) {
					normalMatarMultiples(pos, mv, nMv);
				}

			}
			else {
				if (m_tauler[fila][col].getTipusFitxa() == TIPUS_DAMA)
				{
					Posicio pos = m_tauler[fila][col].getPosicio();


					damaMoure(pos, mv, nMv);

					if (damaMatar(pos, mv, nMv)) {
						damaMatarMultiples(pos, mv, nMv);
					}
				}
			}
			for (int j = 0; j < nMv; j++)
			{
				m_tauler[fila][col].setMovimentPos(j, mv[j]);//Li fot moviments a la fitxa visitada en el bucle for
				m_tauler[fila][col].setNMovimentsValids(nMv);
			}

		}
	}
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
	//Recuerda igualar m_nMoviments a el numero de movimientos
	nPosicions = 0;
	
	for (int i = 0;i < m_tauler[origen.getFila()][origen.getColumna()].getNMoviments();i++) {
		Moviment moviment=m_tauler[origen.getFila()][origen.getColumna()].getMovimentPos(i);

		for (int j = 0; j < moviment.getNPosicions(); j++) {
			if ((moviment.getPosicioPos(j) == origen) == false) {//Que no es foti a on ja està
				bool valid = true;
				for (int k = 0; k < nPosicions;k++) {
					
					if (posicionsPossibles[k] == moviment.getPosicioPos(j)) {//No vull que hi hagin posicions repetides
						valid = false;
					}
				}
				if (valid) {
					posicionsPossibles[nPosicions] = moviment.getPosicioPos(j);
					nPosicions++;
				}
				

			}
		}
	}
}

bool Tauler::bufar() {
	int maxIndex=-1;
	int maxMorts=-1;
	for (int i = 0;i < m_tauler[m_filaFitxaSeleccionada][m_colFitxaSeleccionada].getNMoviments();i++) {
		Moviment moviment = m_tauler[m_filaFitxaSeleccionada][m_colFitxaSeleccionada].getMovimentPos(i);
		if (moviment.getTipus() != NORMAL_NO_MATAR) {
			if (moviment.getNMorts() > maxMorts) {
				maxIndex = i;
				maxMorts = moviment.getNMorts();
			}
		}
	}
	if ((movimentFet.getNMorts() < m_tauler[m_filaFitxaSeleccionada][m_colFitxaSeleccionada].getMovimentPos(maxIndex).getNMorts())) {
		m_tauler[m_filaFitxaSeleccionada][m_colFitxaSeleccionada].setViva(false);
		return true;
	}
	else {
		return false;
	}
	
}
bool Tauler::seleccionaFitxa() {
	cout << "---------------------------------------------" << endl;
	cout << "Selecció fitxa a moure:" << endl;
	cout << "---------------------------------------------" << endl;

	int fila;
	int columna;
	bool valid = true;
	cout << "Introdueix fila: ";
	cin >> fila;
	cout << endl << "Introdueix columna: ";
	cin >> columna;

	if ((fila > N_FILES) || (columna > N_COLUMNES)) {
		valid = false;
	}
	else {
		if (m_tornBlanques) {
			if (m_tauler[fila][columna].getColorFitxa() == COLOR_BLANC) {
				valid = true;
			}
			else {
				valid = false;
			}
		}
		else {
			if (m_tauler[fila][columna].getColorFitxa() == COLOR_NEGRE) {
				valid = true;
			}
			else {
				valid = false;
			}
		}
	}

	if (valid) {
		m_colFitxaSeleccionada = columna;
		m_filaFitxaSeleccionada = fila;
	}
	return valid;


}


bool Tauler::seleccionaDesti(Posicio &desti) {
	int fila;
	int columna;
	bool valid = false;
	cout << "---------------------------------------------" << endl;
	cout << "Selecció posició destí" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "Introdueix fila: ";
	cin >> fila;
	cout << endl << "Introdueix columna: ";
	cin >> columna;


	if ((fila > N_FILES) || (columna > N_COLUMNES)) {
		return false;
	}
	else {
		Posicio posDesti(fila, columna);
		Posicio posicionsPossibles[10];
		int nPos = 0;
		getPosicionsPossibles(Posicio(m_filaFitxaSeleccionada, m_colFitxaSeleccionada), nPos, posicionsPossibles);
		for (int i = 0;i < nPos;i++) {
			if (posDesti == posicionsPossibles[i]) {
				desti = posDesti;
				valid = true;//Perque llavors esta dins de les posicions possibles
			}
		}
		//string posFormat = posDesti.toString();
	}

	return valid;
	

}

/*
void Tauler::transportar(const Posicio& origen, const Posicio& desti) {//El fet concret de moure d'un lloc a l'altre


	Fitxa fitxaAuxiliar = m_tauler[desti.getFila()][desti.getColumna()];//podriem fer std::swap i ens estalviavem aixo. Pero ns si esta permes per tema deteccio de  IA com als seminaris de MD.

	m_tauler[desti.getFila()][desti.getColumna()] = m_tauler[origen.getFila()][origen.getColumna()];
	m_tauler[origen.getFila()][origen.getColumna()] = fitxaAuxiliar;

	m_tauler[desti.getFila()][desti.getColumna()].setPosicio(desti);
	m_tauler[origen.getFila()][origen.getColumna()].setPosicio(origen);


}
*/



bool Tauler::mouFitxa(const Posicio& desti)//Capçalera canviada
{

	m_tauler[desti.getFila()][desti.getColumna()] = m_tauler[m_filaFitxaSeleccionada][m_colFitxaSeleccionada];//ho copio tot
	//pero no vull que es vagin canviant les posicions aixi que:
	m_tauler[desti.getFila()][desti.getColumna()].setPosicio(desti);


	m_tauler[m_filaFitxaSeleccionada][m_colFitxaSeleccionada].setColorITipusFitxa('_');//Fitxa buida

	m_filaFitxaSeleccionada = desti.getFila();//Mes facil. Aixi despres puc bufar i tota la pesca.
	m_colFitxaSeleccionada = desti.getColumna();
	return false;
}



string Tauler::toString() const
{
	string taula = "";
	for (int fila = 0; fila < N_FILES; fila++)
	{
		taula = taula + to_string(8 - fila) + ":";
		for (int col = 0; col < N_COLUMNES; col++)
		{
			taula = taula + m_taulerEnChars[fila][col] + " ";
		}
		taula = taula + "\n";
	}

	taula = taula + "  ";
	for (int i = 0; i < N_FILES; i++)
	{
		taula = taula + (char)('A' + i) + " ";
	}

	return taula;
}



void Tauler::llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]) const
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			tauler[i][j] = '_';
		}
	}

	ifstream fitxer;
	fitxer.open(nomFitxer);

	Posicio posicions[32];
	char fitxes[32];

	if (fitxer.is_open())
	{
		int i = 0;
		while (fitxer.eof() == false)
		{
			fitxer >> fitxes[i];
			fitxer >> posicions[i];

			tauler[posicions[i].getFila()][posicions[i].getColumna()] = fitxes[i];

			i++;
		}
	}
	fitxer.close();
}



void Tauler::convertirADama()
{
	//Damas Blancas
	for (int col = 0; col < N_COLUMNES; col++)
	{
		if (m_tauler[0][col].getColorFitxa() == COLOR_BLANC)
		{
			m_tauler[0][col].setTipusFitxa(TIPUS_DAMA);
		}
	}

	//Damas Negras
	for (int col = 0; col < N_COLUMNES; col++)
	{
		if (m_tauler[7][col].getColorFitxa() == COLOR_NEGRE)
		{
			m_tauler[7][col].setTipusFitxa(TIPUS_DAMA);
		}
	}
}



void Tauler::eliminarFitxesMortes() // Asignarlas como vivas despues de eliminarlas
{
	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			if (m_tauler[fila][col].getViva() == false)
			{
				m_tauler[fila][col].setColorFitxa(COLOR_UNDEFINED);
				m_tauler[fila][col].setTipusFitxa(TIPUS_EMPTY);
				//
				m_tauler[fila][col].setViva(true);
			}
		}
	}
}

int Tauler::comptaNumeroMovimentsPossibles(const ColorFitxa color) const
{
	int nMoviments = 0;
	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			if (m_tauler[fila][col].getColorFitxa() == color)
			{
				nMoviments = nMoviments + m_tauler[fila][col].getNMoviments();
			}
		}
	}

	return nMoviments;
}

bool Tauler::gameOver()
{
	if (m_nBlanques == 0 || (m_tornBlanques == true && comptaNumeroMovimentsPossibles(COLOR_BLANC)))
	{
		cout << "Guanyen les negres" << endl;
		return true;
	}
	else if (m_nNegres == 0 || (m_tornBlanques == false && comptaNumeroMovimentsPossibles(COLOR_NEGRE)))
	{
		cout << "Guanyen les blanques" << endl;
		return true;
	}

	return false;
}
