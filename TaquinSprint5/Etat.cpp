/**
* @author : Amiar Fares / Chen Richard
* @file : Etat.cpp
* @version : Sprint 5
*/

#include "Etat.h"
#include <iostream>



/**
* @brief Cr�er l��tat initial
* @param e : �tat � initialiser
*/
void initialiser(Etat& e) {
	e.colVide = e.damier->colVide;
	e.lnVide = e.damier->lnVide;
	e.mouv = e.FIXE;
	e.g = 0;
	e.h = 0;
	e.f = e.g + e.h;
	e.etatPrecedent = NULL;
}

/**
* @brief D�truire en m�moire l'�tat
* @param e : �tat � d�truire
*/
void detruire(Etat& e) {
	delete[] & e.damier;
	delete &e;
}