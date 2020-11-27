/**
* @author : Amiar Fares / Chen Richard
* @file : Tableau2D.cpp
* @version : Sprint 5
*/

#include <iostream>
#include "Item.h"
#include "Tableau2D.h"
using namespace std;


/**
* @brief Initialiser le damier : Allouer en mémoire dynamique un Tableau2D
* @param m Matrice
* @param nbL nombre de lignes du damier
* @param nbL nombre de colonnes du damier
*/
void initialiser(Tab2D& m, int nbL, int nbC) {

	/*Allocation en mémoire dynamique */
	m.tab = new Item*[nbL];
	for (int i = 0; i < nbL; i++) {
		m.tab[i] = new Item[nbC];
	}

}

/**
* @brief Lecture des cases du damier
* @param m Matrice
*/
void lire(Tab2D& m) {

	char remplir[10];
	for (int i = 0; i < m.nbL; i++) {
		for (int k = 0; k < m.nbC; k++) {
			cin >> remplir;
			if (0 == strcmp(remplir, "#")) {
				m.colVide = i;
				m.lnVide = k;
			}
			m.tab[i][k] = atoi(remplir);
		}
	}
}

/**
* @brief Afficher le contenu du damier
* @param m Matrice
*/
void afficher(const Tab2D& m) {

	for (int i = 0; i < m.nbL; i++) {
		for (int k = 0; k < m.nbC; k++) {

			if (m.tab[i][k] == 0) {
				cout << "  #";
			}
			else {
				if (m.tab[i][k] < 10)
					cout << "  " << m.tab[i][k];
				else
					cout << " " << m.tab[i][k];
			}

			if (k == m.nbC - 1) cout << endl;
		}

	}
}

/**
* @brief Détruire le damier
* @param m Matrice
*/
void detruire(Tab2D& m) {

	for (int i = 0; i < m.nbL; i++)
		delete[] m.tab[i];
	delete[] m.tab;
}