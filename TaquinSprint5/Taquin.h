/** 
* @author : Amiar Fares / Chen Richard
* @file : Taquin.h
* @version : Sprint 5
*/

#include "Etat.h"
#include <iostream>



/** 
* Element pour une file et pile
*/
struct Element
{
	// Etat correspondant
	Etat *etat;
	// Element suivant de la pile ou file
	Element *suivant;
};

/**
* Structure d'une pile
*/
struct Pile
{
	// Premier element d'une pile
	Element *premier = NULL;
	// Nombre d'element d'une pile
	int nb = 0;
};

/**
* Structure d'une pile
*/
struct File
{
	// Premier element d'une file
	Element *premier = NULL;
	// Nombre d'element d'une file
	int nb = 0;
};


/**
* Maille d'une liste chain�e
*/
struct Chainon
{
	// Etat correspondant
	Etat *etat = NULL;
	// Chainon suivant
	Chainon *suivant = NULL;
	// Chainon precedent
	Chainon *precedent = NULL;
};

/**
* Structure d'une liste chain�e
*/
struct Liste
{
	// premier element de la liste
	Chainon *premier = NULL;
	// dernier element de la liste
	Chainon *dernier = NULL;
	// Nombre d'element de la liste
	int nb = 0;
};

/** 
* Structure du taquin avec le damier initial
* les �tats finaux, la file et la liste des �tats et la solution finale
*/
struct Taquin
{
	// nombre de lignes du taquin
	int nbL = 0;
	// nombre de colonnes du taquin
	int nbC = 0;
	// Matrice du taquin de d�part
	Tab2D *damier = NULL;

	// tableau des �tats finaux possibles
	Tab2D *etatFinaux = NULL;
	// Pile des mouvements de la solution finale
	Pile *solution = NULL;
	// Nombre de mouvements de la solution finale
	int nbMvtSolution = 0;
	// liste des �tats �tablis
	File lee;
	// liste des �tats � �tablir
	Liste leae;
};

/** 
* Structure d'un point
*/
struct Position
{
	// Position sur la ligne
	unsigned int ligne;
	// Position sur la colonne
	unsigned int colonne;

};

/** 
* @brief  Ajout d'une valeur en fin de liste
* @param l liste de donn�es o� ins�rer une valeur
* @param nvEtat etat � ins�rer
*/
void PushBack(Liste *l, Etat *nvEtat);

/**
* @brief Ajout d'une valeur en d�but de liste
* @param l liste de donn�es o� ins�rer une valeur
* @param nvEtat etat � ins�rer
*/
void PushFront(Liste *l, Etat *nvEtat);

/**
* @brief Retrait d'une valeur en fin de liste.
* @param l liste de donn�es o� ins�rer une valeur
* @return etat supprim�
*/
Etat * PopBack(Liste *l);

/**
* @brief Retrait d'une valeur en d�but de liste.
* @param l liste de donn�es o� retirer une valeur
* @return etat supprim�
*/
Etat * PopFront(Liste *l);

/**
* @brief Retrait d'une valeur selon sa position.
* @param l liste de donn�es o� retirer une valeur
* @param pos position o� retirer une valeur
* @return etat supprim�
*/
Etat * PopPosition(Liste *liste, int pos);

/**
* @brief Retourne un �tat ayant une valeur de g minimim
* @param liste liste de donn�es � parcourir
* @return �tat ayant une valeur de g minimim
*/
Etat * minGEtat(Liste *liste);

/**
* @brief Retourne un �tat ayant une valeur de f minimim
* et h minimum si plusieurs fmin
* si plusieurs fmin et hmin prendre le plus r�cent ajout�
* @param liste liste de donn�es � parcourir
* @return �tat ayant une valeur de f minimim et h minimum
*/
Etat * minFEtat(Liste *liste);

/**
* @brief Retrait d'une valeur de la liste
* @param liste liste de donn�es � parcourir
* @param etat etat � enlever
* @return �tat ayant une valeur de f minimim et h minimum
*/
Etat * PopEtat(Liste *liste, Etat * etat);

/**
* @brief Ajouter un �tat dans la file
* @param file liste de donn�es � parcourir
* @param nvEtat etat � ajouter
*/
void enfiler(File *file, Etat *nvEtat);

/**
* @brief Enlever un �tat de la file
* @param file liste de donn�es o� retirer une valeur
* @param pos position o� retirer une valeur
* @return etat supprim�
*/
Etat* defiler(File *file);

/**
* @brief Ajouter un �tat dans la pile
* @param pile liste de donn�es � parcourir
* @param nvEtat etat � ajouter
*/
void empiler(Pile *pile, Etat *nvEtat);

