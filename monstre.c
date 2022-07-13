#include "../inc/monstre.h"


/* fonction qui crée un monstre avec des stats qui dépednent de l'étage*/
Monster generate_monster(int lvl){

	int rand_one, rand_two;
	Monster monster;

	/* les dégâts des monstres sont incrémentés de 10 par étage*/
	rand_one = ((rand() % 30) + ((lvl+1) * MONSTER_MIN_HP));
	/* l'attaque d'un monstre fait un dégât de 10*niveau de l'étage+/-10 +2*/
	rand_two = 2+((rand() % 10) + (lvl * 10));

	monster.hp = rand_one;
	monster.max_hp = rand_one;
	
	monster.atk = rand_two;
	monster.gain_exp = 0;

	return monster;	
}

/* indique si le monstre a fait un coup critique ou non*/
/* si elle renvoie true (1) cela signifie que le coup est critique*/
int critique_monstre(){
	int res;
	res = rand() % 100;
	/* il y a 5% de chance pour que le coup soit critique*/
	if(res <= 4)
		return TRUE;
	return FALSE;
}


/* indique une position vide dans le tableau où sont enregistrées les coordonnées des monstres attaqués*/
/* elle renvoie la position vide, s'il n'y en a pas, -1*/
int empty_monster(Coord monster_coords[MAX_MONSTER]){
	int i;
	/* on regarde les emplacements non vide*/
	for(i=0;i< MAX_MONSTER;i++){
		if(monster_coords[i].x == -1 && monster_coords[i].y == -1){
		/* on renvoie le premier emplacement vide*/
			return i;
		}
	}
	/* il n'y a pas d'emplacement vide*/
	return -1;
}
/* retire un monstre dans le tableau où sont enregistrées les coordonnées des monstres attaqués*/
void retire_monster(Coord monster_coords[MAX_MONSTER], Coord monster){
	int i;
	for(i = 0 ; i < MAX_MONSTER ; i++){
		if(monster_coords[i].x == monster.x && monster_coords[i].y == monster.y){
			monster_coords[i].x =-1;
			monster_coords[i].y = -1;
			break;

		}
	}

}
/* vide entièrement le tableau des monstres dans le tableau où sont enregistrées les coordonnées des monstres attaqués*/
void vide_tab_monster(Coord monster_coords[MAX_MONSTER]){
	int i;
	/* on vide en mettant toutes les valeurs -1*/
	for(i=0;i< MAX_MONSTER;i++){
		monster_coords[i].x = -1;
		monster_coords[i].y = -1;
	}

}

/* return 1 si le monstre est déjà dans le tableau, sinon return 0*/
int already_in(Coord monster_coords[MAX_MONSTER], Coord monster){
	int i;

	for(i = 0; i < MAX_MONSTER; i++){
		/* cas où le monstre est présent dans le tableau*/
		if(monster_coords[i].x == monster.x && monster_coords[i].y == monster.y)
			return 1;
	}
	/* cas où le monstre n'est pas présent dans le tableau*/
	return 0;
}
/* ajoute un monstre dans le tableau où sont enregistrées les coordonnées des monstres attaqués*/
void add_monster(Coord monster_coords[MAX_MONSTER], Coord monster){
	int i;
	/* on vérifie que le monstre n'est pas déjà là, si c'est le cas on sort de la fonction*/
	if(already_in(monster_coords,monster) == 1)
		return;
	i = empty_monster(monster_coords);
	if(i == -1)
		return;
	monster_coords[i].x = monster.x;
	monster_coords[i].y = monster.y;


}

/* enregistre les coordonnées du premier monstre du tableau*/
void first_monster(Coord monster_coords[MAX_MONSTER], Coord * monster){
	int i;
	for(i=0;i<MAX_MONSTER;i++){
		if(monster_coords[i].x != -1 || monster_coords[i].y != -1){
			monster->x = monster_coords[i].x;
			monster->y = monster_coords[i].y;
			return;
		}
	}
		
}
/* elle renvoie 0 si le tableau n'est pas vide c'est à dire qu'il y a encore des monstres*/
/* elle renvoie 1 sinon*/

int is_empty_tab_monster(Coord monster_coords[MAX_MONSTER]){
	int i;
	for(i=0;i< MAX_MONSTER;i++){
	/* on détecte un monstre*/
		if(monster_coords[i].x != -1 || monster_coords[i].y != -1)
			return 0;
	}
	/* il n'y a pas de monstre*/
	return 1;

}

/* fonction qui crée des monstres avec des stats qui dépedent de l'étage*/
/* ces monstres apparaissent lors de pièges et donne 0 exp mais font peu de dégâts*/
Monster generate_trap_monster(int lvl){

	int rand_one, rand_two;
	Monster monster;

	/* les dégâts des monstres sont incrémentés de 10 par étage*/
	rand_one = MONSTER_MIN_HP/2;
	/* l'attaque d'un monstre fait un dégât de 2*niveau */
	rand_two = (lvl * 2);

	monster.hp = rand_one;
	monster.max_hp = rand_one;
	
	monster.atk = rand_two;
	monster.gain_exp = 0;

	return monster;	
}