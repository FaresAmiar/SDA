#include <iostream>
#include "Item.h"
#include "Tableau2D.h"
using namespace std;

void initialiser(Tab2D& m, int nbL, int nbC); // Allouer en mémoire dynamique un Tableau2D
void detruire(Tab2D& m); // Desallouer un Tableau2D
void lire(Tab2D& m); // Lire un Tableau2D
void afficher(const Tab2D& m); // Afficher un Tableau2D

void initialiser(Tab2D& m, int nbL, int nbC) {

	/*Allocation en mémoire dynamique */
	m.tab = new Item*[nbL];
	for (int i = 0; i < nbL; i++) {
		m.tab[i] = new Item[nbC];
	}

}

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

void detruire(Tab2D& m) {

	for (int i = 0; i < m.nbL; i++)
		delete[] m.tab[i];
	delete[] m.tab;
}