#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "info_joc.hpp"
#include "tauler.hpp"

using namespace std;


class Joc 
{

public:
    Joc() { m_filaPeca = 0; m_columnaPeca = 0; m_mouseStatusAnterior = false; m_dibuixaFitxa = false; m_columnaRatoli = 0; m_filaRatoli = 0; };
    
    void inicialitza(const string nomFitxer);
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    
    
private:
    Tauler tauler;
    bool m_mouseStatusAnterior;

    int m_filaPeca;
    int m_columnaPeca;

    bool m_dibuixaFitxa;
    int m_columnaRatoli;
    int m_filaRatoli;
};

#endif 
