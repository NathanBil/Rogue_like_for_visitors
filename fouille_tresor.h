#ifndef __FOUILLE_TRESOR__
#define __FOUILLE_TRESOR__

	#include <MLV/MLV_all.h>

	#include "equipement.h"
	#include "potion.h"
	#include "perso.h"
	#include "terrain.h"
	#include "tresor.h"
	#include "boolean.h"
	#include "musique.h"
	#include "graphique.h"
	#include "taille.h"




/* affiche visuellement le contenu du coffre*/
void show_coffre(Treasure coffre[NB_TRESOR], int curseur);

/* fonction qui gère la modification d'un coffre au trésor fouillé par le user*/
int modif_tresor(Perso * hero, Terrain * chemin, Coord tresor_found);

/* fonction qui réalise la récupération du trésor une fois que le joueur a choisi de fouiller le coffre*/
void fouille(Perso * hero, Terrain * chemin, Coord tresor_found);

/*Donne la possibilité au joueur de fouiller un coffre au trésor*/
/* renvoie l'action du joueur*/
int decouverte(Perso * hero, Terrain * chemin, Coord monster_coord, Potion tab_potion[MAX_USED_POTION], int sound_off, MLV_Sound * tab_sound[NB_SOUND]);

/* fonction qui gère l'ajout du trésor à l'inventaire*/
int add_tresor(Perso * hero, Terrain * chemin, int i , Coord tresor_found);

/* fonction qui dit si oui ou non un coffre est vide*/
/* elle renvoie 1 si oui et 0 si non*/
int empty_coffre(Treasure tresor[NB_TRESOR]);


#endif