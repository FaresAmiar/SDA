/**
* @author : Amiar Fares / Chen Richard
* @file : Taquin.cpp
* @version : Sprint 5
*/

#include "Taquin.h"
#include <iostream>
using namespace std;


/**
* @brief Afficher un état du taquin
* @param nvEtat : etat à afficher
*/
void afficher(const Etat& e) 
{
	if (e.mouv == e.NORD) cout << "NORD" << endl;
	if (e.mouv == e.SUD) cout << "SUD" << endl;
	if (e.mouv == e.EST) cout << "EST" << endl;
	if (e.mouv == e.OUEST) cout << "OUEST" << endl;

	afficher(*e.damier);

	//cout << "f=g+h=" << e.g << "+" << e.h << "=" << e.f << endl;
}

/**
* @brief Créer le jeu de taquin avec l’état initial
* @param t : taquin à initialier
*/
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

/**
* @brief Ajout d'une valeur en fin de liste
* @param l liste de données où insérer une valeur
* @param nvEtat etat à insérer
*/
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

/**
* @brief Ajout d'une valeur en début de liste
* @param l liste de données où insérer une valeur
* @param nvEtat etat à insérer
*/
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

/**
* @brief Retrait d'une valeur en fin de liste.
* @param l liste de données où insérer une valeur
* @return etat supprimé
*/
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

/**
* @brief Retrait d'une valeur en début de liste.
* @param l liste de données où retirer une valeur
* @return etat supprimé
*/
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

/**
* @brief Retrait d'une valeur de la liste
* @param liste liste de données à parcourir
* @param etat etat à enlever
* @return état ayant une valeur de f minimim et h minimum
*/
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

/**
* @brief Retrait d'une valeur selon sa position.
* @param l liste de données où retirer une valeur
* @param pos position où retirer une valeur
* @return etat supprimé
*/
Etat * PopPosition(Liste *liste, int pos)
{
	int i;
	Chainon *supp_element, *courant;
	Etat * etatRetour = NULL;

	if (liste->nb == 0)
		return NULL;

	if (pos == 1){ // suppresion de 1er élément
		supp_element = liste->premier;
		liste->premier = liste->premier->suivant;
		if (liste->premier == NULL)
			liste->dernier = NULL;
		else
			liste->premier->precedent = NULL;
	} else 
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
		for (i = 1; i<pos; ++i)
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

/**
* @brief Retourne un état ayant une valeur de g minimim
* @param liste liste de données à parcourir
* @return état ayant une valeur de g minimim
*/
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

/**
* @brief Retourne un état ayant une valeur de f minimim
* et h minimum si plusieurs fmin
* si plusieurs fmin et hmin prendre le plus récent ajouté
* @param liste liste de données à parcourir
* @return état ayant une valeur de f minimim et h minimum
*/
Etat * minFEtat(Liste *liste)
{
	Etat * minEtat = NULL;

	if (liste != NULL)
	{
		Chainon *chainonTemp = liste->premier;

		while (chainonTemp != NULL)
		{
			if (minEtat == NULL || (minEtat != NULL && minEtat->f > chainonTemp->etat->f)
				|| (minEtat->f == chainonTemp->etat->f && minEtat->h > chainonTemp->etat->h))
			{
				minEtat = chainonTemp->etat;
			}

			chainonTemp = chainonTemp->suivant;

		}
	}
	return minEtat;
}

/**
* @brief Ajouter un état dans la file
* @param file liste de données à parcourir
* @param nvEtat etat à ajouter
*/
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

/**
* @brief Enlever un état de la file
* @param file liste de données où retirer une valeur
* @param pos position où retirer une valeur
* @return etat supprimé
*/
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

/**
* @brief Ajouter un état dans la pile
* @param pile liste de données à parcourir
* @param nvEtat etat à ajouter
*/
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

/**
* @brief Enlever un état de la pile
* @param pile liste de données où retirer une valeur
* @return etat supprimé
*/
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

/**
* @brief Enlever un état précis de la pile
* @param pile liste de données où retirer une valeur
* @param nvEtat etat à supprimer
* @return etat supprimé
*/
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

/**
* @brief Afficher le contenu de la pile
* @param pile : structure à afficher
*/
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

/**
* @brief Afficher le contenu de la file
* @param file : structure à afficher
*/
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

/**
* @brief Afficher le contenu de la liste chainée
* @param liste : structure à afficher
*/
void afficherListe(Liste l)
{

	Chainon *pelem = l.premier;
	while (pelem)
	{
		afficher(*pelem->etat);
		pelem = pelem->suivant;
	}

}

/**
* @brief Vérifier si un damier est déjà préent dans la file lee
* @param ef etat a verifier
* @param t taquin courant
* @param file structure à vérifier
* @return bool si damier est deja dans la liste
*/
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

/**
* @brief Vérifier si un damier est déjà préent dans la liste leae
* @param ef etat a verifier
* @param t taquin courant
* @param pile structure à vérifier
* @return bool si damier est deja dans la liste
*/
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

/**
* @brief si l‘état existe déjà dans le taquin
* @param ef etat a verifier
* @param t taquin courant
* @return vrai si damier est deja dans la liste
*/
bool appartient(const Etat& ef, Taquin& t) 
{
	 
	if (&ef == NULL || &ef.damier == NULL) return false;

	return appartient(ef, t, &t.leae) || appartient(ef, t, &t.lee);
}

/**
* @brief renvoie vrai s’il s’agir de l’état final, faux sinon
* @param ef etat a verifier
* @return vrai si damier est une des solutions finales
*/
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

/**
* @brief Calcul de la distance de Manhattan
* @param p1 case à comparer
* @param p2 case du damier final
* @return distance enre les deux cases
*/
unsigned int distanceManhattan(const Position p1, const Position p2) 
{
	return (p1.ligne - p2.ligne)*(p1.ligne - p2.ligne) + (p1.colonne - p2.colonne)*(p1.colonne - p2.colonne);
}

/**
* @brief distance entre un état et la position finale
* @param valeur de la case
* @param etatFini damier final
* @return position finale de la case par rapport au damier final
*/
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

/**
* @brief Heuristique de manhattan avec le nombre de cases mal placées et le minimum de distance
* @param jeu etadamier courant
* @param etatFini damier final
* @return valeur de l'heuristique calculé
*/
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

/**
* @brief calcul de l'heuristique
* @param ef etat
* @return valeur de l'heuristique calculé
*/
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

/**
* @brief Heuristique simple avec le minimum de nombre de cases mal placées
* @param ef etat
* @return valeur de l'heuristique calculé
*/
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

/**
* @brief itération de l’algorithme de recherche
* Résoudre le taquin et définir si une solution a été trouvée
* @param t taquin courant
* @return vrai si la solution a été trouvé, faux sinon
*/
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
	//cout << "Iteration 0" << endl;
	//afficher(t);
	//cout << "Fin iteration 0" << endl << endl;
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


		if (but(*etatCourant)){
			return true;
		}
		else {
			iterationEtat(t, etatCourant);

			//cout << "Iteration " << nbIteration << endl;
			//afficher(t);
			//cout << "Fin iteration " << nbIteration << endl << endl;
		}

		nbIteration++;
	}

	return false;
}

