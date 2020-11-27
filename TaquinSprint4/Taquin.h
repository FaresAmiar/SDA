#include "Etat.h"
#include <iostream>

/*Element pour une file et pile*/
struct Element
{
	Etat *etat;
	Element *suivant;
};

struct Pile
{
	Element *premier = NULL;
	int nb = 0;
};

struct File
{
	Element *premier = NULL;
	int nb = 0;
};

/*Maille d'une liste chain�e*/
struct Chainon
{
	Etat *etat = NULL;
	Chainon *suivant = NULL;
	Chainon *precedent = NULL;
};

struct Liste
{
	Chainon *premier = NULL;
	Chainon *dernier = NULL;

	int nb = 0;
};

struct Taquin
{
	int nbL = 0;
	int nbC = 0;
	Tab2D *damier = NULL;

	Tab2D *etatFinaux = NULL;
	Etat *solution = NULL;

	int nbMvtSolution = 0;
	File lee;
	Liste leae;
};

struct Position
{
	unsigned int ligne;
	unsigned int colonne;

};

/*  Ajout d'une valeur en fin de liste. */

void PushBack(Liste *l, Etat *nvEtat);

/*  Ajout d'une valeur en d�but de liste. */

void PushFront(Liste *l, Etat *nvEtat);

/*  Retrait d'une valeur en fin de liste. */

Etat * PopBack(Liste *l);

/*  Retrait d'une valeur en d�but de liste. */

Etat * PopFront(Liste *l);

/* Retrait d'une valeur selon sa position */
Etat * PopPosition(Liste *liste, int pos);

/* Retourne un �tat ayant une valeur de g minimim */
Etat * minGEtat(Liste *liste);

/* Retourne un �tat ayant une valeur de f minimim et h minimum si plusieurs fmin*/
Etat * minFEtat(Liste *liste);

/* Retrait d'une valeur de la liste */
Etat * PopEtat(Liste *p_list, Etat * etat);

/* Ajouter un �tat dans la file */
void enfiler(File *file, Etat *nvEtat);
/* Enlever un �tat de la file*/
Etat* defiler(File *file);
/* Ajouter un �tat dans la pile */
void empiler(Pile *pile, Etat *nvEtat);
/* Enlever un �tat de la pile*/
Etat* depiler(Pile *pile);
/* Enlever un �tat pr�cis de la pile*/
Etat* depiler(Pile *pile, Etat *adepiler);
// Afficher un �tat du taquin
void afficher(const Etat& e);
// Cr�er le jeu de taquin avec l��tat initial
void initialiser(Taquin& t);
// It�ration de l�algorithme de recherche
//void jouer(Taquin& t);
// Afficher le contenu des listes adev et dev
void afficher(Taquin& t);

/*D�truire les listes du taquin et le taquin*/
void detruire(Taquin& t);
/* d�truire la file en m�moire*/
void detruireFile(File * file);
/* d�truire la pile en m�moire*/
void detruireListe(Liste * l);

void afficherFile(File *file);
/* Afficher le contenu de la liste chain�e*/
void afficherListe(Liste l);

/* V�rifier si un damier est d�j� pr�ent dans la file lee */
bool appartient(const Etat& ef, Taquin& t, File * file);
/* V�rifier si un damier est d�j� pr�ent dans la liste leae */
bool appartient(const Etat& ef, Taquin& t, Liste * pile);
// renvoie vrai si l��tat existe d�j� dans le taquin
bool appartient(const Etat& ef, Taquin& t);
// renvoie vrai s�il s�agir de l��tat final, faux sinon
bool but(const Etat& e);
// it�ration de l�algorithme de recherche
// renvoie vrai si la solution a �t� trouv�, faux sinon
bool jouer(Taquin& t);

// calcul de l'heuristique
unsigned int heuristique(const Etat &t);
/*Heuristique simple avec le minimum de nombre de cases mal plac�es*/
unsigned int heuristiqueSimple(const Etat &t);
/*Heuristique de manhattan avec le nombre de cases mal plac�es et le minimum de distance*/
unsigned int heuristiqueManathan(const Tab2D &jeu, const Tab2D &etatFini);
/*distance entre un �tat et la position finale */
Position localiserPositionFinale(unsigned int valeur, const Tab2D &etatFini);
/* Calcul de la distance de Manhattan*/
unsigned int distanceManhattan(const Position p1, const Position p2);


//affiche la solution
void afficherSolution(Taquin& t);
/* Iteration sur l'algorithme A* */
bool iterationEtat(Taquin &t, Etat * etatCourant);