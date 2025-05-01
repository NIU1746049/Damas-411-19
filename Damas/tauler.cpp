using namespace std;
#include <iostream>
#include "string"

#include "tauler.h"


void Tauler::actualitzaTaulerEnChars() {
	for (int i = 0;i < N_FILES;i++){
		for (int j = 0;j < N_COLUMNES;j++) {
			if ((m_tauler[i][j].getColorFitxa() == COLOR_UNDEFINED) && (m_tauler[i][j].getTipusFitxa() == TIPUS_EMPTY)) {
				m_taulerEnChars[i][j] = '_';
			}
			else {
				if ((m_tauler[i][j].getColorFitxa() == COLOR_BLANC) && (m_tauler[i][j].getTipusFitxa() == TIPUS_NORMAL)) {
					m_taulerEnChars[i][j] = 'O';
				}
				else {
					if ((m_tauler[i][j].getColorFitxa() == COLOR_NEGRE) && (m_tauler[i][j].getTipusFitxa() == TIPUS_NORMAL)) {
						m_taulerEnChars[i][j] = 'X';
					}
					else {
						if ((m_tauler[i][j].getColorFitxa() == COLOR_BLANC) && (m_tauler[i][j].getTipusFitxa() == TIPUS_DAMA)) {
							m_taulerEnChars[i][j] = 'D';
						}
						else {
							if ((m_tauler[i][j].getColorFitxa() == COLOR_NEGRE) && (m_tauler[i][j].getTipusFitxa() == TIPUS_DAMA)) {
								m_taulerEnChars[i][j] = 'R';
							}
						}
					}
				}
			}
			
			

			
		}
	}
}

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
		incrementVertical = -1;

	}
	else {
		incrementVertical = +1;

	}
	for (int i = -1;i < 2;i++) {
		//if (((posicioActual.getFila() + incrementVertical) < N_FILES) && ((posicioActual.getColumna() + i) < N_COLUMNES) && (i != 0)) {//Parentesis ben posats???????????
		
		if (
			((posicioActual.getFila() + incrementVertical) < N_FILES) &&
			((posicioActual.getFila() + incrementVertical) >= 0) &&
			((posicioActual.getColumna() + i) < N_COLUMNES) &&
			((posicioActual.getColumna() + i) >= 0) &&
			(i != 0)
			) {
			if (m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getColumna() + i].getTipusFitxa() == TIPUS_EMPTY) {
				//movimentsValids[nMovimentsValids] = m_tauler[posicioActual.getFila() + 1][posicioActual.getFila() + i]
				Posicio p(posicioActual.getFila() + incrementVertical, posicioActual.getColumna() + i);
				Posicio posicions[2] = { posicioActual,p };
				
			
				Moviment nouMoviment(NORMAL_NO_MATAR, posicions, 2, 0, {});
				movimentsValids[nMovimentsValids] = nouMoviment;
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
		incrementVertical = -1;

	}
	else {
		incrementVertical = 1;

	}
	for (int i = 0; i < 2;i++) {


		if (((posicioActual.getFila() + incrementVertical) < N_FILES) && ((posicioActual.getColumna() + i) < N_COLUMNES) &&
			((posicioActual.getFila() + 2 * incrementVertical) < N_FILES) && ((posicioActual.getColumna() + 2 * i) < N_COLUMNES) &&
			(i != 0)) {//Parentesis ben posats???????????
			if ((m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getColumna() + i].getTipusFitxa() == TIPUS_NORMAL) &&
				(m_tauler[posicioActual.getFila() + 2 * incrementVertical][posicioActual.getColumna() + 2 * i].getTipusFitxa() == TIPUS_EMPTY) &&
				(m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getColumna() + i].getColorFitxa() != m_tauler[posicioActual.getFila()][posicioActual.getColumna()].getColorFitxa())) {
				//Fotre el moviment aqui

				Posicio tmpP1((posicioActual.getFila() + incrementVertical), (posicioActual.getColumna() + i));
				Posicio tmpP2((posicioActual.getFila() + 2 * incrementVertical), (posicioActual.getColumna() + 2 * i));
				Posicio posicions[3] = { posicioActual,
					tmpP1,
					tmpP2
				};


				Posicio tmpP3[12] = {tmpP1};
				
				
				Moviment nouMoviment(NORMAL_MATAR, posicions, 3, 1, tmpP3);

				movimentsValids[nMovimentsValids] = nouMoviment;
				valid = true;
				nMovimentsValids++;

			}
		}
	}
	return valid;
}





