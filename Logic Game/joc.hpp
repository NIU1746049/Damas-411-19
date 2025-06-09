#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "info_joc.hpp"
#include "tauler.hpp"

using namespace std;

typedef enum
{
    PANTALLA_MENU,
    PANTALLA_JOC,
    PANTALLA_REPLAY,
    PANTALLA_VICT_BLANQUES,
    PANTALLA_VICT_NEGRES

}Pantalla;

class Joc 
{

public:
    Joc() { m_fitxaSeleccionada = false; m_mouseStatusAnterior = false; m_columnaRatoli = 0; m_filaRatoli = 0; m_pantalla = PANTALLA_MENU; };
    
    void inicialitza(const string nomFitxer);
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    void visualitzaJoc(int zeroDeX, int zeroDeY, int ampladaX, int alcadaY);
    
private:
    Tauler m_tauler;
    bool m_fitxaSeleccionada;
    int m_colFitxaSeleccionada;
    int m_filaFitxaSeleccionada;

    bool m_mouseStatusAnterior;
    int m_columnaRatoli;
    int m_filaRatoli;

    Pantalla m_pantalla;
};

#endif 