/**
* @brief Iteration sur l'algorithme A*
* @param t taquin
* @param etatCourant case du damier final
*/
void iterationEtat(Taquin &t, Etat * etatCourant) {
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

		}

	}

}

/**
* @brief affiche la solution
* @param t taquin
*/
void afficherSolution(Taquin& t) {
	Element * actuel = (t.solution)->premier;

	cout << "Solution en " << t.nbMvtSolution << " mouvements" << endl;
	while (actuel) {
		afficher(*(actuel->etat));
		actuel = actuel->suivant;
	}
}

/**
* @brief Afficher le contenu des listes adev et dev
* @param t taquin courant
*/
void afficher(Taquin& t) {

	cout << "*** LEE - long : " << t.lee.nb << endl;
	afficherFile(&t.lee);
	cout << endl;
	
	cout << "*** LEAE - long : " << t.leae.nb << endl;
	afficherListe(t.leae);
}

/**
* @brief Détruire les listes du taquin et le taquin
* @param t taquin courant
*/
void detruire(Taquin& t) {

	detruireFile(&t.lee);

	detruireListe(&t.leae);

}

/**
* @brief détruire la file en mémoire
* @param file : strucutre à détruire
*/
void detruireFile(File * file) {
	if (file == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element *actuel = file->premier;

	while (actuel != NULL)
	{
		delete actuel->etat;
		actuel = actuel->suivant;
	}
}

/**
* @brief détruire la pile en mémoire
* @param pile : strucutre à détruire
*/
void detruirePile(Pile * pile) {
	if (pile == NULL)
	{
		exit(EXIT_FAILURE);
	}
	Element *actuel = pile->premier;

	while (actuel != NULL)
	{
		delete actuel->etat;
		actuel = actuel->suivant;
	}
}

/**
* @brief détruire la liste en mémoire
* @param liste : structure à détruire
*/
void detruireListe(Liste * l) {
	Chainon *pelem = l->premier;
	while (pelem)
	{
		delete pelem->etat;
		pelem = pelem->suivant;
	}
}

/**
* @brief Recupere l'etat final dans la liste des états établis
* @param file liste des états établis
* @return état final trouvé
*/
Etat * recupererEtatFinal(File *file) {
	Element *actuel = file->premier;
	Etat *etatFinal = NULL;

	while (actuel != NULL)
	{
		etatFinal = actuel->etat;
		actuel = actuel->suivant;
	}

	return etatFinal;
}

/**
* @brief memorise la solution sous forme de graphe dans une structure
* @param etatFinal état cible de la solution trouvée
* @param t taquin
* @param la pile des états de la solution
*/
Pile * memoriserSolution(Etat *etatFinal, Taquin &t) {
	Pile * solution = new Pile;
	Etat *etatMemorise = etatFinal;
	while (etatMemorise != NULL) {

		empiler(solution, etatMemorise);

		etatMemorise = etatMemorise->etatPrecedent;
	}

	return solution;
}