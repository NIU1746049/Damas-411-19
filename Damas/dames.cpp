#include "dames.h"

/*
int main()
{
	Tauler tauler;

	tauler.inicialitza("dames_input.txt");
	cout << tauler.toString();
}*/


int main()
{
	Tauler tauler;
	bool gameOver = true;
	tauler.setTornBlanques(true);
	while (!gameOver) {
		gameOver = tauler.gameOver();


		bool seleccioValida = tauler.seleccionaFitxa();

		while (!seleccioValida) {
			seleccioValida = tauler.seleccionaFitxa();
		}



		tauler.actualitzaMovimentsValids();//actualitzara els moviments valids de la fitxa seleccionada


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
