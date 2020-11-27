/**
* @author : Amiar Fares / Chen Richard
* @file : Etat.h
* @version : Sprint 5
*/

#include "Tableau2D.h"
#include <iostream>

/**
* Structure d'un état d'un damier
*/
struct Etat
{
	//damier courant de l'état
	Tab2D *damier = NULL;

	//Mouvement possible : état initial est fixe
	enum Mouvement { FIXE, NORD, EST, OUEST, SUD };
	
	Mouvement mouv;

	// Etat précédent qqui a amené à l'état actuel
	Etat *etatPrecedent;

	// Pas pour arriver d'un état à un autre
	unsigned int g = 0;
	// Heuristique
	unsigned int h = 0;
	//Heuristique de recherche
	unsigned int f = 0;

	//Position de la colonne de la case vide dans le damier
	unsigned int colVide = 0;
	//Position de la ligne de la case vide dans le damier
	unsigned int lnVide = 0;
	//Un tableau de damier correspondant aux solutions finales
	Tab2D *etatFinaux = NULL;
};




/**
* @brief Créer l’état initial
* @param e : état à initialiser 
*/
void initialiser(Etat& e);

/**
* @brief Détruire en mémoire l'état
* @param e : état à détruire
*/
void detruire(Etat& e);
