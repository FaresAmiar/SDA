#include "Taquin.h"
#include <iostream>
using namespace std;


// Afficher un état du taquin
void afficher(const Etat& e)
{
	if (e.mouv == e.NORD) cout << "NORD" << endl;
	if (e.mouv == e.SUD) cout << "SUD" << endl;
	if (e.mouv == e.EST) cout << "EST" << endl;
	if (e.mouv == e.OUEST) cout << "OUEST" << endl;

	afficher(*e.damier);

	cout << "f=g+h=" << e.g << "+" << e.h << "=" << e.f << endl;
}

// Créer le jeu de taquin avec l’état initial
void initialiser(Taquin& t)
{
	int nbL = t.nbL;
	int nbC = t.nbC;

	t.etatFinaux = new Tab2D[nbC];


	Item **tab = new Item*[nbL];
	for (int i = 0; i < nbL; i++)
	{
		tab[i] = new Item[nbC];
	}

	int cptr = 0;
	for (int i = 0; i < nbL; i++)
	{
		for (int k = 0; k < nbC; k++)
		{
			cptr++;
			if (cptr == (nbL*nbC))
			{
				cptr = 0;
				t.etatFinaux[0].colVide = k;
				t.etatFinaux[0].lnVide = i;
			}
			tab[i][k] = cptr;
		}
	}

	t.etatFinaux[0].tab = tab;
	t.etatFinaux[0].nbC = nbC;
	t.etatFinaux[0].nbL = nbL;


	for (int itab = 1; itab < nbC; ++itab)
	{
		Item ** tab2 = new Item*[nbL];
		for (int itab2 = 0; itab2 < nbL; itab2++) {
			tab2[itab2] = new Item[nbC];
		}

		for (int l = 0; l < nbL; l++) {
			for (int k = 0; k < nbC; k++) {
				tab2[l][k] = tab[l][k];
			}
		}

		tab = tab2;

		int casetmp = 0;
		for (int i = 0; i < nbL; i++)
		{
			for (int k = 0; k < nbC; k++)
			{
				casetmp = tab[i][k];

				if (k + 1 < nbC)
				{

					if (casetmp == 0)
					{
						t.etatFinaux[itab].colVide = k + 1;
						t.etatFinaux[itab].lnVide = i;
					}

					tab[i][k] = tab[i][k + 1];
					tab[i][k + 1] = casetmp;


				}
			}
		}

		t.etatFinaux[itab].tab = tab;
		t.etatFinaux[itab].nbC = nbC;
		t.etatFinaux[itab].nbL = nbL;

	}

}

/*  Ajout d'un état en fin de liste. */
void PushBack(Liste *l, Etat *nvEtat)
{
	Chainon *nouv = new Chainon;
	if (!nouv) exit(EXIT_FAILURE);
	nouv->etat = nvEtat;
	nouv->precedent = l->dernier;
	nouv->suivant = NULL;
	if (l->dernier) l->dernier->suivant = nouv;
	else l->premier = nouv;
	l->dernier = nouv;
	l->nb++;
}

/*  Ajout d'un état en début de liste. */
void PushFront(Liste *l, Etat *nvEtat)
{
	Chainon *nouv = new Chainon;
	if (!nouv) exit(EXIT_FAILURE);
	nouv->etat = nvEtat;
	nouv->suivant = l->premier;
	nouv->precedent = NULL;
	if (l->premier) l->premier->precedent = nouv;
	else l->dernier = nouv;
	l->premier = nouv;
	l->nb++;
}

/*  Retrait d'un état en fin de liste. */
Etat * PopBack(Liste *l)
{

	Etat * val;
	Chainon *tmp = l->dernier;
	if (!tmp) return NULL;
	val = tmp->etat;
	l->dernier = tmp->precedent;
	if (l->dernier) l->dernier->suivant = NULL;
	else l->premier = NULL;
	l->nb--;
	delete(tmp);
	return val;
}

/*  Retrait d'une état en début de liste. */
Etat * PopFront(Liste *l)
{

	Etat * val;
	Chainon *tmp = l->premier;
	if (!tmp) return NULL;
	val = tmp->etat;
	l->premier = tmp->suivant;
	if (l->premier)l->premier->precedent = NULL;
	else l->dernier = NULL;
	l->nb--;
	delete(tmp);
	return val;
}

