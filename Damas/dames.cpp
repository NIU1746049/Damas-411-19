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
	bool gameOver = true;
	tauler.setTornBlanques(true);


	while (!gameOver) {
		tauler.toString();
		gameOver = tauler.gameOver();


		bool seleccioValida = tauler.seleccionaFitxa();

		while (!seleccioValida) {
			cout << endl << "seleccio invàlida... Torna a escollir." << endl;
			seleccioValida = tauler.seleccionaFitxa();
		}

		tauler.actualitzaMovimentsValids();//actualitzara els moviments valids de la fitxa seleccionada

		Posicio posDesti;
		seleccioValida = tauler.seleccionaDesti(posDesti);
		while (!seleccioValida) {
			cout << endl << "seleccio invàlida... Torna a escollir." << endl;
			seleccioValida = tauler.seleccionaDesti(posDesti);
		}
		
		
		tauler.mouFitxa(posDesti);//Capçalera canviada
		tauler.bufar();
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
