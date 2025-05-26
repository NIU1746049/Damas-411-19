# Damas-411-19
Abel i Hug, 411-19.



Primerament, Tauler és la classe central. Dins de Tauler tenim tots els mètodes centrals del joc (com mouFitxa, getPosicionsPossibles...).
Implementada com una matriu dinàmica de punters a objectes Fitxa, tenim m_tauler. 





Tauler es la classe central.

Dins de tauler tens una matriu de fitxes. Cada fitxa té un objecte de posició i un array de movimentsValids.

actualitzarMovimentsValids itera per totes les posicions de l'array de fitxes de tauler i comprova quins moviments són viables 
per les fitxes que no corresponguin a una casella vuida, sense fitxa (TipusFitxa = EMPTY). Comprova 6 tipus de moviments: normalMoure, 
normalMatar, normalMatarMultiples, damaMoure...

Primer mira si es dama o normal, comprova si es pot moure sense matar i matant a la dreta i a l'esquerra, i en cas que pugui matar, 
comprova si pot matar múltiples vegades. Cada funció de comprovar un tipus de moviment retorna un bool per saber si es viable o no. Internament, 
dins de cada funció que retorni true també vol dir que s'ha afegit un moviment nou a l'array de moviments viables de dins de la fitxa i se nha incrementat el contador. 