/* Enlever un état en entrée dans la liste chainée */
Etat * PopEtat(Liste *liste, Etat * etat)
{
	Etat * etatPop = NULL;
	if (liste != NULL)
	{
		Chainon *chainonTemp = liste->premier;
		int found = 0;
		while (chainonTemp != NULL && !found)
		{
			if (chainonTemp->etat == etat)
			{
				if (chainonTemp->suivant == NULL && chainonTemp->precedent != NULL)
				{
					liste->dernier = chainonTemp->precedent;
					if (liste->dernier != NULL)
						liste->dernier->suivant = NULL;
				}
				else if (chainonTemp->precedent == NULL && chainonTemp->suivant != NULL)
				{
					liste->premier = chainonTemp->suivant;
					if (liste->premier != NULL)
						liste->premier->precedent = NULL;
				}
				else if (chainonTemp->precedent == NULL && chainonTemp->suivant == NULL)
				{
					liste->premier = chainonTemp->suivant;
					if (liste->premier != NULL)
						liste->premier->precedent = NULL;
					liste->dernier = chainonTemp->precedent;
					if (liste->dernier != NULL)
						liste->dernier->suivant = NULL;
				}
				else
				{
					chainonTemp->suivant->precedent = chainonTemp->precedent;
					chainonTemp->precedent->suivant = chainonTemp->suivant;
				}

				etatPop = chainonTemp->etat;
				delete(chainonTemp);
				liste->nb--;
				found = 1;

			}
			else
			{
				chainonTemp = chainonTemp->suivant;
			}
		}
	}
	return etatPop;
}

/* Enlever de la liste un état à une position en entrée*/
Etat * PopPosition(Liste *liste, int pos)
{
	int i;
	Chainon *supp_element, *courant;
	Etat * etatRetour = NULL;

	if (liste->nb == 0)
		return NULL;

	if (pos == 1) { // suppresion de 1er élément
		supp_element = liste->premier;
		liste->premier = liste->premier->suivant;
		if (liste->premier == NULL)
			liste->dernier = NULL;
		else
			liste->premier->precedent = NULL;
	}
	else
		if (pos == liste->nb)
		{
			// suppression du dernier élément
			supp_element = liste->dernier;
			liste->dernier->precedent->suivant = NULL;
			liste->dernier = liste->dernier->precedent;
		}
		else
		{ // suppression ailleurs 
			courant = liste->premier;
			for (i = 1; i < pos; ++i)
				courant = courant->suivant;
			supp_element = courant;
			courant->precedent->suivant = courant->suivant;
			courant->suivant->precedent = courant->precedent;
		}

	etatRetour = supp_element->etat;
	//delete(supp_element->etat);
	delete(supp_element);
	liste->nb--;
	return etatRetour;
}

/* Récupérer le Gmin*/
Etat * minGEtat(Liste *liste)
{
	Etat * minEtat = NULL;

	if (liste != NULL)
	{
		Chainon *chainonTemp = liste->premier;

		while (chainonTemp != NULL)
		{
			if (minEtat == NULL || (minEtat != NULL && minEtat->g > chainonTemp->etat->g))
			{
				minEtat = chainonTemp->etat;
			}

			chainonTemp = chainonTemp->suivant;

		}
	}
	return minEtat;
}

/* Récupérer le fmin avec le hmin */
Etat * minFEtat(Liste *liste)
{
	Etat * minEtat = NULL;

	if (liste != NULL)
	{
		Chainon *chainonTemp = liste->premier;

		while (chainonTemp != NULL)
		{
			if (minEtat == NULL || (minEtat != NULL && minEtat->f > chainonTemp->etat->f))
			{
				minEtat = chainonTemp->etat;
			}

			chainonTemp = chainonTemp->suivant;

		}
	}
	return minEtat;
}

/* Ajouter un état dans la file */
void enfiler(File *file, Etat *nvEtat)
{
	Element *nouveau = new Element;
	if (file == NULL || nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}

	nouveau->etat = nvEtat;
	nouveau->suivant = NULL;

	if (file->premier != NULL) /* La file n'est pas vide */
	{
		/* On se positionne à la fin de la file */
		Element *elementActuel = file->premier;
		while (elementActuel->suivant != NULL)
		{
			elementActuel = elementActuel->suivant;
		}
		elementActuel->suivant = nouveau;
	}
	else /* La file est vide, notre élément est le premier */
	{
		file->premier = nouveau;
	}

	file->nb = file->nb + 1;
}

