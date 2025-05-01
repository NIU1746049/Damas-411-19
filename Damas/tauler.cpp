using namespace std;
#include <iostream>
#include "string"

#include "tauler.hpp"


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

//TO-DO
//passar per referencia
//treure +1


bool Tauler::normalMoure(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids)const
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


bool Tauler::normalMatar(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids)const {
	cout << "Pero aqui si";
	bool valid = false;
	int incrementVertical;
	if (m_tauler[posicioActual.getFila()][posicioActual.getColumna()].getColorFitxa() == COLOR_BLANC) {
		incrementVertical = -1;

	}
	else {
		incrementVertical = 1;

	}
	for (int i = -1; i < 2;i++) {


		if (
			((posicioActual.getFila() + incrementVertical) < N_FILES) && 
			((posicioActual.getColumna() + i) < N_COLUMNES) &&
			((posicioActual.getFila() + 2 * incrementVertical) < N_FILES) && 
			((posicioActual.getColumna() + 2 * i) < N_COLUMNES) &&
			((posicioActual.getFila() + incrementVertical)>=0)&&
			((posicioActual.getColumna() + i)>=0)&&
			((posicioActual.getFila() + 2 * incrementVertical)>=0)&&
			((posicioActual.getColumna() + 2 * i)>=0)&&
			(i != 0)
			
			
			) {//Parentesis ben posats???????????
			if ((m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getColumna() + i].getTipusFitxa() != TIPUS_EMPTY) &&
				(m_tauler[posicioActual.getFila() + 2 * incrementVertical][posicioActual.getColumna() + 2 * i].getTipusFitxa() == TIPUS_EMPTY) &&
				(m_tauler[posicioActual.getFila() + incrementVertical][posicioActual.getColumna() + i].getColorFitxa() != m_tauler[posicioActual.getFila()][posicioActual.getColumna()].getColorFitxa())) {
				//Fotre el moviment aqui
				cout << endl<<"ESTIC A" << posicioActual.toString() << "SOC DEL TIPUS " <<m_tauler[posicioActual.getFila()][posicioActual.getColumna()].getTipusFitxa() << " I EM PUC MOURE MATANT" << endl;
				Posicio tmpP1((posicioActual.getFila() + incrementVertical), (posicioActual.getColumna() + i));
				Posicio tmpP2((posicioActual.getFila() + 2 * incrementVertical), (posicioActual.getColumna() + 2 * i));
				
				//cout << endl << "P1: "<<tmpP1.toString()<<endl;
				//cout << endl << "P2: "<< tmpP2.toString()<<endl;
				Posicio posicions[MAX_POSICIONS] = { posicioActual,
					tmpP2,
				};


				Posicio tmpP3[MAX_POSICIONS] = {tmpP1};
				
				
				Moviment nouMoviment(NORMAL_MATAR, posicions, 2, 1, tmpP3);

				movimentsValids[nMovimentsValids] = nouMoviment;
				
				valid = true;
				//cout << endl<<":- "<<nouMoviment.getPosicioPos(1).toString()<<endl;
				nMovimentsValids++;

			}
		}
	}
	return valid;
}