bool Tauler::normalMatarMultiples(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const {
	bool valid = true;
	int incrementVertical;
	
	
	int filaActual = posicioActual.getFila();
	int columnaActual = posicioActual.getColumna();
	
	
	
	if (m_tauler[filaActual][columnaActual].getColorFitxa() == COLOR_BLANC) {
		incrementVertical = -1;

	}
	else {
		incrementVertical = 1;

	}

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
				int iter = 1;
				Posicio posicions[32];
				posicions[0] = posicioActual;
				int nPosicions = 1;
				while (!limitTrobat) {//Iterar per una direccio possible de moviments fins que no sigui possible o be perque ja no estic al taulell o perque mhe trobat una altre fitxa.
					if (
						((posicioActual.getFila() + incFila * iter) < N_FILES) && 
						((posicioActual.getColumna() + incColumna * iter) < N_COLUMNES)&&
						((posicioActual.getFila() + incFila * iter)>0)&&
						((posicioActual.getColumna() + incColumna * iter)>0)
						) {//Evitant Stack Overflow, que no se surti del taulell

						if ((m_tauler[posicioActual.getFila() + incFila * iter][posicioActual.getColumna() + incColumna * iter].getTipusFitxa() == TIPUS_EMPTY)) {//que no hi hagi una fitxa.............
							
							Posicio p((posicioActual.getFila() + incFila * iter), (posicioActual.getColumna() + incColumna * iter));
							//cout << endl<<endl<<"POS::: " << p.toString() << ".."<<endl<<endl;
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
					iter++;
				}
				if (nPosicions > 1) {
					Moviment m(DAMA_NO_MATAR, posicions, nPosicions, 0, {});
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



bool Tauler::damaMatar(Posicio posicioActual, Moviment movimentsValids[20], int& nMovimentsValids)const {
	bool matada = true;
	for (int incColumna = -1;incColumna < 2;incColumna++) {
		for (int incFila = -1;incFila < 2;incFila++)
		{
			if ((incColumna != 0) && (incFila != 0)) {
				matada = false;
				bool limitTrobat = false;
				int i = 1;
				//nou moviment:
				Posicio posicions[32];
				int nPosicions = 0;
				int nMorts = 0;
				Posicio morts[12];


				while (!limitTrobat) {
					if (
						((posicioActual.getFila() + incFila * i) < N_FILES) &&
						((posicioActual.getColumna() + incColumna * i) < N_COLUMNES) &&
						((posicioActual.getFila() + incFila * i) > 0) &&
						((posicioActual.getColumna() + incColumna * i) > 0)
						
						) 
					{

						if (m_tauler[posicioActual.getFila() + incFila * i][posicioActual.getColumna() + incColumna * i].getTipusFitxa() == TIPUS_EMPTY) {
							Posicio tmpPos1(posicioActual.getFila() + incFila * i, posicioActual.getColumna() + incColumna * i);
							posicions[nPosicions] = tmpPos1;
							nPosicions++;
						}
						else {
							Posicio tmpP(posicioActual.getFila() + (incFila * i), posicioActual.getColumna() + (incColumna * i));
							//cout << tmpP.toString()<<" ";
							Posicio tmpP3(posicioActual.getFila() + (incFila * i) + incFila, posicioActual.getColumna() + (incColumna * i) + incColumna);
							//cout << tmpP3.toString() << "; ";
							//cout << endl;
							if (
								((posicioActual.getFila() + (incFila * i) + incFila)<N_FILES)&&
								((posicioActual.getColumna() + (incColumna * i) + incColumna)<N_COLUMNES)&&
								((posicioActual.getFila() + (incFila * i) + incFila)>0)&&
								((posicioActual.getColumna() + (incColumna * i) + incColumna)>0)
								) {
								if (
									
									m_tauler[posicioActual.getFila() + (incFila * i)][posicioActual.getColumna() + (incColumna * i)].getColorFitxa() != m_tauler[posicioActual.getFila()][posicioActual.getColumna()].getColorFitxa() &&//diferent color
									m_tauler[posicioActual.getFila() + (incFila * i) + incFila][posicioActual.getColumna() + (incColumna * i) + incColumna].getTipusFitxa() == TIPUS_EMPTY
									) {
									
									
									Posicio tmpPos1(posicioActual.getFila() + incFila * i, posicioActual.getColumna() + incColumna * i);
									posicions[nPosicions] = tmpPos1;
									nPosicions++;

									Posicio tmpPos2(posicioActual.getFila() + (incFila * i) + incFila, posicioActual.getColumna() + (incColumna * i) + incColumna);
									posicions[nPosicions] = tmpPos2;
									nPosicions++;
									matada = true;

									morts[nMorts] = tmpPos1;
									nMorts++;

								}

							}
							
							limitTrobat = true;
						}
					}
					else {
						limitTrobat = true;
					}
					
					

					i++;
				
				
				}
				if (matada) {
					Moviment mov(DAMA_MATAR, posicions, nPosicions, 1, morts);
					movimentsValids[nMovimentsValids] = mov;
					nMovimentsValids++;
				}
			}
		}
	}
	return matada;
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
	for (int fila = 0; fila < N_FILES;fila++) {
		for (int col = 0;col < N_COLUMNES;col++) {
			esborraMoviments(m_tauler[fila][col]);
			Moviment mv[100] = {};
			int nMv = 0;

			if (m_tauler[fila][col].getTipusFitxa() == TIPUS_NORMAL)
			{
				//Posicio pos = m_tauler[m_filaFitxaSeleccionada][m_colFitxaSeleccionada].getPosicio();
				Posicio pos(fila, col);

				normalMoure(pos, mv, nMv);

				if (normalMatar(pos, mv, nMv)) {
					normalMatarMultiples(pos, mv, nMv);
				}

			}
			else {
				if (m_tauler[fila][col].getTipusFitxa() == TIPUS_DAMA)
				{
					Posicio pos(fila,col);

					cout << "a";
					damaMoure(pos, mv, nMv);

					if (damaMatar(pos, mv, nMv)) {
						damaMatarMultiples(pos, mv, nMv);
					}
				}
			}
			for (int k = 0; k < nMv; k++)
			{

				m_tauler[fila][col].setMovimentPos(k, mv[k]);
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
		
		bool valid = true;
		for (int k = 0; k < nPosicions;k++) {

			if (posicionsPossibles[k] == moviment.getPosicioPos(moviment.getNPosicions() - 1)) {//No vull que hi hagin posicions repetides
				valid = false;
			}
		}
		if (valid) {
			
			posicionsPossibles[nPosicions] = moviment.getPosicioPos(moviment.getNPosicions() - 1);
			nPosicions++;
		}
		
	}
	//Debug:
	Posicio oPos(origen.getFila(), origen.getColumna());
	if (origen == oPos) {
		cout << "posicions possibles: " << endl;
		for (int i = 0;i < nPosicions;i++) {
			cout << " " << posicionsPossibles[i].toString() << " ;";
		}
		cout << endl << endl;
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

	string fitxaRaw;
	bool valid = true;
	cout << endl<<"Introdueix posicio: ";
	cin >> fitxaRaw;
	cout << endl;
	Posicio p;
	p.fromString(fitxaRaw);
	int filaActual = p.getFila();
	int colActual = p.getColumna();
	
	if ((filaActual > N_FILES) || (colActual > N_COLUMNES) || (filaActual < 0) || (colActual < 0 )) {
		cout << "Overflow";
		valid = false;
	}
	else {
		if (m_tornBlanques) {
			if (m_tauler[filaActual][colActual].getColorFitxa() == COLOR_BLANC) {
				valid = true;
			}
			else {
				valid = false;
			}
		}
		else {
			if (m_tauler[filaActual][colActual].getColorFitxa() == COLOR_NEGRE) {
				valid = true;
			}
			else {
				valid = false;
			}
		}
	}

	if (valid) {
		m_colFitxaSeleccionada = colActual;
		m_filaFitxaSeleccionada = filaActual;
	}
	return valid;


}


bool Tauler::seleccionaDesti(Posicio &desti) {
	cout << "---------------------------------------------" << endl;
	cout << "Selecció posició destí" << endl;
	cout << "---------------------------------------------" << endl;
	string fitxaRaw;
	bool valid = false;
	cout << endl << "Introdueix posicio: ";
	cin >> fitxaRaw;
	cout << endl;
	Posicio p;
	p.fromString(fitxaRaw);
	int filaActual = p.getFila();
	int colActual = p.getColumna();
	
	


	if ((filaActual > N_FILES) || (colActual > N_COLUMNES) || (filaActual < 0) || (colActual < 0)) {
		cout << "Overflow";
		valid=false;
		
	}
	else {
		Posicio posDesti(filaActual, colActual);
		Posicio posicionsPossibles[10];
		int nPos = 0;
		getPosicionsPossibles(Posicio(m_filaFitxaSeleccionada, m_colFitxaSeleccionada), nPos, posicionsPossibles);
		for (int i = 0;i < nPos;i++) {
			if (posDesti == posicionsPossibles[i]) {
				desti = posDesti;
				valid = true;//Perque llavors esta dins de les posicions possibles
			}
		}
	}

	return valid;
}




bool Tauler::mouFitxa(const Posicio& desti)//Capçalera canviada
{

	m_tauler[desti.getFila()][desti.getColumna()] = m_tauler[m_filaFitxaSeleccionada][m_colFitxaSeleccionada];//ho copio tot
	m_tauler[desti.getFila()][desti.getColumna()].setViva(true);
	//pero no vull que es vagin canviant les posicions aixi que:
	m_tauler[desti.getFila()][desti.getColumna()].setPosicio(desti);
	

	m_tauler[m_filaFitxaSeleccionada][m_colFitxaSeleccionada].setColorITipusFitxa('_');//Fitxa buida

	m_filaFitxaSeleccionada = desti.getFila();//Mes facil. Aixi despres puc bufar i tota la pesca.
	m_colFitxaSeleccionada = desti.getColumna();

	//Ara trobar el moviment que s'ha fet dins de la llista de moviments valids de la fitxa. 
	bool trobat = false;
	int i = 0;
	Moviment movimentFet;
	

	while ((i < m_tauler[desti.getFila()][desti.getColumna()].getNMoviments()) && (!trobat)) {		
		if (m_tauler[desti.getFila()][desti.getColumna()].getMovimentPos(i).getPosicioPos(m_tauler[desti.getFila()][desti.getColumna()].getMovimentPos(i).getNPosicions()-1) == desti) {
			movimentFet = m_tauler[desti.getFila()][desti.getColumna()].getMovimentPos(i);
			trobat = true;
			
		}
		i++;
	}
	if (trobat) {
		for (int i = 0; i < movimentFet.getNMorts();i++) {
			m_tauler[movimentFet.getMortsPos(i).getFila()][movimentFet.getMortsPos(i).getColumna()].setViva(false);//Matar totes les fitxes que el moviment mata.
		}
		if (m_tornBlanques) {
			m_nNegres -= movimentFet.getNMorts();
		}
		else {
			m_nBlanques -= movimentFet.getNMorts();
		}
	}
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

//Crec que he fet que funcioni perque com estava abans et parava el joc a la meitat perquesi.
bool Tauler::comptaNumeroMovimentsPossibles(const ColorFitxa color) const
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
	
	if (nMoviments > 0){
		return true;
	}
	return false;
}

bool Tauler::gameOver()
{
	if (m_nBlanques == 0 || (m_tornBlanques == true && !comptaNumeroMovimentsPossibles(COLOR_BLANC)))
	{
		cout << "Guanyen les negres" << endl;
		return true;
	}
	else if (m_nNegres == 0 || (m_tornBlanques == false && !comptaNumeroMovimentsPossibles(COLOR_NEGRE)))
	{
		cout << "Guanyen les blanques" << endl;
		return true;
	}

	return false;
}