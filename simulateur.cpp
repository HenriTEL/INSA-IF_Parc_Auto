/*************************************************************************
                           simulateur  -  description
                             -------------------
    début                : 18 Février 2014
    copyright            : (C) 2014 par Maria ETEGAN	
    e-mail               : maria.etegan@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la tâche <simulateur> (fichier simulateur.cpp) ---

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

//------------------------------------------------------ Include personnel
#include "simulateur.h"
#include "/public/tp/tp-multitache/Menu.h"



///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes



//------------------------------------------------------------------ Types
struct TrameVoitureEntree
{
    TypeBarriere barriere;
    TypeUsager usager;
    unsigned int numero;
};

struct TrameVoitureSortie
{
    unsigned int numero;
};


//---------------------------------------------------- Variables statiques
static int arriveeVoiture[NB_BARRIERES_ENTREE]; 
static int sortieVoiture;


//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void simulateur( const char * CHEMIN_CANAUX_SORTIE_VOITURE, const char ** CHEMIN_CANAL_ARRIVEE_VOITURE )
// Algorithme :
//		Initialisation : ouverture des canaux 
// 		Moteur : appel Menu
//
{
    // Initialisation :
    // ouverture des canaux de communication avec la tâche entree
    // le premier canal (arriveeVoiture[0]) pour la barriere PROF_BLAISE_PASCAL 
    // le deuxieme canal (arriveeVoiture[1]) pour la barriere AUTRE_BLAISE_PASCAL
    // le troisieme canal (arriveeVoiture[2]) pour la barriere ENTREE_GASTON_BERGER 
    
    for ( int i = 0 ; i < NB_BARRIERES_ENTREE ; i++ )
    {
       arriveeVoiture[i] = open(CHEMIN_CANAL_ARRIVEE_VOITURE[i],O_WRONLY);
    }
    // ouverture du canal de communication avec la tâche sortie
    sortieVoiture = open(CHEMIN_CANAUX_SORTIE_VOITURE,O_WRONLY);

    // Moteur :
    for(;;)
    {
        Menu();
    }
} //----- fin de simulateur


void Commande ( char code, unsigned int valeur )
// Algorithme :
// on utilise une variable statique noVoiture qui gère le numéro d'un voiture 
// elle sera incremente chaque fois qu'une voiture demande d'être garée
// Valeur du code autorisés
// 'Q' : ferme les canaux et finit l'application
// 'P', 'A' : met un message dans le canal de communication avec l'entree correspondante et incrementation du noVoiture   
// 'S' : met un message dans le canal de communication avec la sortie 
//
{
    static unsigned int noVoiture = 1;
    TrameVoitureEntree msgEntree;
    switch ( code )
    {
        case 'P' :
			//entree d'un prof
            msgEntree.usager = PROF;
            msgEntree.numero = noVoiture++;
            if(noVoiture == NB_PLACES + 1)
            {	
				//les voitures doivent avoir un numero compris entre 1 et NB_PLACES 
				//si noVoiture depasse NB_PLACES on reinitialise noVoiture à 1
                noVoiture = 1;
            }
            //en fonction de la valeur de l'entier passé en paramétre on écrit dans le canal de l'entree correspondante 
			if(valeur == 1){
				msgEntree.barriere = PROF_BLAISE_PASCAL;
				write(arriveeVoiture[0],&msgEntree,sizeof(TrameVoitureEntree));
			}
			else if(valeur == 2){
				msgEntree.barriere = ENTREE_GASTON_BERGER;
				write(arriveeVoiture[2],&msgEntree,sizeof(TrameVoitureEntree));
			}
            break;
            
            
        case 'A' :
            // Entree d'un usager AUTRE
            msgEntree.usager = AUTRE;
            msgEntree.numero = noVoiture++;
            
            if(noVoiture == NB_IMMATRICULATIONS + 1)
            {
                noVoiture = 1;
            }
            if(valeur == 1)
            {
				msgEntree.barriere = AUTRE_BLAISE_PASCAL;
			}
			else if(valeur == 2) 
			{
				msgEntree.barriere = ENTREE_GASTON_BERGER;
			}
				
            write(arriveeVoiture[valeur],&msgEntree,sizeof(TrameVoitureEntree));
            break;
            
            
        case 'S' :
            // Sortie d'un usager
            write(canalSortie,&valeur,sizeof(valeur));
            break;
            
        case 'Q':
            // Destruction :
            //  fermeture des canaux
            close(sortieVoiture);
            for ( int i = 0 ; i < NB_BARRIERES_ENTREE ; i++ )
            {
                close(arriveeVoiture[i]);
            }
            // autodestruction
            exit(0);
            break;
    }
}


