#include "Etat.h"
#include <iostream>



// Créer le jeu de taquin avec l’état initial
void initialiser(Etat& e) {
	e.colVide = e.damier->colVide;
	e.lnVide = e.damier->lnVide;
	e.mouv = e.FIXE;
	e.g = 0;
	e.h = 0;
	//e.h = e.damier->nbC; //a partir du sprint 4
	e.f = e.g + e.h;
	e.etatPrecedent = &e;
}

// Détruire en mémoire l'état
void detruire(Etat& e) {
	delete[] & e.damier;
	delete &e;
}