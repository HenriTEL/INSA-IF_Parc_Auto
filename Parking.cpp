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
#include <Heure.h>
#include <sys/ipc.h>
#include <unistd.h> // sleep()
#include <signal.h> // kill()
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
	pid_t h_ret;

	InitialiserApplication( XTERM );
	h_ret = ActiverHeure();

	sleep(5);

	kill( h_ret, SIGUSR2 ); // Arrêt de l'heure
	TerminerApplication();

	return 0;
} //----- fin du main
