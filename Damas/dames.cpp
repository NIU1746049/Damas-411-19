#include "dames.h"


int main()
{
	Tauler tauler;

	tauler.inicialitza("dames_input.txt");
	cout << tauler.toString();
}


//TAREAS
//-Pagina 28 pdf, punto 3: 
// Penseu quins atributs i m�todes us poden fer falta a la classe Moviment. Feu la declaraci� de la classe 
// (no cal que implementeu els m�todes, de moment)
//
//-Moviments lo ponemos en la clase Fitxa o en la clase Tauler? 
// 
//-Programar inicializacion tablero cuando el argumento es null
//
//-Pagina 28 pdf, punto 5:
// Penseu com podeu descomposar el codi del m�tode actualitzaMovimentsValids amb funcions m�s petites i simples.
// Penseu b� com podeu organitzar el codi del m�tode per poder implementar de la forma m�s simple possible i evitant duplicitats, 
// el codi per recuperar qualsevol tipus de moviment v�lid per cada qualsevol tipus de pe�a de qualsevol color
//
//