bool Tauler::normalMatarMultiples(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids)const {
	cout << "Executant normalMatarMultiples en la posicio: " << posicioActual.toString() << endl;
	Moviment visitats[MAX_MOVIMENTS];
	Moviment perVisitar[MAX_MOVIMENTS];
	Moviment actual[MAX_MOVIMENTS];

	int nVisitats = 0;
	int nPerVisitar = 0;
	int nActual = 0;
	
	actual[0].setPosicioPos(0,posicioActual);
	actual[0].setNPosicions(1);
	nVisitats++;

	Moviment tmpMoviments[MAX_MOVIMENTS];
	int nTmpMoviments = 0;
	if (
		((actual[nActual].getPosicioPos(actual[nActual].getNPosicions() - 1).getFila())<N_FILES) &&
		((actual[nActual].getPosicioPos(actual[nActual].getNPosicions() - 1).getColumna())<N_COLUMNES) &&
		((actual[nActual].getPosicioPos(actual[nActual].getNPosicions() - 1).getFila())>0)&&
		((actual[nActual].getPosicioPos(actual[nActual].getNPosicions() - 1).getColumna())>=0)
		) {
		normalMatar(actual[nActual].getPosicioPos(actual[nActual].getNPosicions() - 1), tmpMoviments, nTmpMoviments);
		for (int i = 0;i < nTmpMoviments; i++) {
			perVisitar[nPerVisitar] = tmpMoviments[i];

			for (int j = 0;j < actual[nActual].getNPosicions();j++) {
				perVisitar[nPerVisitar].setPosicioPos(j, actual[nActual].getPosicioPos(j));
				perVisitar[nPerVisitar].setNPosicions(perVisitar[nPerVisitar].getNPosicions() + 1);
			}


			perVisitar[nPerVisitar].setPosicioPos((perVisitar[nPerVisitar].getNPosicions() + 1), tmpMoviments[i].getPosicioPos(1));//Nomes vull lultima, i sempre en tenen 2.
			perVisitar[nPerVisitar].setNPosicions(tmpMoviments[i].getNPosicions());
			nPerVisitar++;
		}
	}
	nActual++;
	/*
	for (int j = 0;j < perVisitar[nPerVisitar].getNPosicions();j++) {
		actual[nActual].setPosicioPos(j) = perVisitar[nPerVisitar].getPosicioPos(j);
		actual[nActual].setNPosicions(actual[nActual].getNPosicions() + 1);

	}
	*/
	//aixi jastaria no?
	actual[nActual] = perVisitar[nPerVisitar];
	visitats[nVisitats] = perVisitar[nPerVisitar];
	nVisitats++;
	nPerVisitar--;//realment no cal posar res a l array estil per a "borrar" lo altre, oi?

	while (nPerVisitar > 0) {
		Moviment tmpMoviments[MAX_MOVIMENTS];
		int nTmpMoviments = 0;
		normalMatar(actual[nActual].getPosicioPos(actual[nActual].getNPosicions() - 1), tmpMoviments, nTmpMoviments);
		for (int i = 0;i < nTmpMoviments; i++) {
			perVisitar[nPerVisitar] = tmpMoviments[i];

			for (int j = 0;j < actual[nActual].getNPosicions();j++) {
				perVisitar[nPerVisitar].setPosicioPos(j,actual[nActual].getPosicioPos(j));
				perVisitar[nPerVisitar].setNPosicions(perVisitar[nPerVisitar].getNPosicions() + 1);
			}


			perVisitar[nPerVisitar].setPosicioPos((perVisitar[nPerVisitar].getNPosicions() + 1), tmpMoviments[i].getPosicioPos(1));//Nomes vull lultima, i sempre en tenen 2.
			perVisitar[nPerVisitar].setNPosicions(tmpMoviments[i].getNPosicions());
			nPerVisitar++;
		}
		nActual++;
		/*
		for (int j = 0;j < perVisitar[nPerVisitar].getNPosicions();j++) {
			actual[nActual].setPosicioPos(j) = perVisitar[nPerVisitar].getPosicioPos(j);
			actual[nActual].setNPosicions(actual[nActual].getNPosicions() + 1);

		}
		*/
		for (int k = 0;k < visitats[nVisitats].getNPosicions();k++) {
			cout << endl << "papo: " << visitats[nVisitats].getPosicioPos(k) << endl;
		}
		actual[nActual] = perVisitar[nPerVisitar];
		visitats[nVisitats] = perVisitar[nPerVisitar];
		
		
		nVisitats++;
		nPerVisitar--;//realment no cal posar res a l array estil per a "borrar" lo altre, oi?

	}
	
	
	/*
	
	posicioActual;
	visitats;
	per visitar;

	posicioActual --> visitats[]
	visitats +1

	fer normalMatar(posicio actual, arrayDeMoviments, nMoviments)
		per tants valors com nMoviments :
	agafar ultimes dues posicions de l array de moviments, afegir també a l inici les posicions de posicioActual i establirho
		com a array[] i fotreli dins de perVisitar[].
		incrementem contador de perVisitar

	ara posicio actual es l ultima posicio(on apunta el contador de perVisitar) dins de perVisitar.
	Fem que posicioActual = perVisitar[ultima], perVisitar[ultima] = EMPTY o lo q sigui i decrementem en 1 el contador de perVisitar


	bucle while (segueixin haventhi vehins per visitar) {
		
		int nMoviments=0

		1)
		fer normalMatar(posicio actual, arrayDeMoviments,nMoviments)

		i per tants valors com nMoviments:


		arrayDeMoviments[i].getPosicioPos(1)
			arrayDeMoviments[i].getPosicioPos(2)


			agafar ultimes dues posicions al Moviment (array de poscions), afegir també a l inici les posicions de posicioActual i establirho
					com a array[] i fotreli dins de perVisitar[].
			incrementem contador de perVisitar


		2)
		ara posicio actual es l ultima posicio (on apunta el contador de perVisitar) dins de perVisitar.
		Fem que posicioActual=perVisitar[ultima], visitats=perVisitar[ultima], perVisitar[ultima] = EMPTY o lo q sigui i decrementem en 1 el contador de perVisitar



		
	}
	

	

	



	*/
	
	
	

	movimentsValids = visitats;
	nMovimentsValids = nVisitats;
	

	


	return (nVisitats>1);
	
}