/**
* @brief Enlever un �tat de la pile
* @param pile liste de donn�es o� retirer une valeur
* @return etat supprim�
*/
Etat* depiler(Pile *pile);

/**
* @brief Enlever un �tat pr�cis de la pile
* @param pile liste de donn�es o� retirer une valeur
* @param nvEtat etat � supprimer
* @return etat supprim�
*/
Etat* depiler(Pile *pile, Etat *adepiler);

/**
* @brief Afficher un �tat du taquin
* @param nvEtat etat � afficher
*/
void afficher(const Etat& e);

/**
* @brief Cr�er le jeu de taquin avec l��tat initial
* @param t taquin � initialier
*/
void initialiser(Taquin& t);

/**
* @brief Afficher le contenu des listes adev et dev
* @param t taquin courant
*/
void afficher(Taquin& t);

/**
* @brief D�truire les listes du taquin et le taquin
* @param t taquin courant
*/
void detruire(Taquin& t);

/**
* @brief d�truire la file en m�moire
* @param file : strucutre � d�truire
*/
void detruireFile(File * file);

/**
* @brief d�truire la liste en m�moire
* @param liste : structure � d�truire
*/
void detruireListe(Liste * l);

/**
* @brief d�truire la pile en m�moire
* @param pile : strucutre � d�truire
*/
void detruirePile(Pile * pile);

/**
* @brief Afficher le contenu de la liste chain�e
* @param liste : structure � afficher
*/
void afficherListe(Liste l);

/**
* @brief Afficher le contenu de la file
* @param file : structure � afficher
*/
void afficherFile(File *file);

/**
* @brief V�rifier si un damier est d�j� pr�ent dans la file lee
* @param ef etat a verifier
* @param t taquin courant
* @param file structure � v�rifier
* @return bool si damier est deja dans la liste
*/
bool appartient(const Etat& ef, Taquin& t, File * file);

/**
* @brief V�rifier si un damier est d�j� pr�ent dans la liste leae
* @param ef etat a verifier
* @param t taquin courant
* @param pile structure � v�rifier
* @return bool si damier est deja dans la liste
*/
bool appartient(const Etat& ef, Taquin& t, Liste * pile);

/**
* @brief si l��tat existe d�j� dans le taquin
* @param ef etat a verifier
* @param t taquin courant
* @return vrai si damier est deja dans la liste
*/
bool appartient(const Etat& ef, Taquin& t);

/**
* @brief renvoie vrai s�il s�agir de l��tat final, faux sinon
* @param ef etat a verifier
* @return vrai si damier est une des solutions finales
*/
bool but(const Etat& e);


/**
* @brief it�ration de l�algorithme de recherche
* R�soudre le taquin et d�finir si une solution a �t� trouv�e
* @param t taquin courant
* @return vrai si la solution a �t� trouv�, faux sinon
*/
bool jouer(Taquin& t);

/**
* @brief calcul de l'heuristique
* @param ef etat
* @return valeur de l'heuristique calcul�
*/
unsigned int heuristique(const Etat &t);

/**
* @brief Heuristique simple avec le minimum de nombre de cases mal plac�es
* @param ef etat
* @return valeur de l'heuristique calcul�
*/
unsigned int heuristiqueSimple(const Etat &t);

/**
* @brief Heuristique de manhattan avec le nombre de cases mal plac�es et le minimum de distance
* @param jeu etadamier courant
* @param etatFini damier final
* @return valeur de l'heuristique calcul�
*/
unsigned int heuristiqueManathan(const Tab2D &jeu, const Tab2D &etatFini);

/**
* @brief distance entre un �tat et la position finale
* @param valeur de la case
* @param etatFini damier final
* @return position finale de la case par rapport au damier final
*/
Position localiserPositionFinale(unsigned int valeur, const Tab2D &etatFini);

/**
* @brief Calcul de la distance de Manhattan
* @param p1 case � comparer
* @param p2 case du damier final
* @return distance enre les deux cases
*/
unsigned int distanceManhattan(const Position p1, const Position p2);

/**
* @brief affiche la solution
* @param t taquin
*/
void afficherSolution(Taquin& t);

/**
* @brief Iteration sur l'algorithme A*
* @param t taquin
* @param etatCourant case du damier final
*/
void iterationEtat(Taquin &t, Etat * etatCourant);

/**
* @brief Recupere l'etat final dans la liste des �tats �tablis
* @param file liste des �tats �tablis
* @return �tat final trouv�
*/
Etat * recupererEtatFinal(File *file);

/**
* @brief memorise la solution sous forme de graphe dans une structure
* @param etatFinal �tat cible de la solution trouv�e
* @param t taquin
* @param la pile des �tats de la solution
*/
Pile * memoriserSolution(Etat *etatFinal, Taquin &t);