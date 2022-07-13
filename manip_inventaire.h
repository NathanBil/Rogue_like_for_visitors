#ifndef __MANIP_INVENTAIRE__
#define __MANIP_INVENTAIRE__

#include <MLV/MLV_all.h>

#include "equipement.h"
#include "potion.h"
#include "perso.h"
#include "terrain.h"
#include "tresor.h"
#include "boolean.h"
#include "musique.h"
#include "taille.h"


/* fonction qui affiche graphiquement l'inventaire*/
void show_inventaire(Perso perso, int curseur, int nb_monster);

/* fonction qui gère les actions du perso quand il veut voir son inventaire*/
void modifier_inventaire(Perso *perso, Potion tab_potion[MAX_USED_POTION], int monstre_leftover);

/* gère les cliques dans l'inventaire*/
int clic_invent(int x, int y, char mode);

/*affiche les infos du personnage dans l'inventaire (barre de vie, de mp)*/
void show_perso2(Perso hero);

/* affiche les monstres restant sur la map avec un logo*/
void monstre_restant(int restant);

/* remplace les stats du perso par un rectangle noir qu'il faudra ensuite remplir par une image de ses stats.
	Cette fonction sert pour les updates*/
void erase_perso();

/*Renvoie vrai si le clic se trouve dans le carré de l'inventaire*/
int is_in_square_inv(int clic_x, int clic_y, int x_0, int x_n, int y_0, int y_n);

#endif