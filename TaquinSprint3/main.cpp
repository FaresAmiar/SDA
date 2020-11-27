#include <iostream>

#include "Taquin.h"

using namespace std;


int main() {

	Tab2D m;
	Taquin t;

	bool solutionTrouvee = false;

	int &nbL = m.nbL;
	int &nbC = m.nbC;

	cin >> nbL;
	cin >> nbC;
	cout << "Damier : " << nbL << " Lignes, " << nbC << " Colonnes" << endl;

	t.nbC = m.nbC;
	t.nbL = m.nbL;
	t.damier = &m;

	initialiser(m, nbL, nbC);
	lire(m);

	initialiser(t);

	solutionTrouvee = jouer(t);

	/*if (!solutionTrouvee) {
		cout << "Pas de solution au taquin" << endl;
	}*/

	// a partir du sprint 5
	/*
	if (solutionTrouvee) {

	//memoriserSolution(t);
	Etat *etatFinal = depiler(&t.lee);

	t.solution = new Etat[etatFinal->g + 1];

	while (etatFinal->mouv != etatFinal->FIXE) {
	t.nbMvtSolution = etatFinal->g;
	t.solution[etatFinal->g] = *etatFinal;
	etatFinal = etatFinal->etatPrecedent;
	}

	afficherSolution(t);
	}
	else {
	cout << "Pas de solution au taquin" << endl;
	}*/

	detruire(m);
	detruire(t);

	return 0;
}