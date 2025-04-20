#include "dames.h"



/*
int main()
{
	Tauler tauler;

	tauler.inicialitza("dames_input.txt");
	cout << tauler.toString();

}*/
int main() {
	Tauler tauler;
	bool partidaAcabada = false;
	bool jugantElBlanc = true;
	tauler.inicialitza("dames_input.txt");

	while (!partidaAcabada) {
		partidaAcabada = tauler.gameOver();
		tauler.seleccionaFitxa(jugantElBlanc)

		
		tauler.bufar();
		tauler.eliminarFitxesMortes();
		tauler.convertirADama();
		jugantElBlanc = false;

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