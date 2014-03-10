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
static void usr2_handler( int signo )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
/*
	extern vector<pid_t> pid_voiturier;
	if( signo == SIGUSR2 )
	{
		for( int i=0; i < pid_voiturier.size(); i++ )
			kill( pid_voiturier[i], SIGUSR2 );
		exit( EXIT_SUCCESS );
	}
*/
} //----- fin de sig_handler

static void chld_handler( int signo )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
{
	pid_t pid;
	int status;

	if( signo == SIGCHLD )
	{
		pid = wait( *status );
		// virer voiture dans mem partagée
		// décrémenter nbplaces
		signal(SIGCHLD, chld_handler);
	}
		//exit( EXIT_SUCCESS );
} //----- fin de sig_handler
//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques


pid_t VoiturierSortie ()
// Algorithme :
//
{
	pid_t pid_sortie;
/*	extern int pipe_end[2]; // obtenu à partir de la tâche simulation */
/*	vector<pid_t> pid_voiturier; */
	char place;

	signal(SIGUSR2, usr2_handler);
	if( (pid_sortie = fork()) == 0 )
	// Fils
	{
		// tableau de pid des voituriers - SortirVoiture() -
		// Bloquer signaux
		// Mettre en place pipe
		signal( SIGCHLD, chld_handler );
		for( ;; )
		{
/*
			close( pipe_end[1] ); // Fermeture de la sortie du canal
			while ( read( pipe_end[0], &place, 1 ) > 0 )
			// Une voiture veut sortir
			{
				pid_voiturier.append( SortirVoiture( atoi(place) ) );
			}
*/
			// si SIGUSR2 kill + exit
			// /!\ (in/dé)crémenter au bon moment nb voitures
			// SortirVoiture
			// /!\ délais entre chaque voitur pour sortir
		}
	}
	return pid_sortie;
} //----- fin de VoiturierSortie