/*
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
	*/



//dama
bool Tauler::damaMoure(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids)const
{
	int nMovimentsValidsInicial = nMovimentsValids;
	for (int incColumna = -1;incColumna < 2;incColumna++) {
		for (int incFila = -1;incFila < 2;incFila++)
		{
			if ((incColumna != 0) && (incFila != 0))
			{
				bool possible = false;
				bool limitTrobat = false;//Ja sigui taulell o casella contraria
				int iter = 1;
				Posicio posicions[MAX_POSICIONS];
				posicions[0] = posicioActual;
				while (!limitTrobat) {//Iterar per una direccio possible de moviments fins que no sigui possible o be perque ja no estic al taulell o perque mhe trobat una altre fitxa.
					if (
						((posicioActual.getFila() + incFila * iter) < N_FILES) && 
						((posicioActual.getColumna() + incColumna * iter) < N_COLUMNES)&&
						((posicioActual.getFila() + incFila * iter)>0)&&
						((posicioActual.getColumna() + incColumna * iter)>0)
						) {//Evitant Stack Overflow, que no se surti del taulell

						if ((m_tauler[posicioActual.getFila() + incFila * iter][posicioActual.getColumna() + incColumna * iter].getTipusFitxa() == TIPUS_EMPTY)) {//que no hi hagi una fitxa.............
							
							
							//cout << endl<<endl<<"POS::: " << p.toString() << ".."<<endl<<endl;
							//posicions[nPosicions] = p;
							//nPosicions++;
						}
						else {

							Posicio p((posicioActual.getFila() + incFila * iter), (posicioActual.getColumna() + incColumna * iter));
							posicions[1] = p;
							limitTrobat = true;
							possible = true;
						}
					}
					else {
						limitTrobat = true;
					}
					iter++;
				}
				if (possible) {
					Posicio morts[MAX_MORTS] = {};
					Moviment m(DAMA_NO_MATAR, posicions, 2, 0, morts);
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



bool Tauler::damaMatar(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids)const {
	bool matada = true;
	for (int incColumna = -1;incColumna < 2;incColumna++) {
		for (int incFila = -1;incFila < 2;incFila++)
		{
			if ((incColumna != 0) && (incFila != 0)) {
				matada = false;
				bool limitTrobat = false;
				int i = 1;
				//nou moviment:
				//Posicio posicions[MAX_POSICIONS];
				//int nPosicions = 0;
				Posicio posicions[MAX_POSICIONS];
				int nMorts = 0;
				Posicio morts[MAX_MORTS];


				while (!limitTrobat) {
					if (
						((posicioActual.getFila() + incFila * i) < N_FILES) &&
						((posicioActual.getColumna() + incColumna * i) < N_COLUMNES) &&
						((posicioActual.getFila() + incFila * i) > 0) &&
						((posicioActual.getColumna() + incColumna * i) > 0)
						
						) 
					{

						//if (m_tauler[posicioActual.getFila() + incFila * i][posicioActual.getColumna() + incColumna * i].getTipusFitxa() == TIPUS_EMPTY) {
						//	Posicio tmpPos1(posicioActual.getFila() + incFila * i, posicioActual.getColumna() + incColumna * i);
							//posicions[nPosicions] = tmpPos1;
							//nPosicions++;
						//}
						//else {
						if(m_tauler[posicioActual.getFila() + incFila * i][posicioActual.getColumna() + incColumna * i].getTipusFitxa() != TIPUS_EMPTY){
							
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
									//Posicio tmpP(posicioActual.getFila() + (incFila * i), posicioActual.getColumna() + (incColumna * i));
									//Posicio tmpP3(posicioActual.getFila() + (incFila * i) + incFila, posicioActual.getColumna() + (incColumna * i) + incColumna);
									
									Posicio tmpPos1(posicioActual.getFila() + incFila * i, posicioActual.getColumna() + incColumna * i);
									//posicions[nPosicions] = tmpPos1;
									//nPosicions++;
									
									Posicio tmpPos2(posicioActual.getFila() + (incFila * i) + incFila, posicioActual.getColumna() + (incColumna * i) + incColumna);
									posicions[0] = posicioActual;
									posicions[1] = tmpPos2;
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
					Moviment mov(DAMA_MATAR, posicions, 2, 1, morts);
					movimentsValids[nMovimentsValids] = mov;
					nMovimentsValids++;
				}
			}
		}
	}
	return matada;
}



bool Tauler::damaMatarMultiples(Posicio posicioActual, Moviment movimentsValids[MAX_MOVIMENTS], int& nMovimentsValids)const {
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
			Moviment mv[MAX_MOVIMENTS] = {};
			int nMv = 0;

			if (m_tauler[fila][col].getTipusFitxa() == TIPUS_NORMAL)
			{
				Posicio pos(fila, col);

				normalMoure(pos, mv, nMv);

				if (normalMatar(pos, mv, nMv)) {
					cout << "ES POT NORMALMATASR";
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
						cout <<endl<< "Dama Matar Multiples"<<endl;
						//damaMatarMultiples(pos, mv, nMv);
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

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[MAX_POSICIONS])
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

bool Tauler::bufar(const Posicio& posicioOrigen,Moviment& movimentFet) {
	int maxIndex=-1;
	int maxMorts=-1;


	


	//busquem el moviment de màximes fitxes
	for (int i = 0;i < m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getNMoviments();i++) {
		//DBG
		for (int k = 0;k < m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(i).getNPosicions();k++) {
			cout << "tipus de mov: "<< m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(i).getTipus() <<":  "<< m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(i).getPosicioPos(k) << "- kills: " << m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(i).getNMorts()<< ". " << endl;
		}

		//
		Moviment moviment = m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(i);
		if (moviment.getTipus() != NORMAL_NO_MATAR) {
			if (moviment.getNMorts() > maxMorts) {
				maxIndex = i;
				maxMorts = moviment.getNMorts();
				cout << endl << "maxMorts::: " << maxMorts << endl << "..";
			}
		}
	}
	//Si durant algun moviment es mata::
	if (maxIndex > -1) {
		cout << endl << "el moviment amb mes kills era:" << m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(maxIndex).getTipus() << "amb morts: " << m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(maxIndex).getNMorts() << endl;
		if ((movimentFet.getNMorts() < m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(maxIndex).getNMorts())) {
			//DBG
			cout << endl << "La fitxa en posicio " << posicioOrigen.toString() << " ha estat bufada. El seu moviment de màximes kills era:" << endl;
			//for(int i=0;i<m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(maxIndex).)
			cout << endl << "de tipus: " << m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(maxIndex).getTipus() << "amb n de kills: " << m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].getMovimentPos(maxIndex).getNMorts() << endl;
			//
			m_tauler[posicioOrigen.getFila()][posicioOrigen.getColumna()].setViva(false);
			return true;
		}
		else {
			return false;
		}

	}
	return false;
	
	
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
		Posicio posicionsPossibles[MAX_POSICIONS];
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




bool Tauler::mouFitxa(const Posicio& origen,const Posicio& desti)//Lit que origen no fot res.
{

	

	//Ara trobar el moviment que s'ha fet dins de la llista de moviments valids de la fitxa. 
	bool trobat = false;
	int i = 0;
	Moviment movimentFet;
	

	while ((i < m_tauler[origen.getFila()][origen.getColumna()].getNMoviments()) && (!trobat)) {		
		if (m_tauler[origen.getFila()][origen.getColumna()].getMovimentPos(i).getPosicioPos(m_tauler[origen.getFila()][origen.getColumna()].getMovimentPos(i).getNPosicions()-1) == desti) {
			movimentFet = m_tauler[origen.getFila()][origen.getColumna()].getMovimentPos(i);
			trobat = true;

			m_tauler[desti.getFila()][desti.getColumna()] = m_tauler[origen.getFila()][origen.getColumna()];//ho copio tot



			m_tauler[desti.getFila()][desti.getColumna()].setViva(true);
			m_tauler[desti.getFila()][desti.getColumna()].setPosicio(desti);



			m_tauler[origen.getFila()][origen.getColumna()].setColorITipusFitxa('_');//Fitxa buida



			//
			m_filaFitxaSeleccionada = desti.getFila();//Mes facil. Aixi despres puc bufar i tota la pesca.
			m_colFitxaSeleccionada = desti.getColumna();
			//
			
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
		convertirADama();
		bufar(desti,movimentFet);
		eliminarFitxesMortes();
		
		

	}
	return trobat;
}



string Tauler::toString() const
{
	char taulerEnChars[N_FILES][N_COLUMNES];
	for (int i = 0;i < N_FILES;i++) {
		for (int j = 0;j < N_COLUMNES;j++) {
			if ((m_tauler[i][j].getColorFitxa() == COLOR_UNDEFINED) && (m_tauler[i][j].getTipusFitxa() == TIPUS_EMPTY)) {
				taulerEnChars[i][j] = '_';
			}
			else {
				if ((m_tauler[i][j].getColorFitxa() == COLOR_BLANC) && (m_tauler[i][j].getTipusFitxa() == TIPUS_NORMAL)) {
					taulerEnChars[i][j] = 'O';
				}
				else {
					if ((m_tauler[i][j].getColorFitxa() == COLOR_NEGRE) && (m_tauler[i][j].getTipusFitxa() == TIPUS_NORMAL)) {
						taulerEnChars[i][j] = 'X';
					}
					else {
						if ((m_tauler[i][j].getColorFitxa() == COLOR_BLANC) && (m_tauler[i][j].getTipusFitxa() == TIPUS_DAMA)) {
							taulerEnChars[i][j] = 'D';
						}
						else {
							if ((m_tauler[i][j].getColorFitxa() == COLOR_NEGRE) && (m_tauler[i][j].getTipusFitxa() == TIPUS_DAMA)) {
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