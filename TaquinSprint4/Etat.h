#include "Tableau2D.h"
#include <iostream>


struct Etat
{
	Tab2D *damier = NULL;

	enum Mouvement { FIXE, NORD, EST, OUEST, SUD };
	Mouvement mouv;

	Etat *etatPrecedent;

	unsigned int g = 0;
	unsigned int h = 0;
	unsigned int f = 0;

	unsigned int colVide = 0;
	unsigned int lnVide = 0;
	Tab2D *etatFinaux = NULL;
};




// Créer l’état initial
void initialiser(Etat& e);

// Détruire en mémoire l'état
void detruire(Etat& e);
