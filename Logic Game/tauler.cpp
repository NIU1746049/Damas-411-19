using namespace std;
#include <iostream>
#include "string"

#include "tauler.hpp"


void Tauler::actualitzaTaulerEnChars()
{
	for (int i = 0;i < N_FILES;i++)
	{
		for (int j = 0;j < N_COLUMNES;j++)
		{
			if (m_tauler[i][j] == nullptr)
			{
				m_taulerEnChars[i][j] = '_';
			}
			else {
				if ((m_tauler[i][j]->getColorFitxa() == COLOR_BLANC) && (m_tauler[i][j]->getTipusFitxa() == TIPUS_NORMAL))
				{
					m_taulerEnChars[i][j] = 'O';
				}
				else {
					if ((m_tauler[i][j]->getColorFitxa() == COLOR_NEGRE) && (m_tauler[i][j]->getTipusFitxa() == TIPUS_NORMAL))
					{
						m_taulerEnChars[i][j] = 'X';
					}
					else {
						if ((m_tauler[i][j]->getColorFitxa() == COLOR_BLANC) && (m_tauler[i][j]->getTipusFitxa() == TIPUS_DAMA))
						{
							m_taulerEnChars[i][j] = 'D';
						}
						else {
							if ((m_tauler[i][j]->getColorFitxa() == COLOR_NEGRE) && (m_tauler[i][j]->getTipusFitxa() == TIPUS_DAMA))
							{
								m_taulerEnChars[i][j] = 'R';
							}
							else {
								m_taulerEnChars[i][j] = '?';//Per debugar
							}
						}
					}
				}
			}




		}
	}
}

void Tauler::inicialitza(const string& nomFitxer)//mod
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
					if ((col + fila) % 2 == 1 && fila!=3) // Es negra
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
					if ((col + fila) % 2 == 1 && fila != 4) // Es blanca
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
	Posicio posAux;
	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			if (m_taulerEnChars[fila][col] != '_') {
				m_tauler[fila][col] = new Fitxa;
				m_tauler[fila][col]->setColorITipusFitxa(m_taulerEnChars[fila][col]);
				posAux.setFila(fila);
				posAux.setColumna(col);
				m_tauler[fila][col]->setPosicio(posAux);
				if (m_tauler[fila][col]->getColorFitxa() == COLOR_BLANC)
				{
					m_nBlanques++;
				}
				else if (m_tauler[fila][col]->getColorFitxa() == COLOR_NEGRE)
				{
					m_nNegres++;
				}
			}
			else {//No caldria pero per si de cas
				m_tauler[fila][col] = nullptr;
				//
				Posicio bigD(fila, col);
				cout << "Posicio " << bigD.toString() << " nullptr" << endl;
				//
			}

		}
	}
}




bool Tauler::normalMoure(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const
{

	bool valid = false;
	int incrementVertical;
	if (m_tauler[fitxaQueEsMou.getFila()][fitxaQueEsMou.getColumna()]->getColorFitxa() == COLOR_BLANC)
	{
		incrementVertical = -1;

	}
	else
	{
		incrementVertical = +1;

	}
	for (int i = -1;i < 2;i++)
	{

		if (
			((posicioActual.getFila() + incrementVertical) < N_FILES) &&
			((posicioActual.getFila() + incrementVertical) >= 0) &&
			((posicioActual.getColumna() + i) < N_COLUMNES) &&
			((posicioActual.getColumna() + i) >= 0) &&
			(i != 0)
			)
		{
			Posicio bigD(posicioActual.getFila() + incrementVertical, posicioActual.getColumna() + i);
			cout << endl << "desde: " << posicioActual.toString() << " revisant si puc NormalMoure a " << bigD.toString() << endl;
			if (m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getColumna() + i] == nullptr)
			{
				cout << endl << "SI ES POT" << endl;
				Posicio pospos(posicioActual.getFila() + incrementVertical, posicioActual.getColumna() + i);

				Posicio p(posicioActual.getFila() + incrementVertical, posicioActual.getColumna() + i);

				vector <Posicio> posicions;
				posicions.push_back(posicioActual);
				posicions.push_back(p);
				vector <Posicio> morts;

				Moviment nouMoviment(NORMAL_NO_MATAR, posicions, morts);
				movimentsValids.push_back(nouMoviment);
				valid = true;
				
			}
			else {
				cout << endl << "NO ES POT PERQUE TENIM: "<< m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getColumna() + i]->getTipusFitxa();
				
				
			}



		}


	}

	return valid;

}


