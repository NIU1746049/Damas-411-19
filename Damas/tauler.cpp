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
			}

		}
	}
}




bool Tauler::normalMoure(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids, Posicio fitxaQueEsMou)const
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
			if (m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getColumna() + i] == nullptr)
			{
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


bool Tauler::normalMatar(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids, Posicio fitxaQueEsMou)const
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

				Posicio posicions[MAX_POSICIONS] = { posicioActual, tmpP2 };

				Posicio tmpP3[MAX_POSICIONS] = { tmpP1 };

				Moviment nouMoviment(NORMAL_MATAR, posicions, 2, 1, tmpP3);

				movimentsValids[nMovimentsValids] = nouMoviment;

				nMovimentsValids++;

				valid = true;
			}
		}
	}
	return valid;
}



bool Tauler::normalMatarMultiples(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids, Posicio fitxaQueEsMou)const
{
	Moviment tmpMoviments[MAX_MOVIMENTS];
	int tmpNMoviments = 0;

	brancaNormal(posicioActual, tmpMoviments, tmpNMoviments, movimentsValids, nMovimentsValids, fitxaQueEsMou);

	nMovimentsValids++;


	return (nMovimentsValids > 0);
}



void Tauler::brancaDama(Posicio posicioOrigen, Moviment tmpMoviments[MAX_MOVIMENTS], int& tmpNMoviments, Moviment movimentsDefinitius[MAX_MOVIMENTS], int nMovimentsDefinitius, Posicio fitxaQueEsMou)const
{

	int tmpNMovimentsInicial = tmpNMoviments;


	if (damaMatar(posicioOrigen, tmpMoviments, tmpNMoviments, fitxaQueEsMou))
	{

		for (int i = tmpNMovimentsInicial;i < tmpNMoviments;i++)
		{


			brancaDama(tmpMoviments[i].getPosicioPos(tmpMoviments[i].getNPosicions() - 1), tmpMoviments, tmpNMoviments, movimentsDefinitius, nMovimentsDefinitius, fitxaQueEsMou);
		}
	}
	else {

		cout << endl << "DamaMatar dona FALSE quan la posicio es: " << posicioOrigen.toString() << endl;
	}
	Moviment movimentDefinitiuRaw;
	movimentDefinitiuRaw.setNPosicions(0);
	if (tmpNMoviments == 0) {
		cout << "Return?";
		return;
	}
	cout << "Passat?";
	for (int j = 0;j < tmpNMoviments;j++)
	{
		for (int i = 0;i < tmpMoviments[j].getNPosicions();i++)
		{
			movimentDefinitiuRaw.setPosicioPos(movimentDefinitiuRaw.getNPosicions(), tmpMoviments[j].getPosicioPos(i));
			movimentDefinitiuRaw.setNPosicions(movimentDefinitiuRaw.getNPosicions() + 1);
			movimentDefinitiuRaw.setTipus(DAMA_MATAR_MULTIPLES);
		}
	}


	for (int j = 0;j < tmpNMoviments;j++)
	{
		for (int i = 0;i < tmpMoviments[j].getNMorts();i++)
		{


			movimentDefinitiuRaw.setMortsPos(movimentDefinitiuRaw.getNMorts(), tmpMoviments[j].getMortsPos(i));
			movimentDefinitiuRaw.setNMorts(movimentDefinitiuRaw.getNMorts() + 1);
		}
	}



	movimentsDefinitius[nMovimentsDefinitius] = movimentDefinitiuRaw;
	nMovimentsDefinitius++;
}


