#include "dames.h"


int main()
{
	Tauler tauler;

	tauler.inicialitza("dames_input.txt");
	cout << tauler.toString();
}


//TAREAS
//-Pagina 28 pdf, punto 3: 
// Penseu quins atributs i mètodes us poden fer falta a la classe Moviment. Feu la declaració de la classe 
// (no cal que implementeu els mètodes, de moment)
//
//-Moviments lo ponemos en la clase Fitxa o en la clase Tauler? 
//
//-Pagina 28 pdf, punto 5:
// Penseu com podeu descomposar el codi del mètode actualitzaMovimentsValids amb funcions més petites i simples.
// Penseu bé com podeu organitzar el codi del mètode per poder implementar de la forma més simple possible i evitant duplicitats, 
// el codi per recuperar qualsevol tipus de moviment vàlid per cada qualsevol tipus de peça de qualsevol color
//
//