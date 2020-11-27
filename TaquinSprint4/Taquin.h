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

/*Maille d'une liste chainée*/
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

/*  Ajout d'une valeur en début de liste. */

void PushFront(Liste *l, Etat *nvEtat);

/*  Retrait d'une valeur en fin de liste. */

Etat * PopBack(Liste *l);

/*  Retrait d'une valeur en début de liste. */

Etat * PopFront(Liste *l);

/* Retrait d'une valeur selon sa position */
Etat * PopPosition(Liste *liste, int pos);

/* Retourne un état ayant une valeur de g minimim */
Etat * minGEtat(Liste *liste);

/* Retourne un état ayant une valeur de f minimim et h minimum si plusieurs fmin*/
Etat * minFEtat(Liste *liste);

/* Retrait d'une valeur de la liste */
Etat * PopEtat(Liste *p_list, Etat * etat);

/* Ajouter un état dans la file */
void enfiler(File *file, Etat *nvEtat);
/* Enlever un état de la file*/
Etat* defiler(File *file);
/* Ajouter un état dans la pile */
void empiler(Pile *pile, Etat *nvEtat);
/* Enlever un état de la pile*/
Etat* depiler(Pile *pile);
/* Enlever un état précis de la pile*/
Etat* depiler(Pile *pile, Etat *adepiler);
// Afficher un état du taquin
void afficher(const Etat& e);
// Créer le jeu de taquin avec l’état initial
void initialiser(Taquin& t);
// Itération de l’algorithme de recherche
//void jouer(Taquin& t);
// Afficher le contenu des listes adev et dev
void afficher(Taquin& t);

/*Détruire les listes du taquin et le taquin*/
void detruire(Taquin& t);
/* détruire la file en mémoire*/
void detruireFile(File * file);
/* détruire la pile en mémoire*/
void detruireListe(Liste * l);

void afficherFile(File *file);
/* Afficher le contenu de la liste chainée*/
void afficherListe(Liste l);

/* Vérifier si un damier est déjà préent dans la file lee */
bool appartient(const Etat& ef, Taquin& t, File * file);
/* Vérifier si un damier est déjà préent dans la liste leae */
bool appartient(const Etat& ef, Taquin& t, Liste * pile);
// renvoie vrai si l‘état existe déjà dans le taquin
bool appartient(const Etat& ef, Taquin& t);
// renvoie vrai s’il s’agir de l’état final, faux sinon
bool but(const Etat& e);
// itération de l’algorithme de recherche
// renvoie vrai si la solution a été trouvé, faux sinon
bool jouer(Taquin& t);

// calcul de l'heuristique
unsigned int heuristique(const Etat &t);
/*Heuristique simple avec le minimum de nombre de cases mal placées*/
unsigned int heuristiqueSimple(const Etat &t);
/*Heuristique de manhattan avec le nombre de cases mal placées et le minimum de distance*/
unsigned int heuristiqueManathan(const Tab2D &jeu, const Tab2D &etatFini);
/*distance entre un état et la position finale */
Position localiserPositionFinale(unsigned int valeur, const Tab2D &etatFini);
/* Calcul de la distance de Manhattan*/
unsigned int distanceManhattan(const Position p1, const Position p2);


//affiche la solution
void afficherSolution(Taquin& t);
/* Iteration sur l'algorithme A* */
bool iterationEtat(Taquin &t, Etat * etatCourant);