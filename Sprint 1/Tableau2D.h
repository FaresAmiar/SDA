#include <iostream>
#include "Item.h"

struct Tab2D {
	Item** tab; // adresse du tableau bidimensionnel en mémoire dynamique

	int nbL; //	nombre de ligne de la matrice
	int nbC; //nombre de colonnes de la matrice
};

void initialiser(Tab2D& m, int nbL, int nbC); // Allouer en mémoire dynamique un Tableau2D
void lire(Tab2D& m);
void afficher(const Tab2D& m);
void detruire(Tab2D& m);
