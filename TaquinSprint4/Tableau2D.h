#include <iostream>
#include "Item.h"

struct Tab2D {
	Item** tab; // adresse du tableau bidimensionnel en m�moire dynamique

	int lnVide = 0;
	int colVide = 0;

	int nbL = 0; //	nombre de ligne de la matrice
	int nbC = 0; //nombre de colonnes de la matrice
};

/*Initialiser le damier*/
void initialiser(Tab2D& m, int nbL, int nbC); // Allouer en m�moire dynamique un Tableau2D
/*Lecture des cases du damier*/
void lire(Tab2D& m);
/*Afficher le contenu du damier*/
void afficher(const Tab2D& m);
/*D�truire le damier*/
void detruire(Tab2D& m);