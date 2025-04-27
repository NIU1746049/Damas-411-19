#include "dames.h"

/*
int main()
{
	Tauler tauler;

	tauler.inicialitza("dames_input.txt");
	cout << tauler.toString() << endl;

	cout << "Numero Blanques: " << tauler.getNBlanques() << endl;
	cout << "Numero Negres: " << tauler.getNBlanques() << endl;
}
*/

int main()
{
	Tauler tauler;
	tauler.inicialitza("dames_input.txt");
	bool gameOver = false;
	tauler.setTornBlanques(true);


	while (!gameOver) {
		tauler.actualitzaTaulerEnChars();
		cout << tauler.toString()<<endl;
		if (tauler.getTornBlanques()) {
			cout <<endl<< "Torn de les blanques..."<<endl;
		}
		else {
			cout << endl<<"Torn de les negres..." << endl;
		}

		gameOver = tauler.gameOver();


		bool seleccioValida = tauler.seleccionaFitxa();

		while (!seleccioValida) {
			cout << endl << "seleccio invalida... Torna a escollir." << endl;
			seleccioValida = tauler.seleccionaFitxa();
		}
		tauler.actualitzaMovimentsValids();//actualitzara els moviments valids de la fitxa seleccionada
		
		
		Posicio posDesti;
		seleccioValida = tauler.seleccionaDesti(posDesti);
		while (!seleccioValida) {
			cout << endl << "seleccio invalida... Torna a escollir." << endl;
			seleccioValida = tauler.seleccionaDesti(posDesti);
		}
		
		
		tauler.mouFitxa(posDesti);//Capçalera canviada
		//tauler.bufar();
		tauler.eliminarFitxesMortes();
		tauler.convertirADama();
		tauler.setTornBlanques(!tauler.getTornBlanques());


	}
}




//TAREAS
//Hug:
// -actualitzarMovimentsValids (amb subfuincions)
// -Bufar
// -bucle principal (main)
// 
//Abel:
// -convertirADama
// -eliminarFitxesMortes
// -gameOver
//


//fixes (hug):
//seleccio de peces