/* Enlever le premier état de la file */
Etat* defiler(File *file)
{
	if (file == NULL)
	{
		exit(EXIT_FAILURE);
	}

	Etat *etatDefile = NULL;

	/* On vérifie s'il y a quelque chose à défiler */
	if (file->premier != NULL)
	{
		Element *elementDefile = file->premier;

		etatDefile = elementDefile->etat;
		file->premier = elementDefile->suivant;
		delete elementDefile;
		file->nb = file->nb - 1;
	}

	return etatDefile;
}

/* Ajouter un état dans la pile */
void empiler(Pile *pile, Etat *nvEtat)
{
	Element *nouveau = new Element;

	if (pile == NULL || nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}

	nouveau->etat = nvEtat;
	nouveau->suivant = pile->premier;
	pile->premier = nouveau;
	pile->nb = pile->nb + 1;

}

/* Enlever le dernier état de la pile */
Etat* depiler(Pile *pile)
{
	if (pile == NULL)
	{
		exit(EXIT_FAILURE);
	}

	Etat *etatDepile = NULL;
	Element *elementDepile = pile->premier;


	if (pile != NULL && pile->premier != NULL)
	{
		etatDepile = elementDepile->etat;
		pile->premier = elementDepile->suivant;
		delete(elementDepile);
		pile->nb--;
	}

	return etatDepile;
}

/* Enlever un état de la pile */
Etat* depiler(Pile *pile, Etat *adepiler)
{
	if (pile == NULL)
	{
		exit(EXIT_FAILURE);
	}

	Etat *etatDepile = NULL;
	Element *elementDepile = pile->premier;
	int cptr = 0;

	if (pile != NULL && pile->premier != NULL)
	{
		while (elementDepile != NULL)
		{
			etatDepile = elementDepile->etat;
			if (etatDepile == adepiler)
			{

				if (cptr == 0) {
					pile->premier = elementDepile->suivant;
					delete(elementDepile);
				}
				else
				{
					Element *elementADepile = elementDepile;
					elementDepile = elementDepile->suivant;
					delete(elementADepile);
				}


				pile->nb--;
				return etatDepile;
			}
			elementDepile = elementDepile->suivant;
			cptr++;
		}

	}

	return etatDepile;
}

