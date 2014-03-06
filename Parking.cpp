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
#include "Sortie.h"
#include <Outils.h>
#include <Heure.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h> // shmget()
#include <sys/sem.h> // semget()
#include <unistd.h> // sleep(), pause()
#include <signal.h> // kill()

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
const unsigned int NB_REQ = 3;
const char* CONF_PATH = "./modele/config.h";
const int NB_SEM = 2;
const sigset_t SIG_SET[] = { SIGINT, SIGUSR2 };

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
int main()
// Algorithme :
//
{
	pid_t h_ret, sv_ret; // Id des tâches
	key_t shm_key, sem_key;
	int shm_flag, sem_flag;
	int shm_id, sem_id;
	int shm_size = NB_PLACES * 12 + 4 + NB_REQ * 12;

	// Masquage des signaux
	sigprocmask( SIG_SETMASK, SIG_SET, NULL);

	// Création du segment de mémoire partagée
	shm_key = ftok( CONF_PATH, 'R' );
	shm_flag = IPC_CREAT;
	if( (shm_id = shmget( shm_key, shm_size, shm_flag )) < 0 )
	{
		cerr << "ERR: Impossible de créer le segment de mémoire partagée." << endl;
		return 1;
	}

	// Création du sémaphore pour l'accès au segment de mp
	sem_key = ftok( CONF_PATH, 'R' );
	sem_flag = IPC_CREAT;
	if( (sem_id = semget( sem_key, NB_SEM, sem_flag )) < 0 )
	{
		cerr << "ERR: Impossible de créer le sémaphore." << endl;
		return 1;
	}
//	sem_set[0] = 0; // accès libre aux places de parking
//	sem_set[1] = 0; // accès libre aux requêtes en attente

	InitialiserApplication( XTERM );

	// Lancement des tâches
	h_ret = ActiverHeure();
	sv_ret = VoiturierSortie();
	// Attente d'un signal
	sigprocmask( SIG_UNBLOCK, SIG_SET, NULL);	
	//pause();
	sleep(5);

	kill( h_ret, SIGUSR2 ); // Arrêt de la tâche heure
	sleep(2);
	kill( sv_ret, SIGUSR2 ); // Arrêt de la tâche Sortie
	sleep(2);
	shmctl( shm_id, IPC_RMID, NULL ); // Destruction du segment de mp
	TerminerApplication();

	return EXIT_SUCCESS;
} //----- fin du main
