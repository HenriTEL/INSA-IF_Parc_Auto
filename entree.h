/*************************************************************************
                           entree  -  description
                             -------------------
    début                : 18 Février 2014
    copyright            : (C) 2014 par Maria ETEGAN	
    e-mail               : maria.etegan@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tache <Entree> (fichier Entree.h) -------
#if ! defined ( ENTREE_H )
#define ENTREE_H

//------------------------------------------------------------------------ 
// Role de la tache <entree>
//	tâche qui gère l'entree dans le parking pour chaque porte
//  on aura une tâche pour chaque porte 
//  (PROF_BLAISE_PASCAL, AUTRE_BLAISE_PASCAL, ENTREE_GASTON_BERGER)
//------------------------------------------------------------------------ 

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisees

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Entree(unsigned int porte, int requetes, int etatParking,  
    int nbPlaces, int placeLibre, int semMemoire, const char * const CANAL);
// Mode d'emploi : 
// Tâche entree crée par la tâche mere 
// Paramétres : 
// - unsigned int porte:
//	 le numero de la porte qu'elle controle : 
//   	0 pour la porte PROF_BLAISE_PASCAL, 
//   	1 pour la porte AUTRE_BLAISE_PASCAL, 
//   	2 pour la porte ENTREE_GASTON_BERGER 
//
// - int requetes: l'identifiant de la zone de memoire partagee requetes
// - int etatParking: l'identifiant de la zone de memoire partagee etatParking 
// - int nbPlaces: l'identifiant de la zone de memoire partagee nbPlaces

// - int placeLibre: l'identifiant du semaphore placeLibre, au prealable cree. 
// - int semMemoire: l'identifiant du semaphore triple qui protège les 3 zones mémoire. 
// - const char * const CANAL: le chemin d'acces au canal entre entree et simulateur
//


#endif // ENTREE_H