void Tauler::brancaNormal(Posicio posicioOrigen, Moviment tmpMoviments[MAX_MOVIMENTS], int& tmpNMoviments, Moviment movimentsDefinitius[MAX_MOVIMENTS], int nMovimentsDefinitius, Posicio fitxaQueEsMou)const
{

	int tmpNMovimentsInicial = tmpNMoviments;

	if (normalMatar(posicioOrigen, tmpMoviments, tmpNMoviments, fitxaQueEsMou))
	{

		for (int i = tmpNMovimentsInicial;i < tmpNMoviments;i++)
		{
			brancaNormal(tmpMoviments[i].getPosicioPos(tmpMoviments[i].getNPosicions() - 1), tmpMoviments, tmpNMoviments, movimentsDefinitius, nMovimentsDefinitius, fitxaQueEsMou);

		}
	}
	else {
		Moviment movimentDefinitiuRaw;
		movimentDefinitiuRaw.setNPosicions(0);
		for (int j = 0;j < tmpNMoviments;j++) {
			for (int i = 0;i < tmpMoviments[j].getNPosicions();i++)
			{
				movimentDefinitiuRaw.setPosicioPos(movimentDefinitiuRaw.getNPosicions(), tmpMoviments[j].getPosicioPos(i));
				movimentDefinitiuRaw.setNPosicions(movimentDefinitiuRaw.getNPosicions() + 1);
				movimentDefinitiuRaw.setTipus(NORMAL_MATAR_MULTIPLES);
			}
		}

		for (int j = 0;j < tmpNMoviments;j++)
		{
			for (int i = 0;i < tmpMoviments[j].getNMorts();i++)
			{


				movimentDefinitiuRaw.setMortsPos(movimentDefinitiuRaw.getNMorts(), tmpMoviments[j].getMortsPos(i));
				movimentDefinitiuRaw.setNMorts(movimentDefinitiuRaw.getNMorts() + 1);
			}
		}

		movimentsDefinitius[nMovimentsDefinitius] = movimentDefinitiuRaw;
		nMovimentsDefinitius++;

	}

}



bool Tauler::damaMatarMultiples(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids, Posicio fitxaQueEsMou)const
{

	Moviment tmpMoviments[MAX_MOVIMENTS];
	int tmpNMoviments = 0;



	//jo crec q aixi esta be no? NO?
	brancaDama(posicioActual, tmpMoviments, tmpNMoviments, movimentsValids, nMovimentsValids, fitxaQueEsMou);
	cout << "Supera branca Dama?";

	nMovimentsValids += tmpNMoviments;
	//

	for (int i = 0;i < tmpNMoviments;i++) {
		cout << endl << "moviment " << i << ": " << endl;
		for (int j = 0;j < tmpMoviments[i].getNPosicions();j++) {
			cout << tmpMoviments[i].getPosicioPos(j).toString() << endl;
		}
	}
	//
	cout << "I a més a més arriba al final de branca dama";
	return (tmpNMoviments > 0);


}





