/*************************************************************************
                           Sortie  -  description
                             -------------------
    début                : 05 mars 2014
    copyright            : (C) 2014 par Henri HANNETEL
    e-mail               : henri.hannetel@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <Sortie> (fichier Sortie.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Sortie.h"
#include <sys/types.h> // pid_t
#include <signal.h> // fork()
#include <unistd.h>
#include <cstdlib>

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
static void usr2_handler(int signo)
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
	if( signo == SIGUSR2 )
		exit( EXIT_SUCCESS );
} //----- fin de sig_handler

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques


pid_t VoiturierSortie ()
// Algorithme :
//
{
	pid_t pid;

	signal(SIGUSR2, usr2_handler);
	if( (pid = fork()) == 0 ) // fork is successful
	{
		// tableau de pid des voituriers - SortirVoiture() -
		// Bloquer signaux
		// Mettre en place pipe
		for( ;; )
		{
			pause();
			// si SIGUSR2 kill + exit
			// /!\ (in/dé)crémenter au bon moment nb voitures
			// SortirVoiture
			// /!\ délais entre chaque voitur pour sortir
		}
	}
	return pid;	
} //----- fin de VoiturierSortie