bool Tauler::normalMatar(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const // diria que aqui esta el problema
{
	bool valid = false;
	int incrementVertical;
	if (m_tauler[fitxaQueEsMou.getFila()][fitxaQueEsMou.getColumna()]->getColorFitxa() == COLOR_BLANC)
	{
		incrementVertical = -1;

	}
	else
	{
		incrementVertical = 1;

	}

	for (int i = -1; i < 2;i++)
	{
		if (((posicioActual.getFila() + incrementVertical) < N_FILES) && ((posicioActual.getColumna() + i) < N_COLUMNES) && ((posicioActual.getFila() + 2 * incrementVertical) < N_FILES) && ((posicioActual.getColumna() + 2 * i) < N_COLUMNES) && ((posicioActual.getFila() + incrementVertical) >= 0) && ((posicioActual.getColumna() + i) >= 0) && ((posicioActual.getFila() + 2 * incrementVertical) >= 0) && ((posicioActual.getColumna() + 2 * i) >= 0) && (i != 0))
		{
			if ((m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getColumna() + i] != nullptr) &&
				(m_tauler[posicioActual.getFila() + 2 * incrementVertical][posicioActual.getColumna() + 2 * i] == nullptr) &&
				(m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getColumna() + i]->getColorFitxa() != m_tauler[fitxaQueEsMou.getFila()][fitxaQueEsMou.getColumna()]->getColorFitxa()))
			{
				//Fotre el moviment aqui
				Posicio tmpP1((posicioActual.getFila() + incrementVertical), (posicioActual.getColumna() + i));
				Posicio tmpP2((posicioActual.getFila() + 2 * incrementVertical), (posicioActual.getColumna() + 2 * i));

				vector <Posicio> posicions;
				posicions.push_back(posicioActual);
				posicions.push_back(tmpP2);

				vector <Posicio> tmpP3;
				tmpP3.push_back(tmpP1);

				

				Moviment nouMoviment(NORMAL_MATAR, posicions, tmpP3);

				movimentsValids.push_back(nouMoviment);
				valid = true;
			}
		}
	}
	return valid;
}