/* Afficher la pile des états */
void afficherPile(Pile *pile)
{
	if (pile == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element *actuel = pile->premier;
	int cp = 0;
	while (actuel != NULL && cp < pile->nb)
	{
		afficher(*actuel->etat);
		actuel = actuel->suivant;
		cp++;
	}

}

/* afficher la liste des états établis */
void afficherFile(File *file)
{
	if (file == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element *actuel = file->premier;
	int cp = 0;
	while (actuel != NULL && cp < file->nb)
	{
		afficher(*actuel->etat);
		actuel = actuel->suivant;
		cp++;
	}

}

/* Afficher la liste */
void afficherListe(Liste l)
{

	Chainon *pelem = l.premier;
	while (pelem)
	{
		afficher(*pelem->etat);
		pelem = pelem->suivant;
	}

}

/* Vérifier si le taquin appartient à la liste des états établis */
bool appartient(const Etat& ef, Taquin& t, File * file) {
	int nbfileparcouru = 0;
	bool appartient = true;
	Element *actuel = file->premier;

	int &nbC = t.nbC;
	int &nbL = t.nbL;

	if (actuel == NULL) return false;

	while (actuel)
	{

		for (int i = 0; i < nbL; i++)
		{
			for (int k = 0; k < nbC; k++)
			{

				if (ef.damier->tab[i][k] != (actuel->etat->damier)->tab[i][k]) {
					appartient = false;
				}

			}
		}

		if (appartient) return appartient;
		actuel = actuel->suivant;

		if (nbfileparcouru >= file->nb) return false;

		nbfileparcouru++;
		appartient = true;
	}


	return false;
}

/* Vérifier si le taquin appartient à la liste des états à établir */
bool appartient(const Etat& ef, Taquin& t, Liste * file) {
	int nbfileparcouru = 0;
	bool appartient = true;
	Chainon *actuel = file->premier;

	int &nbC = t.nbC;
	int &nbL = t.nbL;

	if (actuel == NULL) return false;

	while (actuel)
	{

		for (int i = 0; i < nbL; i++)
		{
			for (int k = 0; k < nbC; k++)
			{

				if (ef.damier->tab[i][k] != (actuel->etat->damier)->tab[i][k]) {
					appartient = false;
				}

			}
		}

		if (appartient) return appartient;
		actuel = actuel->suivant;

		if (nbfileparcouru >= file->nb) return false;

		nbfileparcouru++;
		appartient = true;
	}


	return false;
}

// renvoie vrai si l‘état existe déjà dans le taquin
bool appartient(const Etat& ef, Taquin& t)
{

	if (&ef == NULL || &ef.damier == NULL) return false;

	return appartient(ef, t, &t.leae) || appartient(ef, t, &t.lee);
}

// renvoie vrai s’il s’agir de l’état final, faux sinon
bool but(const Etat& e)
{
	int nbC = e.damier->nbC;
	int nbL = e.damier->nbL;
	bool but = false;

	for (int itab = 0; itab < nbC; ++itab)
	{
		but = true;
		Tab2D etatFinal = e.etatFinaux[itab];
		Item ** tab = etatFinal.tab;

		for (int i = 0; i < nbL; i++)
		{
			for (int k = 0; k < nbC; k++)
			{
				if (e.damier->tab[i][k] != tab[i][k])
				{
					but = false;
				}
			}
		}

		if (but) return true;
	}
	return but;
}

/* Calculer la distance de Manhattan */
unsigned int distanceManhattan(const Position p1, const Position p2)
{
	return (p1.ligne - p2.ligne)*(p1.ligne - p2.ligne) + (p1.colonne - p2.colonne)*(p1.colonne - p2.colonne);
}

/* Retrouver où se trouve la position Finale */
Position localiserPositionFinale(unsigned int valeur, const Tab2D &etatFini)
{
	Position point; point.colonne = 0; point.ligne = 0;

	for (int i = 0; i < etatFini.nbL; ++i)
	{
		for (int j = 0; j < etatFini.nbC; ++j)
		{

			if (etatFini.tab[i][j] == valeur)
			{

				point.ligne = i;
				point.colonne = j;
				return point;
			}
		}
	}
	return point;
}

// une case mal placée = +distance de manathan à la destination d'heuristique
unsigned int heuristiqueManathan(const Tab2D &jeu, const Tab2D &etatFini)
{
	unsigned int k = 0;

	for (int i = 0; i < jeu.nbL; ++i)
	{
		for (int j = 0; j < jeu.nbC; ++j)
		{
			Position point; point.ligne = i; point.colonne = j;
			k += distanceManhattan(point, localiserPositionFinale(jeu.tab[i][j], etatFini));

		}
	}
	return k;
}

// heuristique pour calculer h
unsigned int heuristique(const Etat &t)
{
	unsigned int h = 1;
	/*unsigned int k = 1;

	for (int itab = 0; itab < t.damier->nbC; ++itab) {
	cout << "avant heuristiqueManathan itab " << itab << endl;
	k = heuristiqueManathan(*t.damier, t.etatFinaux[itab]);
	cout << "avant heuristiqueManathan " << k << endl;
	if (itab == 0 || k < h) h = k;

	}*/
	h = heuristiqueSimple(t);

	return h;
}

//h avec heuristique simple :nombre de cases mal placées
unsigned int heuristiqueSimple(const Etat &t)
{
	unsigned int h = 1;
	unsigned int k = 0;

	for (int itab = 0; itab < t.damier->nbC; ++itab)
	{

		for (int i = 0; i < t.damier->nbL; ++i)
		{
			for (int j = 0; j < t.damier->nbC; ++j)
			{
				if (t.etatFinaux[itab].tab[i][j] != 0 && t.etatFinaux[itab].tab[i][j] != t.damier->tab[i][j])
					k++;
			}
		}


		if (itab == 0 || k < h) h = k;
		k = 0;
	}

	return h;
}

/* Résoudre le taquin et définir si une solution a été trouvée */
bool jouer(Taquin& t)
{

	int nbIteration = 0;
	Etat *eInit = NULL, *etatCourant = NULL;
	eInit = new Etat;
	eInit->damier = t.damier;
	eInit->etatFinaux = t.etatFinaux;
	initialiser(*eInit);
	eInit->h = heuristique(*eInit);
	eInit->f = eInit->g + eInit->h;
	etatCourant = eInit;

	PushFront(&t.leae, etatCourant);
	cout << "Iteration 0" << endl;
	afficher(t);
	cout << "Fin iteration 0" << endl << endl;
	//fin iteration 0
	//debut iteration 1
	nbIteration++;

	while (t.leae.premier != NULL)
	{
		etatCourant = minFEtat(&t.leae);

		PopEtat(&t.leae, etatCourant);
		enfiler(&t.lee, etatCourant);
		//cout << "etatCourant" << endl;
		//afficher(*etatCourant);


		if (but(*etatCourant)) {
			return true;
		}
		else {
			iterationEtat(t, etatCourant);

			cout << "Iteration " << nbIteration << endl;
			afficher(t);
			cout << "Fin iteration " << nbIteration << endl << endl;
		}

		nbIteration++;
	}

	return false;
}

/* Iteration sur l'algorithme A* */
bool iterationEtat(Taquin &t, Etat * etatCourant) {
	bool okPourCeTour = false;

	int &nbL = t.nbL;
	int &nbC = t.nbC;

	for (int i = 0; i < nbL && !okPourCeTour; ++i) {
		for (int j = 0; j < nbC && !okPourCeTour; ++j) {

			if (etatCourant->damier->tab[i][j] != 0) {
				continue;
			}

			// on a notre case vide
			okPourCeTour = true;

			// NORD
			if (i > 0) {

				Tab2D *damierDerive = new Tab2D;
				Item **tab = new Item*[nbL];
				for (int itab = 0; itab < nbL; itab++) {
					tab[itab] = new Item[nbC];
				}
				damierDerive->tab = tab;

				for (int l = 0; l < nbL; l++) {
					for (int k = 0; k < nbC; k++) {
						damierDerive->tab[l][k] = etatCourant->damier->tab[l][k];
					}
				}

				Etat * etatDerive = new Etat;
				etatDerive->etatPrecedent = etatCourant;
				etatDerive->etatFinaux = t.etatFinaux;
				etatDerive->mouv = etatDerive->NORD;


				damierDerive->tab[i][j] = etatCourant->damier->tab[i - 1][j];
				damierDerive->tab[i - 1][j] = etatCourant->damier->tab[i][j];

				damierDerive->lnVide = i - 1;
				damierDerive->colVide = j;

				damierDerive->nbC = nbC;
				damierDerive->nbL = nbL;
				etatDerive->damier = damierDerive;
				etatDerive->colVide = damierDerive->colVide;
				etatDerive->lnVide = damierDerive->lnVide;
				etatDerive->g = etatDerive->etatPrecedent->g + 1;
				etatDerive->h = heuristique(*etatDerive);
				etatDerive->f = etatDerive->g + etatDerive->h;


				etatDerive->etatFinaux = new Tab2D;
				etatDerive->etatFinaux = t.etatFinaux;

				for (int iFinal = 0; iFinal < nbC; ++iFinal)
					etatDerive->etatFinaux[iFinal] = t.etatFinaux[iFinal];

				if (!appartient(*etatDerive, t)) {
					PushFront(&t.leae, etatDerive);
				}

			}



			// OUEST
			if (j > 0) {

				Tab2D *damierDerive = new Tab2D;
				Item **tab = new Item*[nbL];
				for (int itab = 0; itab < nbL; itab++) {
					tab[itab] = new Item[nbC];
				}
				damierDerive->tab = tab;

				for (int l = 0; l < nbL; l++) {
					for (int k = 0; k < nbC; k++) {
						damierDerive->tab[l][k] = etatCourant->damier->tab[l][k];
					}
				}

				//memcpy(damierDerive->tab, etatCourant->damier->tab, sizeof(Item)*t.nbC*t.nbL);

				Etat * etatDerive = new Etat;
				etatDerive->etatPrecedent = etatCourant;
				etatDerive->etatFinaux = t.etatFinaux;
				etatDerive->mouv = etatDerive->OUEST;


				damierDerive->tab[i][j] = etatCourant->damier->tab[i][j - 1];
				damierDerive->tab[i][j - 1] = etatCourant->damier->tab[i][j];

				damierDerive->lnVide = i;
				damierDerive->colVide = j - 1;

				damierDerive->nbC = nbC;
				damierDerive->nbL = nbL;
				etatDerive->damier = damierDerive;
				etatDerive->colVide = damierDerive->colVide;
				etatDerive->lnVide = damierDerive->lnVide;
				etatDerive->g = etatDerive->etatPrecedent->g + 1;
				etatDerive->h = heuristique(*etatDerive);
				etatDerive->f = etatDerive->g + etatDerive->h;
				etatDerive->etatFinaux = new Tab2D;
				etatDerive->etatFinaux = t.etatFinaux;
				for (int iFinal = 0; iFinal < nbC; ++iFinal)
					etatDerive->etatFinaux[iFinal] = t.etatFinaux[iFinal];

				if (!appartient(*etatDerive, t)) {
					PushFront(&t.leae, etatDerive);
				}

			}

			// OUEST
			if (j == 0) {

				Tab2D *damierDerive = new Tab2D;
				Item **tab = new Item*[nbL];
				for (int itab = 0; itab < nbL; itab++) {
					tab[itab] = new Item[nbC];
				}
				damierDerive->tab = tab;

				for (int l = 0; l < nbL; l++) {
					for (int k = 0; k < nbC; k++) {
						damierDerive->tab[l][k] = etatCourant->damier->tab[l][k];
					}
				}

				Etat * etatDerive = new Etat;
				etatDerive->etatPrecedent = etatCourant;
				etatDerive->etatFinaux = t.etatFinaux;
				etatDerive->mouv = etatDerive->OUEST;


				damierDerive->tab[i][j] = etatCourant->damier->tab[i][nbC - 1];
				damierDerive->tab[i][nbC - 1] = etatCourant->damier->tab[i][j];

				damierDerive->lnVide = i;
				damierDerive->colVide = nbC - 1;

				damierDerive->nbC = nbC;
				damierDerive->nbL = nbL;
				etatDerive->damier = damierDerive;
				etatDerive->colVide = damierDerive->colVide;
				etatDerive->lnVide = damierDerive->lnVide;
				etatDerive->g = etatDerive->etatPrecedent->g + 1;
				etatDerive->h = heuristique(*etatDerive);
				etatDerive->f = etatDerive->g + etatDerive->h;
				etatDerive->etatFinaux = new Tab2D;
				etatDerive->etatFinaux = t.etatFinaux;
				for (int iFinal = 0; iFinal < nbC; ++iFinal)
					etatDerive->etatFinaux[iFinal] = t.etatFinaux[iFinal];

				if (!appartient(*etatDerive, t)) {
					PushFront(&t.leae, etatDerive);
				}

			}

			// SUD
			if (i < nbL - 1) {
				Tab2D *damierDerive = new Tab2D;

				Item **tab = new Item*[nbL];
				for (int itab = 0; itab < nbL; itab++) {
					tab[itab] = new Item[nbC];
				}
				damierDerive->tab = tab;

				for (int l = 0; l < nbL; l++) {
					for (int k = 0; k < nbC; k++) {
						damierDerive->tab[l][k] = etatCourant->damier->tab[l][k];
					}
				}

				Etat * etatDerive = new Etat;
				etatDerive->etatPrecedent = etatCourant;
				etatDerive->etatFinaux = t.etatFinaux;
				etatDerive->mouv = etatDerive->SUD;


				damierDerive->tab[i][j] = etatCourant->damier->tab[i + 1][j];
				damierDerive->tab[i + 1][j] = etatCourant->damier->tab[i][j];

				damierDerive->lnVide = i + 1;
				damierDerive->colVide = j;

				damierDerive->nbC = nbC;
				damierDerive->nbL = nbL;
				etatDerive->damier = damierDerive;
				etatDerive->colVide = damierDerive->colVide;
				etatDerive->lnVide = damierDerive->lnVide;
				etatDerive->g = etatDerive->etatPrecedent->g + 1;
				etatDerive->h = heuristique(*etatDerive);
				etatDerive->f = etatDerive->g + etatDerive->h;
				etatDerive->etatFinaux = new Tab2D;
				etatDerive->etatFinaux = t.etatFinaux;
				for (int iFinal = 0; iFinal < nbC; ++iFinal)
					etatDerive->etatFinaux[iFinal] = t.etatFinaux[iFinal];

				if (!appartient(*etatDerive, t)) {
					PushFront(&t.leae, etatDerive);
				}

			}

			// SUD
			/*if (i == nbL - 1) {
				Tab2D *damierDerive = new Tab2D;

				Item **tab = new Item*[nbL];
				for (int itab = 0; itab < nbL; itab++) {
					tab[itab] = new Item[nbC];
				}
				damierDerive->tab = tab;

				for (int l = 0; l < nbL; l++) {
					for (int k = 0; k < nbC; k++) {
						damierDerive->tab[l][k] = etatCourant->damier->tab[l][k];
					}
				}

				Etat * etatDerive = new Etat;
				etatDerive->etatPrecedent = etatCourant;
				etatDerive->etatFinaux = t.etatFinaux;
				etatDerive->mouv = etatDerive->SUD;


				damierDerive->tab[i][j] = etatCourant->damier->tab[0][j];
				damierDerive->tab[0][j] = etatCourant->damier->tab[i][j];

				damierDerive->lnVide = 0;
				damierDerive->colVide = j;

				damierDerive->nbC = nbC;
				damierDerive->nbL = nbL;
				etatDerive->damier = damierDerive;
				etatDerive->colVide = damierDerive->colVide;
				etatDerive->lnVide = damierDerive->lnVide;
				etatDerive->g = etatDerive->etatPrecedent->g + 1;
				etatDerive->f = etatDerive->g + etatDerive->h;

				if (!appartient(*etatDerive, t)) {
					PushFront(&t.leae, etatDerive);
				}

				if (but(*etatDerive)) {
					return true;
				}
			}*/

			// EST
			if (j < nbC - 1) {

				Tab2D *damierDerive = new Tab2D;

				Item **tab = new Item*[nbL];
				for (int itab = 0; itab < nbL; itab++) {
					tab[itab] = new Item[nbC];
				}
				damierDerive->tab = tab;

				for (int l = 0; l < nbL; l++) {
					for (int k = 0; k < nbC; k++) {
						damierDerive->tab[l][k] = etatCourant->damier->tab[l][k];
					}
				}

				Etat * etatDerive = new Etat;
				etatDerive->etatPrecedent = etatCourant;
				etatDerive->etatFinaux = t.etatFinaux;
				etatDerive->mouv = etatDerive->EST;


				damierDerive->tab[i][j] = etatCourant->damier->tab[i][j + 1];
				damierDerive->tab[i][j + 1] = etatCourant->damier->tab[i][j];

				damierDerive->lnVide = i;
				damierDerive->colVide = j + 1;

				damierDerive->nbC = nbC;
				damierDerive->nbL = nbL;
				etatDerive->damier = damierDerive;
				etatDerive->colVide = damierDerive->colVide;
				etatDerive->lnVide = damierDerive->lnVide;
				etatDerive->g = etatDerive->etatPrecedent->g + 1;
				etatDerive->h = heuristique(*etatDerive);
				etatDerive->f = etatDerive->g + etatDerive->h;
				etatDerive->etatFinaux = new Tab2D;
				etatDerive->etatFinaux = t.etatFinaux;
				for (int iFinal = 0; iFinal < nbC; ++iFinal)
					etatDerive->etatFinaux[iFinal] = t.etatFinaux[iFinal];

				if (!appartient(*etatDerive, t)) {
					PushFront(&t.leae, etatDerive);
				}

			}

			// EST
			if (j == nbC - 1) {

				Tab2D *damierDerive = new Tab2D;

				Item **tab = new Item*[nbL];
				for (int itab = 0; itab < nbL; itab++) {
					tab[itab] = new Item[nbC];
				}
				damierDerive->tab = tab;

				for (int l = 0; l < nbL; l++) {
					for (int k = 0; k < nbC; k++) {
						damierDerive->tab[l][k] = etatCourant->damier->tab[l][k];
					}
				}

				Etat * etatDerive = new Etat;
				etatDerive->etatPrecedent = etatCourant;
				etatDerive->etatFinaux = t.etatFinaux;
				etatDerive->mouv = etatDerive->EST;


				damierDerive->tab[i][j] = etatCourant->damier->tab[i][0];
				damierDerive->tab[i][0] = etatCourant->damier->tab[i][j];

				damierDerive->lnVide = i;
				damierDerive->colVide = 0;

				damierDerive->nbC = nbC;
				damierDerive->nbL = nbL;
				etatDerive->damier = damierDerive;
				etatDerive->colVide = damierDerive->colVide;
				etatDerive->lnVide = damierDerive->lnVide;
				etatDerive->g = etatDerive->etatPrecedent->g + 1;
				etatDerive->h = heuristique(*etatDerive);
				etatDerive->f = etatDerive->g + etatDerive->h;
				etatDerive->etatFinaux = new Tab2D;
				etatDerive->etatFinaux = t.etatFinaux;
				for (int iFinal = 0; iFinal < nbC; ++iFinal)
					etatDerive->etatFinaux[iFinal] = t.etatFinaux[iFinal];

				if (!appartient(*etatDerive, t)) {
					PushFront(&t.leae, etatDerive);
				}

			}


			// NORD
			/*if (i == 0) {

				Tab2D *damierDerive = new Tab2D;
				Item **tab = new Item*[nbL];
				for (int itab = 0; itab < nbL; itab++) {
					tab[itab] = new Item[nbC];
				}
				damierDerive->tab = tab;

				for (int l = 0; l < nbL; l++) {
					for (int k = 0; k < nbC; k++) {
						damierDerive->tab[l][k] = etatCourant->damier->tab[l][k];
					}
				}

				Etat * etatDerive = new Etat;
				etatDerive->etatPrecedent = etatCourant;
				etatDerive->etatFinaux = t.etatFinaux;
				etatDerive->mouv = etatDerive->NORD;


				damierDerive->tab[i][j] = etatCourant->damier->tab[nbL - 1][j];
				damierDerive->tab[nbL - 1][j] = etatCourant->damier->tab[i][j];

				damierDerive->lnVide = nbL - 1;
				damierDerive->colVide = j;

				damierDerive->nbC = nbC;
				damierDerive->nbL = nbL;
				etatDerive->damier = damierDerive;
				etatDerive->colVide = damierDerive->colVide;
				etatDerive->lnVide = damierDerive->lnVide;
				etatDerive->g = etatDerive->etatPrecedent->g + 1;
				etatDerive->f = etatDerive->g + etatDerive->h;

				if (!appartient(*etatDerive, t)) {
					PushFront(&t.leae, etatDerive);
				}

				if (but(*etatDerive)) {
					return true;
				}

			}*/
		}

	}

	return false;
}

//affiche la solution
void afficherSolution(Taquin& t) {

	cout << "Solution en " << t.nbMvtSolution << " mouvements" << endl;
	for (int i = 0; i < t.nbMvtSolution + 1; ++i) {
		if (t.solution[i].mouv == t.solution[i].NORD) cout << "NORD" << endl;
		if (t.solution[i].mouv == t.solution[i].SUD) cout << "SUD" << endl;
		if (t.solution[i].mouv == t.solution[i].EST) cout << "EST" << endl;
		if (t.solution[i].mouv == t.solution[i].OUEST) cout << "OUEST" << endl;

		afficher(*t.solution[i].damier);
	}
}


// Afficher le contenu des listes adev et dev
void afficher(Taquin& t) {

	/*cout << "*** LEE - long : " << t.lee.nb << endl;
	afficherFile(&t.lee);
	cout << endl;
	*/
	cout << "*** LEAE - long : " << t.leae.nb << endl;
	afficherListe(t.leae);
}

void detruire(Taquin& t) {

	detruireFile(&t.lee);
	//	delete &t.lee;

	detruireListe(&t.leae);
	//	delete &t.leae;

		//delete &t;
}

void detruireFile(File * file) {
	if (file == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element *actuel = file->premier;
	int cp = 0;
	while (actuel != NULL)
	{
		delete actuel->etat;
		actuel = actuel->suivant;
	}
}

void detruireListe(Liste * l) {
	Chainon *pelem = l->premier;
	while (pelem)
	{
		delete pelem->etat;
		pelem = pelem->suivant;
	}
}