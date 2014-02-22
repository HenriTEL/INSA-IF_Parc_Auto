/*************************************************************************
                           Parking  -  description
                             -------------------
    début                : 20 février 2014
    copyright            : (C) 2014 par Henri HANNETEL
    e-mail               : henri.hannetel@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <Parking> (fichier Parking.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Parking.h"
#include <Outils.h>
#include <unistd.h> //sleep()
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int main(void)
// Algorithme :
//
{
	InitialiserApplication( XTERM );
	sleep(5);
	TerminerApplication();
	return 0;
} //----- fin du main

