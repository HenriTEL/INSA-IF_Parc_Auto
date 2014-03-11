/*************************************************************************
                           simulateur  -  description
                             -------------------
    début                : 18 Février 2014
    copyright            : (C) 2014 par Maria ETEGAN	
    e-mail               : maria.etegan@insa-lyon.fr
*************************************************************************/

//---------- Interface de la tâche <simulateur> (fichier simulateur.h) -------
#if ! defined ( simulateur_H )
#define simulateur_H

//------------------------------------------------------------------------
// Rôle de la tâche <simulateur>
//	la tâche simulateur récupére la commande tappe au clavier par l'utilisateur
//		si c'est un caractère 'Q' ferme l'application 
//		si c'est un caractère 'S' met un massage dans le canal de communication avec la tâche sortie
//		si c'est un carcatère 'P' ou 'A' met un massage dans le canal de communication avec la tâche sortie
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include "/public/tp/tp-multitache/Outils.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void simulateur( const char * CHEMIN_CANAUX_SORTIE_VOITURE, const char ** CHEMIN_CANAL_ARRIVEE_VOITURE );
// Mode d'emploi :
// 	Ouvre les canaux de communication avec les tâches entree et sortie 
//
// Contrat : aucun
//
//);
void Commande ( char code, unsigned int valeur );
// Mode d'emploi :
// Procédure appelée par le module Menu qui fait l'action correspondante pour chaque commande 
//									(écriture dans le canal adequat ou fin de l'application)
//
// Contrat : aucun
//

#endif // simulateur_H

