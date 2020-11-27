#include "Etat.h"
#include <iostream>



// Cr�er le jeu de taquin avec l��tat initial
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

// D�truire en m�moire l'�tat
void detruire(Etat& e) {
	delete[] & e.damier;
	delete &e;
}