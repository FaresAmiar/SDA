#include <iostream>
#include <cstdio>

#include "Taquin.h"

using namespace std;


int main() {

	Tab2D m;
	Taquin t;

	bool solutionTrouvee = false;

	int &nbL = m.nbL;
	int &nbC = m.nbC;
	// lire le contenu du damier
	cin >> nbL;
	cin >> nbC;
	cout << "Damier : " << nbL << " lignes, " << nbC << " colonnes" << endl;

	t.nbC = m.nbC;
	t.nbL = m.nbL;
	t.damier = &m;

	// initialiser le damier
	initialiser(m, nbL, nbC);
	lire(m);

	// initialiser le taquin
	initialiser(t);

	//résoudre le taquin et vérifier si une solution est trouvée
	solutionTrouvee = jouer(t);

	// pas de solution trouvée donc affichage du message
	if (!solutionTrouvee) {
		cout << "Pas de solution au taquin" << endl;
	}

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

	/* Vider la mémoire une fois la fin du programme*/
	detruire(m);
	detruire(t);

	//system("pause");
	return 0;
}