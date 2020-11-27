/**
* @author : Amiar Fares / Chen Richard
* @file : Tableau2D.h
* @version : Sprint 5
*/

#include <iostream>
#include "Item.h"

/** 
* Structure du tableau bidimensionnel
*/
struct Tab2D {
	// adresse du tableau bidimensionnel en mémoire dynamique
	Item** tab; 

	int lnVide = 0;
	int colVide = 0;
	//	nombre de ligne de la matrice
	int nbL = 0; 
	//nombre de colonnes de la matrice
	int nbC = 0; 
};

/** 
* @brief Initialiser le damier : Allouer en mémoire dynamique un Tableau2D
* @param m Matrice 
* @param nbL nombre de lignes du damier
* @param nbL nombre de colonnes du damier
*/
void initialiser(Tab2D& m, int nbL, int nbC);

/**
* @brief Lecture des cases du damier
* @param m Matrice
*/
void lire(Tab2D& m);

/**
* @brief Afficher le contenu du damier
* @param m Matrice
*/
void afficher(const Tab2D& m);

/**
* @brief Détruire le damier
* @param m Matrice
*/
void detruire(Tab2D& m);