#ifndef __MONSTRE__
#define __MONSTRE__

	#include <stdlib.h>
	#include "boolean.h"
	#include "coordonnees.h"

	#define MONSTER_MIN_HP 100
	#define MAX_MONSTER 4
	typedef  struct monster {
		int hp;
		int max_hp;
		int atk;
		int gain_exp;
		
	}Monster;

	/* fonction qui crée un monstre avec des stats qui dépednent de l'étage*/
	Monster generate_monster(int lvl);
	/* indique si le monstre a fait un coup critique ou non*/
	/* si elle renvoie 1 cela signifie*/
	int critique_monstre();

	/* indique une position vide dans le tableau où sont enregistrées les coordonnées des monstres attaqués*/
	int empty_monster(Coord monster_coords[MAX_MONSTER]);
	/* retire un monstre dans le tableau où sont enregistrées les coordonnées des monstres attaqués*/
	void retire_monster(Coord monster_coords[MAX_MONSTER], Coord monster);
	/* vide entièrement le tableau des monstres dans le tableau où sont enregistrées les coordonnées des monstres attaqués*/
	void vide_tab_monster(Coord monster_coords[MAX_MONSTER]);

	/* return 1 si le monstre est déjà dans le tableau, sinon return 0*/
	int already_in(Coord monster_coords[MAX_MONSTER], Coord monster);

	/* elle renvoie 0 si le tableau n'est pas vide c'est à dire qu'il y a encore des monstres*/
	/* elle renvoie 1 sinon*/
	int is_empty_tab_monster(Coord monster_coord[MAX_MONSTER]);

	/* enregistre les coordonnées du premier monstre du tableau*/
	void first_monster(Coord monster_coords[MAX_MONSTER], Coord * monster);

	/* ajoute un monstre dans le tableau où sont enregistrées les coordonnées des monstres attaqués*/
	void add_monster(Coord monster_coords[MAX_MONSTER], Coord monster);

	/* fonction qui crée des monstres avec des stats qui dépedent de l'étage*/
	/* ces monstres apparaissent lors de pièges et donne 0 exp mais font peu de dégâts*/
	Monster generate_trap_monster(int lvl);

	
#endif