//dama
bool Tauler::damaMoure(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids, Posicio fitxaQueEsMou)const
{
	int nMovimentsValidsInicial = nMovimentsValids;
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
							Posicio posicions[MAX_POSICIONS];
							posicions[0] = posicioActual;
							Posicio p((posicioActual.getFila() + (incFila * iter)), (posicioActual.getColumna() + (incColumna * iter)));
							posicions[1] = p;
							Posicio morts[MAX_MORTS] = {};
							Moviment m(DAMA_NO_MATAR, posicions, 2, 0, morts);
							movimentsValids[nMovimentsValids] = m;
							nMovimentsValids++;

						}
						else
						{

							Posicio p((posicioActual.getFila() + (incFila * iter) - incFila), (posicioActual.getColumna() + (incColumna * iter) - incColumna));

							if ((p == posicioActual) == false)
							{
								Posicio posicions[MAX_POSICIONS];
								posicions[0] = posicioActual;
								posicions[1] = p;
								Posicio morts[MAX_MORTS] = {};
								Moviment m(DAMA_NO_MATAR, posicions, 2, 0, morts);
								movimentsValids[nMovimentsValids] = m;
								nMovimentsValids++;

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
	int incrementMovimentsValids = nMovimentsValids - nMovimentsValidsInicial;
	if (incrementMovimentsValids > 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}


/*bool Tauler::damaMatar(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids,Posicio fitxaQueEsMou)const
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

				Posicio posicions[MAX_POSICIONS];
				int nMorts = 0;
				Posicio morts[MAX_MORTS];


				while (!limitTrobat) {

					if (
						((posicioActual.getFila() + incFila * i) < N_FILES) &&
						((posicioActual.getColumna() + incColumna * i) < N_COLUMNES) &&
						((posicioActual.getFila() + incFila * i) > 0) &&
						((posicioActual.getColumna() + incColumna * i) > 0)

						)//evitar Stack Overflow
					{

						cout << endl << "en la posicio " << posicioActual.toString() << " s'arriba despres de STACK OVERFLOW i abans de EMPTY";
						if(m_tauler[posicioActual.getFila() + incFila * i][posicioActual.getColumna() + incColumna * i].getTipusFitxa() != TIPUS_EMPTY)//si la següent NO esta buida
						{
							cout << endl << "en la posicio " << posicioActual.toString() << " s'arriba despres de la comprovacio de empty";

							Posicio pos((posicioActual.getFila() + incFila * i), (posicioActual.getColumna() + incColumna * i));
							if (
								((posicioActual.getFila() + (incFila * i) + incFila)<N_FILES)&&
								((posicioActual.getColumna() + (incColumna * i) + incColumna)<N_COLUMNES)&&
								((posicioActual.getFila() + (incFila * i) + incFila)>0)&&
								((posicioActual.getColumna() + (incColumna * i) + incColumna)>0)
								) {


								cout << endl << "en la posicio " << posicioActual.toString() << " no es troba un Stack Overflow a la segona comprovacio. (comprovacio de la posicio següent no l altre)";

								if (

									m_tauler[posicioActual.getFila() + (incFila * i)][posicioActual.getColumna() + (incColumna * i)].getColorFitxa() != m_tauler[fitxaQueEsMou.getFila()][fitxaQueEsMou.getColumna()].getColorFitxa() &&//diferent color
									m_tauler[posicioActual.getFila() + (incFila * i) + incFila][posicioActual.getColumna() + (incColumna * i) + incColumna].getTipusFitxa() == TIPUS_EMPTY
									) {
									//DEBUG
									cout <<endl<< "moment de la veritat" << endl;

									//

									//no recordo que es aixo ni perque serveix pero dona problemes, perque depen de si troba o no troba, el moviment s'afageix o no.
									Posicio tmpPos1(posicioActual.getFila() + incFila * i, posicioActual.getColumna() + incColumna * i);
									bool trobat = false;

									for (int j = 0;j < nMovimentsValids;j++)
									{
										cout << endl << "entra for"<<endl;
										for (int k = 0;k < movimentsValids[j].getNMorts();k++)
										{
											if (movimentsValids[j].getMortsPos(k) == tmpPos1)
											{
												cout << endl << "trobat = true en la posicio següent: " << tmpPos1.toString() << endl;

												trobat = true;
											}
										}
									}
									///

									if (!trobat)
									{
										cout << endl << "entra !trobat" << endl;
										Posicio pos2((posicioActual.getFila() + (incFila * i) + incFila), (posicioActual.getColumna() + (incColumna * i) + incColumna));


										Posicio tmpPos2(posicioActual.getFila() + (incFila * i) + incFila, posicioActual.getColumna() + (incColumna * i) + incColumna);
										posicions[0] = posicioActual;
										posicions[1] = tmpPos2;

										matada = true;


										morts[nMorts] = tmpPos1;
										nMorts++;


										//
										Moviment mov(DAMA_MATAR, posicions, 2, 1, morts);
										movimentsValids[nMovimentsValids] = mov;
										nMovimentsValids++;
										//

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
*/


//DamaMatar

bool Tauler::damaMatar(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids, Posicio fitxaQueEsMou)const
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

				Posicio posicions[MAX_POSICIONS];
				int nMorts = 0;
				Posicio morts[MAX_MORTS];


				while (!limitTrobat) {

					if (
						((posicioActual.getFila() + incFila * i) < N_FILES) &&
						((posicioActual.getColumna() + incColumna * i) < N_COLUMNES) &&
						((posicioActual.getFila() + incFila * i) > 0) &&
						((posicioActual.getColumna() + incColumna * i) > 0)

						)//evitar Stack Overflow
					{

						if (m_tauler[posicioActual.getFila() + incFila * i][posicioActual.getColumna() + incColumna * i] != nullptr)//si la següent NO esta buida
						{

							Posicio pos((posicioActual.getFila() + incFila * i), (posicioActual.getColumna() + incColumna * i));
							if (
								((posicioActual.getFila() + (incFila * i) + incFila) < N_FILES) &&
								((posicioActual.getColumna() + (incColumna * i) + incColumna) < N_COLUMNES) &&
								((posicioActual.getFila() + (incFila * i) + incFila) > 0) &&
								((posicioActual.getColumna() + (incColumna * i) + incColumna) > 0)
								) {

								if ((m_tauler[posicioActual.getFila() + (incFila * i)][posicioActual.getColumna() + (incColumna * i)] != nullptr) && (m_tauler[fitxaQueEsMou.getFila()][fitxaQueEsMou.getColumna()] != nullptr)) {

									if (

										m_tauler[posicioActual.getFila() + (incFila * i)][posicioActual.getColumna() + (incColumna * i)]->getColorFitxa() != m_tauler[fitxaQueEsMou.getFila()][fitxaQueEsMou.getColumna()]->getColorFitxa() &&//diferent color
										m_tauler[posicioActual.getFila() + (incFila * i) + incFila][posicioActual.getColumna() + (incColumna * i) + incColumna] == nullptr
										) {

										//no recordo que es aixo ni perque serveix pero dona problemes, perque depen de si troba o no troba, el moviment s'afageix o no.
										Posicio tmpPos1(posicioActual.getFila() + incFila * i, posicioActual.getColumna() + incColumna * i);
										bool trobat = false;


										for (int j = 0;j < nMovimentsValids;j++)
										{
											for (int k = 0;k < movimentsValids[j].getNMorts();k++)
											{
												if (movimentsValids[j].getMortsPos(k) == tmpPos1)
												{
													cout << endl << "desde la posicio " << posicioActual.toString() << " trobat = true en la posicio següent : " << tmpPos1.toString() << endl;

													trobat = true;
												}
											}
										}
										///




										if (!trobat)
										{

											cout << endl << "entra !troba:::::::::::::::::::::::::::::::::::::::::::::::::::::::t" << endl;
											Posicio pos2((posicioActual.getFila() + (incFila * i) + incFila), (posicioActual.getColumna() + (incColumna * i) + incColumna));


											Posicio tmpPos2(posicioActual.getFila() + (incFila * i) + incFila, posicioActual.getColumna() + (incColumna * i) + incColumna);
											posicions[0] = posicioActual;
											posicions[1] = tmpPos2;

											matada = true;


											morts[nMorts] = tmpPos1;
											nMorts++;


											//
											Moviment mov(DAMA_MATAR, posicions, 2, 1, morts);
											movimentsValids[nMovimentsValids] = mov;
											nMovimentsValids++;
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




/*
void Tauler::actualitzaMovimentsValids()
{
	for (int fila = 0; fila < N_FILES;fila++)
	{
		for (int col = 0;col < N_COLUMNES;col++)
		{
			m_tauler[fila][col].esborraMoviments();
			Moviment mv[MAX_MOVIMENTS] = {};
			int nMv = 0;

			if (m_tauler[fila][col].getTipusFitxa() == TIPUS_NORMAL)
			{
				Posicio pos(fila, col);
				Posicio fitxaQueEsMou = pos;

				normalMoure(pos, mv, nMv, fitxaQueEsMou);

				if (normalMatar(pos, mv, nMv, fitxaQueEsMou))
				{
					normalMatarMultiples(pos, mv, nMv, fitxaQueEsMou);

				}
			}
			else
			{
				if (m_tauler[fila][col].getTipusFitxa() == TIPUS_DAMA)
				{
					//DEBUG
					cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaa";
					//
					Posicio pos(fila,col);
					Posicio fitxaQueEsMou = pos;



					damaMoure(pos, mv, nMv, fitxaQueEsMou);

					if (damaMatar(pos, mv, nMv, fitxaQueEsMou))
					{
						//DEBUG
						cout << "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
						//
						damaMatarMultiples(pos, mv, nMv, fitxaQueEsMou);
					}
				}
			}

			for (int k = 0; k < nMv; k++)
			{
				m_tauler[fila][col].setMovimentPos(k, mv[k]);

			}
			m_tauler[fila][col].setNMovimentsValids(nMv);
		}
	}
}
*/

void Tauler::actualitzaMovimentsValids()
{
	for (int fila = 0; fila < N_FILES;fila++)
	{
		for (int col = 0;col < N_COLUMNES;col++)
		{
			if (m_tauler[fila][col] != nullptr) {
				m_tauler[fila][col]->esborraMoviments();
				Moviment mv[MAX_MOVIMENTS] = {};
				int nMv = 0;

				if (m_tauler[fila][col]->getTipusFitxa() == TIPUS_NORMAL)
				{
					Posicio pos(fila, col);
					Posicio fitxaQueEsMou = pos;

					normalMoure(pos, mv, nMv, fitxaQueEsMou);

					if (normalMatar(pos, mv, nMv, fitxaQueEsMou))
					{
						normalMatarMultiples(pos, mv, nMv, fitxaQueEsMou);

					}
				}
				else
				{
					if (m_tauler[fila][col]->getTipusFitxa() == TIPUS_DAMA)
					{
						//DEBUG
						cout << endl << "aaaaaaaaaaaaaaaaaaaaaaaaaaa";
						//
						Posicio pos(fila, col);
						Posicio fitxaQueEsMou = pos;


						cout << "Intento fer DamaMoure";
						damaMoure(pos, mv, nMv, fitxaQueEsMou);//El fallo esta en damaMoure
						cout << "Supera Dama Moure";
						damaMatarMultiples(pos, mv, nMv, fitxaQueEsMou);
						damaMatar(pos, mv, nMv, fitxaQueEsMou);



					}
				}

				for (int k = 0; k < nMv; k++)
				{
					m_tauler[fila][col]->setMovimentPos(k, mv[k]);

				}
				m_tauler[fila][col]->setNMovimentsValids(nMv);

			}

		}
	}
}



/*
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[MAX_POSICIONS])
{
	nPosicions = 0;

	for (int i = 0;i < m_tauler[origen.getFila()][origen.getColumna()].getNMoviments();i++)
	{
		Moviment moviment=m_tauler[origen.getFila()][origen.getColumna()].getMovimentPos(i);


		bool valid = true;
		for (int k = 0; k < nPosicions;k++)
		{

			if (posicionsPossibles[k] == moviment.getPosicioPos(moviment.getNPosicions() - 1)) {//No vull que hi hagin posicions repetides
				valid = false;
			}
		}
		if (valid)
		{

			//posicionsPossibles[nPosicions] = moviment.getPosicioPos(moviment.getNPosicions() - 1);
			for (int i = 0;i < moviment.getNPosicions() - 1;i++) {
				posicionsPossibles[nPosicions]=moviment.getPosicioPos(i+1);
				nPosicions++;

			}


		}


	}

}
*/
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[MAX_POSICIONS])//Mod
{
	//DEBUG
	cout << endl << "getPosicionsPossibles: " << endl;


	//
	nPosicions = 0;
	//
	int tmpNPosicions = 0;
	Posicio tmpPosicionsPossibles[MAX_POSICIONS];

	//
	if (m_tauler[origen.getFila()][origen.getColumna()] != nullptr) {
		for (int i = 0;i < m_tauler[origen.getFila()][origen.getColumna()]->getNMoviments();i++)
		{
			//
			//if (m_tauler[origen.getFila()][origen.getColumna()] == nullptr) { cout << "DAQUI BE EL FALLO"; }
			//


			Moviment moviment = m_tauler[origen.getFila()][origen.getColumna()]->getMovimentPos(i);


			bool valid = true;
			for (int k = 0; k < tmpNPosicions;k++)
			{

				if (tmpPosicionsPossibles[k] == moviment.getPosicioPos(moviment.getNPosicions() - 1)) {//No vull que hi hagin posicions repetides
					valid = false;
				}
			}
			if (valid)
			{

				for (int i = 0;i < moviment.getNPosicions() - 1;i++) {
					tmpPosicionsPossibles[tmpNPosicions] = moviment.getPosicioPos(i + 1);
					tmpNPosicions++;

				}


			}


		}
		for (int i = 0;i < tmpNPosicions;i++) {
			bool trobat = false;
			int j = 0;
			while ((j < nPosicions) && (!false)) {
				if (tmpPosicionsPossibles[i] == posicionsPossibles[j]) {
					trobat = true;
				}
				j++;
			}
			if ((!trobat) && ((tmpPosicionsPossibles[i] == origen) == false)) {
				cout << tmpPosicionsPossibles[i].toString() << endl;
				posicionsPossibles[nPosicions] = tmpPosicionsPossibles[i];
				nPosicions++;
			}
		}
		cout << endl;

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
			if (m_tauler[fila][col] != nullptr) {
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

	//Si durant algun moviment es mata::
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
bool Tauler::seleccionaFitxa() //MOD pero crec q ni cal
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

////TO-DO
//arreglant tema de memoria dinamica.(en proces)
//cnaviar moviments valids i getmoviments (per simetria ni q sigui)



bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) //os important
{
	//Ara trobar el moviment que s'ha fet dins de la llista de moviments valids de la fitxa. 
	bool trobat = false;
	int i = 0;
	Moviment movimentFet;


	if (m_tauler[origen.getFila()][origen.getColumna()] != nullptr) {
		while ((i < m_tauler[origen.getFila()][origen.getColumna()]->getNMoviments()) && (!trobat))
		{



			if (m_tauler[origen.getFila()][origen.getColumna()]->getMovimentPos(i).getPosicioPos(m_tauler[origen.getFila()][origen.getColumna()]->getMovimentPos(i).getNPosicions() - 1) == desti)
			{
				movimentFet = m_tauler[origen.getFila()][origen.getColumna()]->getMovimentPos(i);
				trobat = true;



				///..Faig aixo, pero sé que després s'haura de sobreccaregar operador
				//m_tauler[desti.getFila()][desti.getColumna()] = m_tauler[origen.getFila()][origen.getColumna()];//ho copio tot
				if (m_tauler[desti.getFila()][desti.getColumna()] == nullptr)
				{
					m_tauler[desti.getFila()][desti.getColumna()] = new Fitxa;
				}


				m_tauler[desti.getFila()][desti.getColumna()]->setColorFitxa(m_tauler[origen.getFila()][origen.getColumna()]->getColorFitxa());
				m_tauler[desti.getFila()][desti.getColumna()]->setTipusFitxa(m_tauler[origen.getFila()][origen.getColumna()]->getTipusFitxa());
				m_tauler[desti.getFila()][desti.getColumna()]->setNMovimentsValids(m_tauler[origen.getFila()][origen.getColumna()]->getNMoviments());
				m_tauler[desti.getFila()][desti.getColumna()]->setPosicio(m_tauler[origen.getFila()][origen.getColumna()]->getPosicio());

				for (int j = 0; j < m_tauler[desti.getFila()][desti.getColumna()]->getNMoviments();j++)
				{
					m_tauler[desti.getFila()][desti.getColumna()]->setMovimentPos(i, m_tauler[desti.getFila()][desti.getColumna()]->getMovimentPos(i));
				}

				///..



				m_tauler[desti.getFila()][desti.getColumna()]->setPosicio(desti);
				m_tauler[origen.getFila()][origen.getColumna()]->setColorITipusFitxa('_');//Fitxa buida


				//
				m_filaFitxaSeleccionada = desti.getFila();//Mes facil. Aixi despres puc bufar i tota la pesca.
				m_colFitxaSeleccionada = desti.getColumna();
				//			
			}
			i++;
		}

		if (trobat) {
			for (int j = 0; j < movimentFet.getNMorts(); j++)
			{
				//AQUI HARIA DE POSARME DEFENISU I FDER UN !=nullptr?
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
			



		}
		return trobat;

	}
	actualitzaTaulerEnChars();


}



string Tauler::toString() const //MOD (ja esta no?)
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

//Crec que he fet que funcioni perque com estava abans et parava el joc a la meitat perquesi.
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