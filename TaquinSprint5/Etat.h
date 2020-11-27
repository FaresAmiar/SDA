/**
* @author : Amiar Fares / Chen Richard
* @file : Etat.h
* @version : Sprint 5
*/

#include "Tableau2D.h"
#include <iostream>

/**
* Structure d'un �tat d'un damier
*/
struct Etat
{
	//damier courant de l'�tat
	Tab2D *damier = NULL;

	//Mouvement possible : �tat initial est fixe
	enum Mouvement { FIXE, NORD, EST, OUEST, SUD };
	
	Mouvement mouv;

	// Etat pr�c�dent qqui a amen� � l'�tat actuel
	Etat *etatPrecedent;

	// Pas pour arriver d'un �tat � un autre
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
* @brief Cr�er l��tat initial
* @param e : �tat � initialiser 
*/
void initialiser(Etat& e);

/**
* @brief D�truire en m�moire l'�tat
* @param e : �tat � d�truire
*/
void detruire(Etat& e);
