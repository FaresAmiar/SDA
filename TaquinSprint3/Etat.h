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




// Créer le jeu de taquin avec l’état initial
void initialiser(Etat& e);
// Itération de l’algorithme de recherche
void lire(Etat& e);
// Afficher le contenu des listes adev et dev
void detruire(Etat& e);
