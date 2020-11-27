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
* Maille d'une liste chainée
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
* Structure d'une liste chainée
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
* les états finaux, la file et la liste des états et la solution finale
*/
struct Taquin
{
	// nombre de lignes du taquin
	int nbL = 0;
	// nombre de colonnes du taquin
	int nbC = 0;
	// Matrice du taquin de départ
	Tab2D *damier = NULL;

	// tableau des états finaux possibles
	Tab2D *etatFinaux = NULL;
	// Pile des mouvements de la solution finale
	Pile *solution = NULL;
	// Nombre de mouvements de la solution finale
	int nbMvtSolution = 0;
	// liste des états établis
	File lee;
	// liste des états à établir
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
* @param l liste de données où insérer une valeur
* @param nvEtat etat à insérer
*/
void PushBack(Liste *l, Etat *nvEtat);

/**
* @brief Ajout d'une valeur en début de liste
* @param l liste de données où insérer une valeur
* @param nvEtat etat à insérer
*/
void PushFront(Liste *l, Etat *nvEtat);

/**
* @brief Retrait d'une valeur en fin de liste.
* @param l liste de données où insérer une valeur
* @return etat supprimé
*/
Etat * PopBack(Liste *l);

/**
* @brief Retrait d'une valeur en début de liste.
* @param l liste de données où retirer une valeur
* @return etat supprimé
*/
Etat * PopFront(Liste *l);

/**
* @brief Retrait d'une valeur selon sa position.
* @param l liste de données où retirer une valeur
* @param pos position où retirer une valeur
* @return etat supprimé
*/
Etat * PopPosition(Liste *liste, int pos);

/**
* @brief Retourne un état ayant une valeur de g minimim
* @param liste liste de données à parcourir
* @return état ayant une valeur de g minimim
*/
Etat * minGEtat(Liste *liste);

/**
* @brief Retourne un état ayant une valeur de f minimim
* et h minimum si plusieurs fmin
* si plusieurs fmin et hmin prendre le plus récent ajouté
* @param liste liste de données à parcourir
* @return état ayant une valeur de f minimim et h minimum
*/
Etat * minFEtat(Liste *liste);

/**
* @brief Retrait d'une valeur de la liste
* @param liste liste de données à parcourir
* @param etat etat à enlever
* @return état ayant une valeur de f minimim et h minimum
*/
Etat * PopEtat(Liste *liste, Etat * etat);

/**
* @brief Ajouter un état dans la file
* @param file liste de données à parcourir
* @param nvEtat etat à ajouter
*/
void enfiler(File *file, Etat *nvEtat);

/**
* @brief Enlever un état de la file
* @param file liste de données où retirer une valeur
* @param pos position où retirer une valeur
* @return etat supprimé
*/
Etat* defiler(File *file);

/**
* @brief Ajouter un état dans la pile
* @param pile liste de données à parcourir
* @param nvEtat etat à ajouter
*/
void empiler(Pile *pile, Etat *nvEtat);

/**
* @brief Enlever un état de la pile
* @param pile liste de données où retirer une valeur
* @return etat supprimé
*/
Etat* depiler(Pile *pile);

/**
* @brief Enlever un état précis de la pile
* @param pile liste de données où retirer une valeur
* @param nvEtat etat à supprimer
* @return etat supprimé
*/
Etat* depiler(Pile *pile, Etat *adepiler);

/**
* @brief Afficher un état du taquin
* @param nvEtat etat à afficher
*/
void afficher(const Etat& e);

/**
* @brief Créer le jeu de taquin avec l’état initial
* @param t taquin à initialier
*/
void initialiser(Taquin& t);

/**
* @brief Afficher le contenu des listes adev et dev
* @param t taquin courant
*/
void afficher(Taquin& t);

/**
* @brief Détruire les listes du taquin et le taquin
* @param t taquin courant
*/
void detruire(Taquin& t);

/**
* @brief détruire la file en mémoire
* @param file : strucutre à détruire
*/
void detruireFile(File * file);

/**
* @brief détruire la liste en mémoire
* @param liste : structure à détruire
*/
void detruireListe(Liste * l);

/**
* @brief détruire la pile en mémoire
* @param pile : strucutre à détruire
*/
void detruirePile(Pile * pile);

/**
* @brief Afficher le contenu de la liste chainée
* @param liste : structure à afficher
*/
void afficherListe(Liste l);

/**
* @brief Afficher le contenu de la file
* @param file : structure à afficher
*/
void afficherFile(File *file);

/**
* @brief Vérifier si un damier est déjà préent dans la file lee
* @param ef etat a verifier
* @param t taquin courant
* @param file structure à vérifier
* @return bool si damier est deja dans la liste
*/
bool appartient(const Etat& ef, Taquin& t, File * file);

/**
* @brief Vérifier si un damier est déjà préent dans la liste leae
* @param ef etat a verifier
* @param t taquin courant
* @param pile structure à vérifier
* @return bool si damier est deja dans la liste
*/
bool appartient(const Etat& ef, Taquin& t, Liste * pile);

/**
* @brief si l‘état existe déjà dans le taquin
* @param ef etat a verifier
* @param t taquin courant
* @return vrai si damier est deja dans la liste
*/
bool appartient(const Etat& ef, Taquin& t);

/**
* @brief renvoie vrai s’il s’agir de l’état final, faux sinon
* @param ef etat a verifier
* @return vrai si damier est une des solutions finales
*/
bool but(const Etat& e);


/**
* @brief itération de l’algorithme de recherche
* Résoudre le taquin et définir si une solution a été trouvée
* @param t taquin courant
* @return vrai si la solution a été trouvé, faux sinon
*/
bool jouer(Taquin& t);

/**
* @brief calcul de l'heuristique
* @param ef etat
* @return valeur de l'heuristique calculé
*/
unsigned int heuristique(const Etat &t);

/**
* @brief Heuristique simple avec le minimum de nombre de cases mal placées
* @param ef etat
* @return valeur de l'heuristique calculé
*/
unsigned int heuristiqueSimple(const Etat &t);

/**
* @brief Heuristique de manhattan avec le nombre de cases mal placées et le minimum de distance
* @param jeu etadamier courant
* @param etatFini damier final
* @return valeur de l'heuristique calculé
*/
unsigned int heuristiqueManathan(const Tab2D &jeu, const Tab2D &etatFini);

/**
* @brief distance entre un état et la position finale
* @param valeur de la case
* @param etatFini damier final
* @return position finale de la case par rapport au damier final
*/
Position localiserPositionFinale(unsigned int valeur, const Tab2D &etatFini);

/**
* @brief Calcul de la distance de Manhattan
* @param p1 case à comparer
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
* @brief Recupere l'etat final dans la liste des états établis
* @param file liste des états établis
* @return état final trouvé
*/
Etat * recupererEtatFinal(File *file);

/**
* @brief memorise la solution sous forme de graphe dans une structure
* @param etatFinal état cible de la solution trouvée
* @param t taquin
* @param la pile des états de la solution
*/
Pile * memoriserSolution(Etat *etatFinal, Taquin &t);