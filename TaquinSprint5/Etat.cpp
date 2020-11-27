/**
* @author : Amiar Fares / Chen Richard
* @file : Etat.cpp
* @version : Sprint 5
*/

#include "Etat.h"
#include <iostream>



/**
* @brief Créer l’état initial
* @param e : état à initialiser
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
* @brief Détruire en mémoire l'état
* @param e : état à détruire
*/
void detruire(Etat& e) {
	delete[] & e.damier;
	delete &e;
}