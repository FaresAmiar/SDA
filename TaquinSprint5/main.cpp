/**
* @author : Amiar Fares / Chen Richard
* @file : main.cpp
* @version : Sprint 5
*/

#include <iostream>

#include "Taquin.h"

using namespace std;

/**
* @brief Programme principal du resolveur de taquin
* @return 0 pour fin du programme
*/
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

	// le taquin a une solution
	if (solutionTrouvee) {
	
		//memoriserSolution
		Etat *etatFinal = recupererEtatFinal(&t.lee);
		t.nbMvtSolution = etatFinal->g;

		t.solution = memoriserSolution(etatFinal, t);

		afficherSolution(t);
	}
	else {
		cout << "Pas de solution au taquin" << endl;
	}

	/* Vider la mémoire une fois la fin du programme*/
	detruire(m);
	detruire(t);

	return 0;
}