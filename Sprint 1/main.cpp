#include <iostream>
#include <cstdio>
#include "Item.h"
#include "Tableau2D.h"
using namespace std;


int main() {
	Tab2D m;

	int &nbL = m.nbL;
	int &nbC = m.nbC;

	cin >> nbL;
	cin >> nbC;
	cout << "Damier :" << nbL << " Lignes, " << nbC << " Colonnes" << endl;

	initialiser(m, nbL, nbC);

	lire(m);

	afficher(m);

	detruire(m);

	system("pause");
	return 0;
}