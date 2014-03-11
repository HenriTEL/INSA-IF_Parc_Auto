/*************************************************************************
                           entree  -  description
                             -------------------
    début                : 18 Février 2014
    copyright            : (C) 2014 par Maria ETEGAN	
    e-mail               : maria.etegan@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <entree> (fichier entree.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <set>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

//------------------------------------------------------ Include personnel
#include "Entree.h"
#include "/public/tp/tp-multitache/Outils.h"
#include "config.h"


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
static const unsigned int TEMPO = 1;

//------------------------------------------------------------------ Types
struct Requete
{
	TypeBarriere barriere; 
    TypeUsager usager;
    time_t arrivee;
};

struct EtatParking
{
    TypeUsager usager;
    unsigned int numero;
    time_t arrivee;
};


//---------------------------------------------------- Variables statiques
static set<pid_t> lesVoituriers; 
// set de toutes les tâches voiturier lancées par la tâche entree

static EtatParking * adrEtatParking;
static unsigned int * adrNbPLaces;
static Requete * adrRequetes;

static int idCanal;
static TypeUsager usagers[NB_PLACES];
static time_t arrivee[NB_PLACES];

//------------------------------------------------------ Fonctions privées
static void DestructionEntree (int noSignal)
// Algorithme :
// 
// - detachement des zones memoires
// - fermeture du canal Canal[i]
// - destruction de toutes les tâches VoiturierEntree existantes
// - destruction de la tache. 
//

{
    // Destruction:
        
        // Detachement de la zone memoire Requetes : 
        shmdt ( adrRequetes );
        
        // Demande de detachement de la zone memoire EtatParking: 
        shmdt ( adrEtatParking );

        // Detachement de la zone memoire NbPLaces : 
        shmdt ( adrNbPLaces );

      

        // Fermeture du canal correspondant  : 
        close ( idCanal );
        
        for(set<pid_t>::iterator id = lesVoituriers.begin(); id!= lesVoituriers.end();id++)
        { 
            // Envoi de SIGUSR2: 
            kill(*id, SIGUSR2);

            // Attente de la mort : 
            waitpid(*id, NULL, 0);
        }


        // Fin de la tâche : 
        exit(0);
} //----- fin de DestructionEntree



static void FinGarage (int noSignal)
// Mode d'emploi : Handler de signal SIGCHLD. 
//
// Algorithme :
// - Tant qu'il y a des taches voiturier mortes dont la mort n'a pas ete constatee
//    - Prise en compte de la place du parking occupée en recuperant le pid des tâches mortes
//	  - Mise à jour des zones mémoires : etatParking et nbPLaces
//    - Affichage de la nouvelle place de parking occupee
//
{
    int crdu;

    // Si une des tâches voiturier est morte, on recupere son pid : 
    pid_t pidRenvoie = waitpid(-1, &crdu, 0);  

    // Tant qu'il y a des morts, valeur de retour de waitpid non nulle : 
    while(pidRenvoie > 0)
    {
        // suppresion du pid de la tâche morte de la liste des pid des tâches voiturier lancées 
        lesVoituriers.erase(pidRenvoie);

        // Mise à jour zone memoire etatParking : 
        EtatParking nouveauEtat;
        
        nouveauEtat.numero = (WEXITSTATUS(crdu) & 0xF0) >> 4;
        nouveauEtat.usager = usagers[nouveauEtat.numero-1];
        nouveauEtat.arrivee = arrivee[nouveauEtat.numero-1];
        
        //semaphore pour la zone EtatParking -semEtat
        semop ( semMemoire, &reserver, 1 );
        adrEtatParking[WEXITSTATUS(crdu) & 0x0F] = nouveauEtat;
        semop ( semMemoire, &liberer, 1 );
        
         
         
        // Decrementation du nombre de place occupées : 
        //semaphore pour la zone nbPLaces - semNbPLaces
        semop ( semMemoire, &reserver, 1 );
        nbPLacesLibes--;
        *adrPlacesDispo = nbPLacesLibes;
        semop ( semMemoire, &liberer, 1 );

        // Affichage de la nouvelle place de parking occupee : 
        AfficherPlace(WEXITSTATUS(crdu) & 0x0F, nouveauEtat.usager,
            nouveauEtat.numero, nouveauEtat.arrivee);

        // Si une tache voiturier est morte, on constate sa mort : 
        pidRenvoie = waitpid(0, &crdu, 0);
        sleep(TEMPO);
    }
} //----- fin de FinGarage

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void Entree(unsigned int porte, int requetes, int etat,  
    int nbPlaces, int placeLibre, int semMemoire, const char * const CANAL);

// Algorithme :
// - Initialisation : 
//    - Ouverture en lecture du canal arriveeVoiture correspondant (arriveeVoiture[i])
//    - Attachement des zones memoire
//    - Armement du handler DestructionEntree sur le signal SIGUSR2
//    - Armement du handler FinGarage sur le signal SIGCHLD
//    
// - Moteur : 
//    - lecture d'un message sur le canal 
//    - Dessin de la voiture à la barriere
//    
//    - Consultation du nombre de places occupées
//   	 - Si le parking n'est pas plein : 
//        	- appel fonction GarerVoiture
//   	 - Sinon (parking plein)
//        	- formation d'une nouvelle requete
//       	- Mise à jour de la zone memoire Requetes
//       	- Affichage de la requete formulee
//       	- Attente d'une autorisation sur le semaphore placeLibre
//    
//    - enregistrement de son PID dans le set de PID, lesVoituriers
//    - Sommeil pendant <TEMPO> secondes
//
{
    // Phase d'initialisation : 
       

        // Ouverture en lecture du canal : 
        int idCanal;
        //on protege l'appel systeme bloquant open  
       
        while(((idCanal = open ( CANAL, O_RDONLY )) == -1 ) && (errno == EINTR));

        // Attachement de la zone memoire Requetes : 
        Requete * adrRequetes = (Requete *) shmat ( requetes, NULL, 0);

        // Attachement de la zone memoire NbPLaces : 
        unsigned int * adrNbPLaces = (unsigned int *) shmat ( nbPLaces, NULL, 0);

        // Attachement de la zone memoire EtatParking : 
        EtatParking * adrEtatParking = (EtatParking *) shmat ( etatParking, NULL, 0);
        
        
         // Armement du handler DestructionEntree sur le signal SIGUSR2: 
        struct sigaction action;
        action.sa_handler = DestructionEntree;
        sigemptyset ( &action.sa_mask ); 
        action.sa_flags = 0; 
        sigaction ( SIGUSR2, &action, NULL );

        // Armement du handler FinGarage sur le signal SIGCHLD 
        struct sigaction actionGarage;
        actionGarage.sa_handler = FinGarage;
        sigemptyset ( &actionGarage.sa_mask ); 
        sigaddset( &actionGarage.sa_mask, SIGCHLD); 
        actionGarage.sa_flags = 0; 
        sigaction ( SIGCHLD, &actionGarage, NULL );


    // Moteur : 
        TrameVoitureEntree message;
        
        // on initialise la zone memoire qui contient le type de usager 
        // 		et l'instant d'arrivée
        for (unsigned int i = 0; i < NB_PLACES; i++)
        {
            usagers[i] = AUCUN; 
            arrivee[i] = 0;	
        }
        
        
        struct sembuf reserver = { 0 , -1, 0};
        struct sembuf liberer = { 0 , 1, 0};
        
        unsigned int nbPLacesLibes;
        Requete nouvelleRequete;
        
        
        for(;;)
        {  
            // on protege l'appel systeme bloquant read 
            while((read(idCanal, &message, sizeof(TrameVoitureEntree) == -1) && (errno==EINTR));
            
            usagers[message.numero-1] = message.usager;
            arrivee[message.numero-1] = time(NULL);
            
            // Affichage de la voiture а la barriere : 
            DessinerVoitureBarriere( (TypeBarriere)(i+1), message.usager );
            
            // Consultation du nombre de places disponibles : 
			//semaphore pour la zone nbPLaces - semNbPLaces
            
            semop ( semMemoire, &reserver, 1 );
            nbPLacesLibes = *adrNbPLaces;
            semop ( semMemoire, &liberer, 1 );
            
            
       

            // S'il y a une place disponible : 
            if (nbPLacesLibes < NB_PLACES)
            {
				//on appelle la fonction GarerVoiture qui va lancer la tâche voiturier entree 
				//et on enregistre le pid du voiturier lancé
				lesVoitures.insert( GarerVoiture((TypeBarriere)(i+1), message.numero ));
               
			} 
			
			
            else // parking plein
            {
                // formation d'une nouvelle requete : 
                
                if(porte == 0) nouvelleRequete.barriere = PROF_BLAISE_PASCAL ;
				else if(porte == 1 ) nouvelleRequete.barriere = AUTRE_BLAISE_PASCAL ;
				else nouvelleRequete.barriere = ENTREE_GASTON_BERGER ;
                
                nouvelleRequete.usager = message.usager;
                nouvelleRequete.arrivee = arrivee[message.numero-1];
                

                // Mise à jour zone memoire requetes
                //	semaphore pour la zone requetes - semRequetes
                
                semop ( semMemoire, &reserver, 1 );
				adrRequetes[porte] = nouvelleRequete;
				semop ( semMemoire, &liberer, 1 );

                // Affichage de la requete formulee : 
                AfficherRequete ( (TypeBarriere)(i+1), nouvelleRequete.usager, 
                    nouvelleRequete.arrivee );

                // Retrait sur le semaphore placeLibre : 
               
                while((semop ( placeLibre, &reserver, 1 ) == -1) && (errno==EINTR));
            
            }
    
        }
} //----- fin de entree