bool Tauler::normalMatarMultiples(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const//AQUI ESTA EL FALLO!!!!
{
	vector <Moviment> tmpMoviments;
	brancaNormal(posicioActual, tmpMoviments, fitxaQueEsMou);

	Moviment tmpMoviment;

	for (int i = 0; i < tmpMoviments.size();i++) {
		if (i == 0) {
			tmpMoviment.setTipus(NORMAL_MATAR);
		}
		else {
			tmpMoviment.setTipus(NORMAL_MATAR_MULTIPLES);
		}
		tmpMoviment.afegirPosicio(posicioActual);
		tmpMoviment.afegirPosicio(tmpMoviments[i].getPosicioPos(tmpMoviments[i].getNPosicions() - 1)); //afegeixo lultima pos
		tmpMoviment.afegirMorts(tmpMoviments[i].getMortsPos(0));//sempre estara en 0

		movimentsValids.push_back(tmpMoviment);

	}




	
	return (tmpMoviments.size() > 1);
}


void Tauler::brancaDama(Posicio posicioOrigen, vector <Moviment>& movimentsDefinitius, Posicio fitxaQueEsMou)const 
{
	int movimentsDefinitiusInicials = movimentsDefinitius.size();

	




	if (damaMatar(posicioOrigen, movimentsDefinitius, fitxaQueEsMou)) 
	{
		for (int i = movimentsDefinitiusInicials; i < movimentsDefinitius.size();i++) {
			brancaDama(movimentsDefinitius[i].getPosicioPos(movimentsDefinitius[i].getNPosicions() - 1), movimentsDefinitius, fitxaQueEsMou);
		}
	}
	

}

void Tauler::brancaNormal(Posicio posicioOrigen, vector <Moviment>& movimentsDefinitius, Posicio fitxaQueEsMou)const 
{
	int movimentsDefinitiusInicials = movimentsDefinitius.size();
	if (normalMatar(posicioOrigen, movimentsDefinitius, fitxaQueEsMou)) {
		for (int i = movimentsDefinitiusInicials; i < movimentsDefinitius.size();i++) {
			brancaNormal(movimentsDefinitius[i].getPosicioPos(movimentsDefinitius[i].getNPosicions() - 1),movimentsDefinitius,fitxaQueEsMou);
		}
	}
	
}



bool Tauler::damaMatarMultiples(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const
{

	vector <Moviment> tmpMoviments;
	

	
	int nMovimentsValidsInicial = movimentsValids.size();
	brancaDama(posicioActual, tmpMoviments, fitxaQueEsMou);
	
	Moviment tmpMoviment;

	for (int i = 0; i < tmpMoviments.size();i++) {
		if (i == 0) {
			tmpMoviment.setTipus(NORMAL_MATAR);
		}
		else {
			tmpMoviment.setTipus(NORMAL_MATAR_MULTIPLES);
		}

		tmpMoviment.afegirPosicio(posicioActual);
		tmpMoviment.afegirPosicio(tmpMoviments[i].getPosicioPos(tmpMoviments[i].getNPosicions() - 1)); //afegeixo lultima pos
		tmpMoviment.afegirMorts(tmpMoviments[i].getMortsPos(0));//sempre estara en 0 perque nomes fem una captura per moviment (perque tots en la llista tmpMoviment son damaMatar i no multiples)
		
		movimentsValids.push_back(tmpMoviment);
		
	}

	return (tmpMoviments.size()> 1);


}





//dama
bool Tauler::damaMoure(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const
{
	int nMovimentsValidsInicial = movimentsValids.size();
	for (int incColumna = -1;incColumna < 2;incColumna++)
	{
		for (int incFila = -1;incFila < 2;incFila++)
		{
			if ((incColumna != 0) && (incFila != 0))
			{
				bool possible = false;
				bool limitTrobat = false;//Ja sigui taulell o casella contraria
				int iter = 1;

				while (!limitTrobat)
				{//Iterar per una direccio possible de moviments fins que no sigui possible o be perque ja no estic al taulell o perque mhe trobat una altre fitxa.
					if (
						((posicioActual.getFila() + incFila * iter) < N_FILES) &&
						((posicioActual.getColumna() + incColumna * iter) < N_COLUMNES) &&
						((posicioActual.getFila() + incFila * iter) >= 0) &&
						((posicioActual.getColumna() + incColumna * iter) >= 0)




						) {//Evitant Stack Overflow, que no se surti del taulell


						if ((m_tauler[posicioActual.getFila() + incFila * iter][posicioActual.getColumna() + incColumna * iter] == nullptr))
						{
							vector <Posicio> posicions;
							posicions.push_back(posicioActual);
							
							Posicio p((posicioActual.getFila() + (incFila * iter)), (posicioActual.getColumna() + (incColumna * iter)));
							posicions.push_back(p);
							vector <Posicio> morts;
							Moviment m(DAMA_NO_MATAR, posicions, morts);
							movimentsValids.push_back(m);

						}
						else
						{

							Posicio p((posicioActual.getFila() + (incFila * iter) - incFila), (posicioActual.getColumna() + (incColumna * iter) - incColumna));

							if ((p == posicioActual) == false)
							{
								vector <Posicio> posicions;
								posicions.push_back(posicioActual);
								posicions.push_back(p);
								vector <Posicio> morts;
								Moviment m(DAMA_NO_MATAR, posicions, morts);//ASAPGOTOa
								movimentsValids.push_back(m);
								

								limitTrobat = true;
							}
							else
							{
								limitTrobat = true;
							}

						}
					}
					else {
						limitTrobat = true;
					}
					iter++;
				}

			}
		}
	}
	int incrementMovimentsValids = movimentsValids.size() - nMovimentsValidsInicial;
	if (incrementMovimentsValids > 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}




//DamaMatar

bool Tauler::damaMatar(Posicio posicioActual, vector <Moviment> &movimentsValids, Posicio fitxaQueEsMou)const
{
	bool matada = false;
	for (int incColumna = -1;incColumna < 2;incColumna++)
	{
		for (int incFila = -1;incFila < 2;incFila++)
		{
			if ((incColumna != 0) && (incFila != 0))
			{
				bool limitTrobat = false;
				int i = 1;

				
				vector <Posicio> posicions;
				vector <Posicio> morts;

				while (!limitTrobat) {
					if (
						((posicioActual.getFila() + incFila * i) < N_FILES) &&
						((posicioActual.getColumna() + incColumna * i) < N_COLUMNES) &&
						((posicioActual.getFila() + incFila * i) >= 0) &&
						((posicioActual.getColumna() + incColumna * i) >= 0)

						)//evitar Stack Overflow
					{
						if (m_tauler[posicioActual.getFila() + incFila * i][posicioActual.getColumna() + incColumna * i] != nullptr)//si la següent NO esta buida
						{
							
							if (
								((posicioActual.getFila() + (incFila * i) + incFila) < N_FILES) &&
								((posicioActual.getColumna() + (incColumna * i) + incColumna) < N_COLUMNES) &&
								((posicioActual.getFila() + (incFila * i) + incFila) >= 0) &&
								((posicioActual.getColumna() + (incColumna * i) + incColumna) >= 0)
								) {
								if ((m_tauler[posicioActual.getFila() + (incFila * i)][posicioActual.getColumna() + (incColumna * i)] != nullptr) && (m_tauler[fitxaQueEsMou.getFila()][fitxaQueEsMou.getColumna()] != nullptr)) {
									if (

										m_tauler[posicioActual.getFila() + (incFila * i)][posicioActual.getColumna() + (incColumna * i)]->getColorFitxa() != m_tauler[fitxaQueEsMou.getFila()][fitxaQueEsMou.getColumna()]->getColorFitxa() &&//diferent color
										m_tauler[posicioActual.getFila() + (incFila * i) + incFila][posicioActual.getColumna() + (incColumna * i) + incColumna] == nullptr
										) {
										//no recordo que es aixo ni perque serveix pero dona problemes, perque depen de si troba o no troba, el moviment s'afageix o no.
										Posicio tmpPos1(posicioActual.getFila() + incFila * i, posicioActual.getColumna() + incColumna * i);
										bool trobat = false;


										for (int j = 0;j < movimentsValids.size();j++)
										{
											for (int k = 0;k < movimentsValids[j].getNMorts();k++)
											{
												if (movimentsValids[j].getMortsPos(k) == tmpPos1)
												{

													trobat = true;
												}
											}
										}
										///




										if (!trobat)
										{

											Posicio pos2((posicioActual.getFila() + (incFila * i) + incFila), (posicioActual.getColumna() + (incColumna * i) + incColumna));


											Posicio tmpPos2(posicioActual.getFila() + (incFila * i) + incFila, posicioActual.getColumna() + (incColumna * i) + incColumna);
											posicions.push_back(posicioActual);
											posicions.push_back(tmpPos2);

											matada = true;


											morts.push_back(tmpPos1);
											


											//
											Moviment mov(DAMA_MATAR, posicions, morts);
											movimentsValids.push_back(mov);
										
											//

										}


									}




								}



							}

							limitTrobat = true;
						}

					}
					else
					{
						limitTrobat = true;
					}



					i++;


				}
			}
		}
	}
	return matada;
}






void Tauler::actualitzaMovimentsValids()
{
	for (int fila = 0; fila < N_FILES;fila++)
	{
		for (int col = 0;col < N_COLUMNES;col++)
		{
			if (m_tauler[fila][col] != nullptr) {
				
				m_tauler[fila][col]->esborraMoviments();
				vector <Moviment> mv;
				
				Posicio pos(fila, col);
				Posicio fitxaQueEsMou = pos;
				if (m_tauler[fila][col]->getTipusFitxa() == TIPUS_NORMAL)
				{
					normalMoure(pos, mv, fitxaQueEsMou);
					normalMatarMultiples(pos, mv, fitxaQueEsMou);
				}
				else
				{
					if (m_tauler[fila][col]->getTipusFitxa() == TIPUS_DAMA)
					{
						damaMoure(pos, mv, fitxaQueEsMou);//El fallo esta en damaMoure
						damaMatarMultiples(pos, mv, fitxaQueEsMou);

					}
				}
				for (int k = 0; k < mv.size(); k++)
				{
					m_tauler[fila][col]->afegeixMoviment(mv[k]);
				}
			}

		}
	}
}




void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[MAX_POSICIONS]) 
{
	nPosicions = 0;
	if (m_tauler[origen.getFila()][origen.getColumna()] != nullptr) {

		for (int i = 0; i < m_tauler[origen.getFila()][origen.getColumna()]->getNMoviments();i++) 
		{
			
			
			Moviment tmpMoviment = m_tauler[origen.getFila()][origen.getColumna()]->getMovimentPos(i);
			for (int j = 0; j < tmpMoviment.getNPosicions();j++) {
				bool trobat = false;
				int k = 0;
				while((k < nPosicions)&&(!trobat)){
					if (tmpMoviment.getPosicioPos(j) == posicionsPossibles[k]) {
						trobat = true;
					}
					k++;
				}

				if ((!trobat) && ((tmpMoviment.getPosicioPos(j) == origen) == false)) {
					posicionsPossibles[nPosicions] = tmpMoviment.getPosicioPos(j);
					nPosicions++;
				}
			}
		}

	}
}








bool Tauler::bufar(const Posicio& posicioOrigen, Moviment& movimentFet) //mod
{
	int maxIndex = -1;
	//Posicion de la ficha con el mejor movimiento
	int maxFila = -1;
	int maxCol = -1;
	int maxMorts = -1;


	//busquem el moviment de màximes morts
	for (int col = 0; col < N_COLUMNES; col++)
	{
		for (int fila = 0; fila < N_FILES; fila++)
		{
			if (m_tauler[fila][col] != nullptr && m_tauler[fila][col]->getColorFitxa() - 1 == m_tornBlanques) {
				for (int i = 0; i < m_tauler[fila][col]->getNMoviments(); i++)
				{

					Moviment moviment = m_tauler[fila][col]->getMovimentPos(i);
					if ((moviment.getTipus() != NORMAL_NO_MATAR) && (moviment.getTipus() != DAMA_NO_MATAR))
					{
						if (moviment.getNMorts() > maxMorts)
						{
							maxIndex = i;
							maxFila = fila;
							maxCol = col;
							maxMorts = moviment.getNMorts();

						}
					}

				}

			}

		}
	}

	//Si durant algun moviment es mata
	if (maxIndex != -1)
	{
		if (movimentFet.getNMorts() < maxMorts)
		{
			if (maxFila == posicioOrigen.getFila() && maxCol == posicioOrigen.getColumna()) //Si la ficha con el mejor movimiento es la que se mueve: mata la ficha en la posicion de destino
			{
				//Ultima posicion del movimiento
				Posicio posFinal = movimentFet.getPosicioPos(movimentFet.getNPosicions() - 1);
				if (m_tauler[posFinal.getFila()][posFinal.getColumna()] != nullptr) {
					m_tauler[posFinal.getFila()][posFinal.getColumna()]->setViva(false);//aixo pot donar problemes?
				}

			}
			else
			{
				if (m_tauler[maxFila][maxCol] != nullptr) {//defensiva
					m_tauler[maxFila][maxCol]->setViva(false);
				}

			}
			return true;
		}

	}
	return false;


}


/*
bool Tauler::seleccionaFitxa()
{

	cout << "---------------------------------------------" << endl;
	cout << "Selecció fitxa a moure:" << endl;
	cout << "---------------------------------------------" << endl;

	string fitxaRaw;
	bool valid = true;
	cout << endl << "Introdueix posicio: ";
	cin >> fitxaRaw;
	cout << endl;
	Posicio p;
	p.fromString(fitxaRaw);
	int filaActual = p.getFila();
	int colActual = p.getColumna();

	if ((filaActual > N_FILES) || (colActual > N_COLUMNES) || (filaActual < 0) || (colActual < 0))
	{
		cout << "Overflow";
		valid = false;
	}
	else {
		if (m_tauler[filaActual][colActual] != nullptr) {//no crec q clagui pero ho provem igual
			if (m_tornBlanques) {
				if (m_tauler[filaActual][colActual]->getColorFitxa() == COLOR_BLANC)
				{
					valid = true;
				}
				else {
					valid = false;
				}
			}
			else {
				if (m_tauler[filaActual][colActual]->getColorFitxa() == COLOR_NEGRE)
				{
					valid = true;
				}
				else {
					valid = false;
				}
			}

		}


	}

	if (valid) {
		m_colFitxaSeleccionada = colActual;
		m_filaFitxaSeleccionada = filaActual;
	}
	return valid;


}
*/


/*
bool Tauler::seleccionaDesti(Posicio& desti)
{
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




	if ((filaActual > N_FILES) || (colActual > N_COLUMNES) || (filaActual < 0) || (colActual < 0))
	{
		cout << "Overflow";
		valid = false;

	}
	else
	{
		Posicio posDesti(filaActual, colActual);
		Posicio posicionsPossibles[MAX_POSICIONS];
		int nPos = 0;
		getPosicionsPossibles(Posicio(m_filaFitxaSeleccionada, m_colFitxaSeleccionada), nPos, posicionsPossibles);
		for (int i = 0;i < nPos;i++)
		{
			if (posDesti == posicionsPossibles[i])
			{
				desti = posDesti;
				valid = true;//Perque llavors esta dins de les posicions possibles
			}
		}
	}

	return valid;
}
*/



bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) //os important
{
	//Ara trobar el moviment que s'ha fet dins de la llista de moviments valids de la fitxa. 
	bool trobat = false;
	int i = 0;
	Moviment movimentFet;


	if (m_tauler[origen.getFila()][origen.getColumna()] != nullptr) {
		while ((i < m_tauler[origen.getFila()][origen.getColumna()]->getNMoviments()) && (!trobat)) // AQUI ESTA EL POBLEMA; NO SURT DEL WHILE
		{


			if (m_tauler[origen.getFila()][origen.getColumna()]->getMovimentPos(i).getPosicioPos(m_tauler[origen.getFila()][origen.getColumna()]->getMovimentPos(i).getNPosicions() - 1) == desti)
			{
				movimentFet = m_tauler[origen.getFila()][origen.getColumna()]->getMovimentPos(i);
				trobat = true;



				///..Faig aixo, pero sé que després s'haura de sobreccaregar operador
				//m_tauler[desti.getFila()][desti.getColumna()] = m_tauler[origen.getFila()][origen.getColumna()];//ho copio tot
				//GOTO (to-do):
					//sobrecarregar el operador = de manera que pugui fer que una fitxa pilli tot lo d una altra
				if (m_tauler[desti.getFila()][desti.getColumna()] == nullptr)
				{
					m_tauler[desti.getFila()][desti.getColumna()] = new Fitxa;
				}


				m_tauler[desti.getFila()][desti.getColumna()]->setColorFitxa(m_tauler[origen.getFila()][origen.getColumna()]->getColorFitxa());
				m_tauler[desti.getFila()][desti.getColumna()]->setTipusFitxa(m_tauler[origen.getFila()][origen.getColumna()]->getTipusFitxa());
				m_tauler[desti.getFila()][desti.getColumna()]->setNMovimentsValids(m_tauler[origen.getFila()][origen.getColumna()]->getNMoviments());
				m_tauler[desti.getFila()][desti.getColumna()]->setPosicio(m_tauler[origen.getFila()][origen.getColumna()]->getPosicio());
				for (int j = 0; j < m_tauler[origen.getFila()][origen.getColumna()]->getNMoviments();j++)
				{
					m_tauler[desti.getFila()][desti.getColumna()]->afegeixMoviment(m_tauler[origen.getFila()][origen.getColumna()]->getMovimentPos(j));//former i
				}

				///..



				m_tauler[desti.getFila()][desti.getColumna()]->setPosicio(desti);
				m_tauler[origen.getFila()][origen.getColumna()]->setViva(false);
				/*
				m_filaFitxaSeleccionada = desti.getFila();//Mes facil. Aixi despres puc bufar i tota la pesca.
				m_colFitxaSeleccionada = desti.getColumna();
				*/			
			}
			i++;
		}
		if (trobat) {
			for (int j = 0; j < movimentFet.getNMorts(); j++)
			{
				m_tauler[movimentFet.getMortsPos(j).getFila()][movimentFet.getMortsPos(j).getColumna()]->setViva(false);//Matar totes les fitxes que el moviment mata.
			}
			if (m_tornBlanques)
			{
				m_nNegres -= movimentFet.getNMorts();
			}
			else
			{
				m_nBlanques -= movimentFet.getNMorts();
			}

			convertirADama();
			bufar(origen, movimentFet);
			eliminarFitxesMortes();
			
			m_tornBlanques = !m_tornBlanques;


		}
		return trobat;


	}
	
	actualitzaTaulerEnChars();


}



string Tauler::toString() const
{
	char taulerEnChars[N_FILES][N_COLUMNES];
	for (int i = 0;i < N_FILES;i++)
	{
		for (int j = 0;j < N_COLUMNES;j++)
		{
			if (m_tauler[i][j] == nullptr)
			{
				taulerEnChars[i][j] = '_';
			}
			else {
				if ((m_tauler[i][j]->getColorFitxa() == COLOR_BLANC) && (m_tauler[i][j]->getTipusFitxa() == TIPUS_NORMAL))
				{
					taulerEnChars[i][j] = 'O';
				}
				else {
					if ((m_tauler[i][j]->getColorFitxa() == COLOR_NEGRE) && (m_tauler[i][j]->getTipusFitxa() == TIPUS_NORMAL))
					{
						taulerEnChars[i][j] = 'X';
					}
					else {
						if ((m_tauler[i][j]->getColorFitxa() == COLOR_BLANC) && (m_tauler[i][j]->getTipusFitxa() == TIPUS_DAMA))
						{
							taulerEnChars[i][j] = 'D';
						}
						else {
							if ((m_tauler[i][j]->getColorFitxa() == COLOR_NEGRE) && (m_tauler[i][j]->getTipusFitxa() == TIPUS_DAMA))
							{
								taulerEnChars[i][j] = 'R';
							}
						}
					}
				}
			}




		}
	}

	string taula = "";
	for (int fila = 0; fila < N_FILES; fila++)
	{
		taula = taula + to_string(8 - fila) + ":";
		for (int col = 0; col < N_COLUMNES; col++)
		{
			taula = taula + taulerEnChars[fila][col] + " ";
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



void Tauler::llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]) const // NO MOD PERO CREC QUE ES IGUAL PERQUE ES TAULER EN CHARS
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
		if (m_tauler[0][col] != nullptr) {
			if (m_tauler[0][col]->getColorFitxa() == COLOR_BLANC)
			{
				m_tauler[0][col]->setTipusFitxa(TIPUS_DAMA);
			}

		}

	}

	//Damas Negras
	for (int col = 0; col < N_COLUMNES; col++)
	{
		if (m_tauler[7][col] != nullptr) {
			if (m_tauler[7][col]->getColorFitxa() == COLOR_NEGRE)
			{
				m_tauler[7][col]->setTipusFitxa(TIPUS_DAMA);
			}
		}

	}
}



void Tauler::eliminarFitxesMortes() //MOD
{

	//ELIMINAR EL CONTINGUT DE CADA CELA DE L ARRAY DINAMIC. DELETE I DESPRES TORNA A SER NULLPTR
	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			if (m_tauler[fila][col] != nullptr) {
				if (m_tauler[fila][col]->getViva() == false)
				{
					delete m_tauler[fila][col];
					m_tauler[fila][col] = nullptr;
				}
			}

		}
	}
}

bool Tauler::comptaNumeroMovimentsPossibles(const ColorFitxa color) const //MOD
{
	int nMoviments = 0;
	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			if (m_tauler[fila][col] != nullptr) {
				if (m_tauler[fila][col]->getColorFitxa() == color)
				{
					nMoviments = nMoviments + m_tauler[fila][col]->getNMoviments();
				}
			}

		}
	}

	if (nMoviments > 0)
	{
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

void Tauler::visualitzaTauler(int zeroDeX, int zeroDeY, int ampladaX, int alcadaY)
{
	for (int fila = 0; fila < N_FILES; fila++)
	{
		for(int col = 0; col < N_COLUMNES; col++)
		{
			if(m_tauler[fila][col] != nullptr)
			{
				m_tauler[fila][col]->visualitzaFitxa(zeroDeX, zeroDeY, ampladaX, alcadaY);
			}
		}
	}
}