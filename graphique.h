#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipement.h"
#include "potion.h"
#include "perso.h"
#include "terrain.h"
#include "tresor.h"
#include "boolean.h"
#include "musique.h"
#include "manip_inventaire.h"
#include "distribution_pts.h"
#include "../inc/clic.h"



/*taille des jauges liées aux attaques*/
#define JAUGE_ATTAQUE 80

	/*Affiche un menu graphique*/
	int menu();

	void initialise_window();

	

	/*affiche les infos du personnage (barre de vie, de mp)*/
	void show_perso(Perso hero);
	
	/* temps d'attente du joueur avant de refaire une action*/
	void attente(void);

	/* renvoie 1 si le joueur peut tomber sur un assaut de monstres et 0 sinon*/
	int random_trap(void);

	void affiche_terrain(int dim_x, int dim_y, Terrain chemin, Perso hero);

	/* affiche l'ensemble des éléments du jeu*/
	void show_game(int dim_x, int dim_y, Terrain chemin, Perso hero);

	void close_window();

	/* cette fonction affiche un msg si le joueur n'a pas suffisamment de mp pour attaquer*/
	void msg_mp(void);
	/* affiche les différentes barrres liées aux actions possibles pendant un combat*/
	/* on affiche aussi un triangle sur le monstre qui est en face du joueur*/
	void barre_combat(void);
	/* affiche la barre indiquant au user qu'il peut fouiller un coffre*/

	

	/* fonction qui affiche graphiquement l'inventaire*/
	/*void show_inventaire(Perso perso, int curseur, int nb_monster);*/

	/*affiche les infos du monstre (barre de vie)*/
	/* numero correspond à l'ordre dans lequel apparait le monstre, cela permet de savoir où placer sa jauge*/
	void show_monster_hp(Monster monster, int numero);
	/* affiche à côté du perso les dégâts subis*/
	void affiche_degats(int x, int y, int degats);

	/* affiche les dégats reçu par le monstre après une attaque*/
	void show_degats_monstre(int numero, int degats);

	/* affiche les dégats reçu par le monstre après une attaque*/
	void show_degats_perso(int degats);

	/* affiche la barre indiquant au user qu'il peut fouiller un coffre*/
	void barre_fouille(void);

	/* permet de passer de coordonnées de coord à une position sur l'écran*/
	int reecrire_coordx_monster(int x, Perso hero);

	/* permet de passer de coordonnées de coord à une position sur l'écran*/
	int reecrire_coordy_monster(int y, Perso hero);

	/* permet de passer de coordonnées de coord à une position sur l'écran*/
	int reecrire_coordx_perso(int x, Perso hero);

	/* permet de passer de coordonnées de coord à une position sur l'écran*/
	int reecrire_coordy_perso(int y, Perso hero);

	/* fonction qui gère l'échange entre un équipement que le héros portait et le nouvel équipement qu'il veut maintenant porter*/
	void changer_equipement(Perso *hero, int i, int j);

	/* fait changer la direction du joueur ou confirme sa fuite, selon son choix*/
	/* renvoie TRUE (0) s'il veut fuir et FALSE (1) si il a seulement changé de direction*/
	int wait_fuite_direction(Perso *perso);



	int wait_event(Perso * perso, Terrain * chemin, int limit_x, int limit_y, Potion tab_potion[MAX_USED_POTION]);
	/* fonction qui gère le combat entre le personnage et un monstre*/
	/* elle renvoie true si le combat continue*/
	/* elle renvoie false si le combat est fini*/

	/* regarde si le joueur a changé de direction en plein combat, si oui on lui demande avec Wait_event s'il veut fuir , si oui il fuit*/
	int fuite_mouv(Perso *perso, Direction old_dir, Terrain * chemin, Coord monster_coords[MAX_MONSTER]);

	/* fonction qui teste si le combat continue ou non*/
	/* fonction qui teste si le combat continue ou non*/
	/* elle renvoie false (0) si le héros fuit, et true (1)sinon*/
	int test_resume_fight(Perso hero, Coord monster_coord);

	/*gère un combat*/
	/* elle renvoie false si le combat est fini*/
	int fight(Perso * hero, Terrain * chemin, Coord monster_coord[MAX_MONSTER], Potion tab_potion[MAX_USED_POTION]);

	

	/* renvoie true si le perso a fait un mouvement directionnel et  qu'il dit ensuite vouloir fuir*/
	int fuit_mouv(Perso *perso, MLV_Keyboard_button touche, Direction old_dir, Terrain * chemin, int limit_x, int limit_y, Potion tab_potion[MAX_USED_POTION]);
	
	
	/*Affiche un message en haut de la fenêtre ainsi que les stats du joueur
	durant la partie*/
	void animation_end(const char * message, Perso hero, Donjon dongeon);
	

	/* fait en sorte qu'une liste de monstre attaquent le perso tour à tour*/
	void list_monster_atk_perso(Perso * hero, Terrain * chemin, Coord monster_coord[MAX_MONSTER]);

	/* fonction qui génère des nouveaux monstres lorsque le user s'est fait piéger*/
	void spawn_monster(Perso hero, Terrain * chemin, Coord monster_coords[MAX_MONSTER]);

	/* génère plusieurs monstre autour du perso lors d'un piège*/
	void piege_monster(Perso hero, Terrain * chemin, Coord monster_found[MAX_MONSTER] , int etage );

	/* Elle modifie (corrige) la position du héros selon les coordonnées du monstre suivant auquel il peut faire face dans le même combat */
	void new_position_fight(Perso * hero, Coord monster_coord);

	/* actualise la position du héro lors d'un mouvement de côté*/
	void actualise_orientation_perso(Perso hero);

	/* Donne la possibilité au user de choisir comment il veut améliorer son personnage après une une montée de niveau*/
	void choice_level_up(Perso *p1);
	
	









#endif