#include "../inc/perso.h"



void initialise_stats(Perso* hero){

	(hero->stats).monster_killed = 0;
	(hero->stats).treasures_opened = 0;
}


/* initalise le personnage lors de la première partie avec son niveau, ses pv etc...*/
Perso initialise_pt_perso(void){
	Perso p1;
	p1.hp = 100;
	p1.mp = 50;
	p1.atk = 10;
	p1.inte = 10;
	p1.def = 10;
	p1.exp = 0;
	p1.lv = 1;
	p1.boost = 5;
	p1.boost_exp = 0;

	initialise_stats(&p1);

	return p1;
}






/*HP ET MP ont une valeur maxiamle de 10 * DEF pour Hp et 10 * Int - 50 pour */



/*exp ACCUMULÉE À CHAQUE VICTOIRE EN COMBAT  ET EST DÉPENDÉ POUR MONTER LE NIVEAU*/



/*Pour passer du Lv n au Lv n + 1 necessite 350 + 50 x n  Exp*/


/*À chaque niveau monté on a les jauges HP, MP à leur max et ocroie 3 points à affecter librement aux attributs Atk, Int, Def*/



/* met à jour les pts du personnage en fonction de son niveau*/
void update_perso(Perso *p1){
	(*p1).hp = 10*(p1->def);
	(*p1).mp = 10*(p1->inte)-50;
	/*p1->lv++;*/
}

/* fonction qui donne le nombre de hp maximum du personnage en fonction de ses stats de défense*/
int max_hp(Perso p1){
	return 10*(p1.def);
}

/* fonction qui donne le nombre de mp maximum du personnage en fonction de ses stats d'inte*/
int max_mp(Perso p1){
	return 10*(p1.inte)-50;
}


/* renvoie le pourcentage d'exp du joueur par rapport au pourcentage d'exp nécessaire pour augmenter un niveau*/
int pourcentage_xp(Perso p1){
	int pourcent;
	int lvl_up;
	int joueur_exp;
	/* correspond à ce qu'il faut pour monter en niveau*/
	lvl_up = 350+(50*p1.lv);
	joueur_exp = p1.exp;
	/* pourcentage d'exp du joueur*/
	pourcent = (joueur_exp*100)/lvl_up;
	return pourcent;

}
/* initialise l'inventaire du héros en le rendant vide et lui donne aussi ses premiers équipements*/
/* l'argument est le personnage qui reçoit les équipements et l'inventaire vide*/
void initialise_inventaire_equipement(Perso * p1){
	int j;
	/* on inititalise l'inventaire des équipements avec des emplacements vides*/
	for(j= 0; j< SIZE_INVENTAIRE;j++){
			p1->invent[0][j].eq = generateur_arme_null();
	}
	p1->invent[0][0].eq = generateur_first_arme();
	p1->invent[0][1].eq = generateur_first_baguette();
	p1->invent[0][2].eq = generateur_first_armure();
	printf("l'inventaire des équipements est  : \n\n\n\n");
	show_equipement(p1->invent[0][0].eq);
	show_equipement(p1->invent[0][1].eq);
	show_equipement(p1->invent[0][2].eq);

	
}

/* initialise l'inventaire du héros en le rendant vide et lui donne aussi ses premiers équipements*/
/* l'argument est le personnage qui reçoit les équipements et l'inventaire vide*/
void initialise_inventaire_potion(Perso * p1){
	int j;
	/* on inititalise l'inventaire avec des emplacements vides*/
	for(j= 0; j< SIZE_INVENTAIRE;j++){
		p1->invent[1][j].pot = generateur_potion_null();
	}	
}

/* vérifie si le tab_potion est vide*/
/* renvoie true si oui (0) et false sinon (1)*/
int empty_tab(Potion tab_potion[MAX_USED_POTION]){
	int i;
	for(i = 0; i<  MAX_USED_POTION; i++){
		if(tab_potion[i].exists == TRUE)
			return FALSE;
	}
	return TRUE;
}
/* met à jour les objets portés par le joueur*/
void mise_a_jour_stuff(Perso *p1, Potion tab_potion[MAX_USED_POTION]){
	int i;
	int j;
	p1->invent[2][0].eq = p1->arme;
	p1->invent[2][1].eq = p1->armure;
	p1->invent[2][2].eq = p1->baguette;
	/* on commence à partir de l'emplacement pour les potions*/
	/* il y en a au maximum trois en même temps même si on permis au tableau d'avoir 5 potions*/
	j = 0;
	for(i = 3; i < SIZE_INVENTAIRE; i++){
		p1->invent[2][i].pot = tab_potion[j];
		j++;
	}
	


}
/* initialise les équipements que porte le héros*/
/* l'argument est le personnage qui met ses équipements*/
void initialise_objet_porte(Perso * p1){
	int j;
	/* on inititalise l'inventaire avec des équipements et des potions vides pour les potions en cours d'utilisation*/
	/* ici les potions*/
	for(j= 3; j< SIZE_INVENTAIRE;j++){
		p1->invent[2][j].pot = generateur_potion_null();
	}	
	/*ici les équipements portés par le joueur*/
	for(j= 0; j< 3;j++){
		p1->invent[2][j].eq = generateur_arme_null();
	}	
}



/*initialise le perso et ses coordonnées*/
void initialise_perso(Perso * perso, int x, int y){
	(*perso) = initialise_pt_perso();
	initialise_inventaire_equipement(perso);
	initialise_inventaire_potion(perso);
	perso->coord.x = x;
	perso->coord.y = y;
	perso->direction = NORD;
	/* on équipe le personnage avec des armes de plus bas_niveau*/
	perso->arme =  generateur_arme_null();
	perso->armure =  generateur_armure_null();
	perso->baguette =  generateur_baguette_null();
	initialise_objet_porte(perso);
}

/* cette fonction dit si oui ou non un emplacement vide a été trouvé dans l'inventaire des armures*/
/* elle remplit les variables x et y avec les coordonnées de cet emplacement*/
/* elle renvoie true si un emplacement a été trouvé*/
/* elle renvoie false si non*/
int find_empty_place_1(Perso p1, int *x, int *y){
	int j;
	for(j= 0; j< SIZE_INVENTAIRE;j++){
		/* cas où un emplacement vide a été trouvé*/
		/* on renvoie true*/
		if(p1.invent[0][j].eq.exists == FALSE){
			*x = 0;
			*y = j;
			return TRUE;
		}
	}
	/* cas où l'inventaire est plein, on a échoué pour trouver un emplacement vide*/
	*y = 0;
	*x = 0;
	return FALSE;

}

/* cette fonction dit si oui ou non un emplacement vide a été trouvé dans l'inventaire des potions*/
/* elle remplit les variables x et y avec les coordonnées de cet emplacement*/
/* elle renvoie true si un emplacement a été trouvé*/
/* elle renvoie false si non*/
int find_empty_place_2(Perso p1, int *x, int *y){
	int j;
	for(j= 0; j< SIZE_INVENTAIRE;j++){
		/* cas où un emplacement vide a été trouvé*/
		/* on renvoie true*/
		if(p1.invent[1][j].pot.exists == FALSE){
			*x = 1;
			*y = j;
			return TRUE;
		}
	}
	/* cas où l'inventaire est plein, on a échoué pour trouver un emplacement vide*/
	*y = 0;
	*x = 1;
	return FALSE;

}

/* cette fonction affiche l'ensemble des éléments de l'inventaire des équipements*/
void show_inventaire_equipement(Perso p1){
	int j;
	Equipement eq1;
	int vide = 1;
	printf("Le contenu de l'inventaire des équipements est : \n");
	for(j= 0; j< SIZE_INVENTAIRE;j++){
		/* cas où un emplacement non vide est trouvé*/
		/* on renvoie true*/
		if(p1.invent[0][j].eq.exists == TRUE){
			eq1 = p1.invent[0][j].eq;
			show_equipement(eq1);
			vide = 0;
		}
	}
	if(vide == 1)
		printf("Votre inventaire des équipements est vide.\n");
}

/* cette fonction affiche l'ensemble des éléments de l'inventaire des potions*/
void show_inventaire_potion(Perso p1){
	int j;
	Potion pot1;
	int vide = 1;
	printf("Le contenu de l'inventaire des potions est : \n");
	for(j= 0; j< SIZE_INVENTAIRE;j++){
		/* cas où un emplacement non vide est trouvé*/
		/* on renvoie true*/
		if(p1.invent[1][j].pot.exists == TRUE){
			pot1 = p1.invent[1][j].pot;
			show_potion(pot1);	
			vide = 0;
		}
	}
	if(vide == 1)
		printf("Votre inventaire des potions est vide. \n");
}


void deplacement_perso(Perso * perso, Direction direction, int limit_x, int limit_y){

	switch(direction){
		case NORD: {
			if(perso->coord.y > 0){
				perso->coord.y -= 1;
			}

			break;
		}

		case SUD: {
			if(perso->coord.y < limit_y -1){
				perso->coord.y += 1;
			}

			break;
		}

		case EST: {
			if(perso->coord.x < limit_x - 1){
				perso->coord.x += 1;
			}

			break;
		}


		case OUEST: {
			if(perso->coord.x > 0){
				perso->coord.x -= 1;
			}

			break;
		}
	}
}

/* fonction qui vérifie si le personnage est mort*/
/* renvoie 0 si il est mort*/
/* elle renvoie 1 si il est en vie e*/
int is_character_dead(Perso character){
	if(character.hp <= 0){
		return 0;
	}
	return 1;
}


int monster_atk_perso(Perso * perso, Monster monster, int *degats){

	/* variable qui contient le total des dégats réalisés par le monstre en prenant en compte les facteurs aléatoires*/
	int monster_damage;
	/* min est le minimum en terme de pourcentage que l'attaque du joueur doit représenter par rapport à l'attaque totale du joueur*/
	float min;
	/* facteur est le nombre de pourcentage en plus du minimum que l'attaque du joueur va faire*/
	/* l'attaque peut atteindre 120% de la puissance initiale*/
	float facteur;
	/* variable indiquant si l'attaque sera critique ou non*/
	int critique;
	min = 80;
	facteur = rand() % 41;
	critique = critique_monstre();
	/* on divise par 100 le facteur et le min pour arriver à un pourcentage : 1,20 (120%) au maximum ou 0,80 (80%)au minimum*/
	monster_damage = (monster.atk)*((facteur+min)/100);
	if(critique == TRUE)
		monster_damage *= 3;

	if(perso->hp <= monster_damage){
		perso->hp = 0;
	}else{
		perso->hp = perso->hp - monster_damage;
	}
	/*printf("L'atk du monstre est de %d \n" , monster.atk);*/
	/*printf("Le dommage du monstre est de %d \n" , monster_damage);*/
	*degats = monster_damage;
	return monster_damage;
}

/* indique si le monstre a fait un coup critique ou non*/
/* si elle renvoie true cela signifie que le coup est critique*/
/* boost correpsond à un pourcentage de chance de faire une attaque critique de 15%
il est lié à un boost permis par une potion*/
int critique_hero(Perso hero){
		int res;
		res = rand() % 100;
		/* il y a 5% à 15% de chance pour que le coup soit critique en fonction de si le
		joueur a pris ou non une potion de boost*/
		if(res <= hero.boost-1)
			return TRUE;
		
		return FALSE;
}

/* fonction qui calcule la puissance de l'attaque normale du joueur*/
/* elle renvoie la valeur de l'attaque du joueur*/
int perso_atk_melee(Perso hero){
		/* min est le minimum en terme de pourcentage que l'attaque du joueur doit représenter par rapport à l'attaque totale du joueur*/
		float min;
		/* facteur est le nombre de pourcentage en plus du minimum que l'attaque du joueur va faire*/
		/* l'attaque peut atteindre 120% de la puissance initiale*/
		float facteur;
		/* variable qui contient le total des dégats réalisés par le joueur en prenant en compte les facteurs aléatoires*/
		int hero_damage;
		/* variable indiquant si l'attaque sera critique ou non*/
		int critique;
		min = 80;
		facteur = rand() % 41;
		critique = critique_hero(hero);
		/* on divise par 100 le facteur et le min pour arriver à un pourcentage : 1,20 (120%) au maximum ou 0,80 (80%)au minimum*/
		hero_damage= ((hero.atk + hero.arme.atk)*((facteur+min)/100));
		if(critique == TRUE)
			return hero_damage*3;
		return hero_damage;
}

/* fonction qui gère la perte de vie du monstre en fonction de la puissance d'attaque du joueur*/
/* elle renvoie true or false selon si l'attaque est autorisée, pour ce type d'attaque c'est toujours autorisé*/
int perso_atk_melee_monster(Perso *hero, Monster * monster, int * degats){
	int boost_joueur;
	*degats = perso_atk_melee(*hero);
	monster->hp -= *degats;
	if(monster->hp <= 0){
		monster->hp = 0;
		boost_joueur = (hero->boost_exp +100);
		hero->exp += ((monster->gain_exp)*boost_joueur)/100;
		level_up(hero);
	}
	return TRUE;
}

/* fonction qui calcule la puissance de l'attaque magique du joueur*/
/* elle renvoie la valeur de l'attaque magique du joueur*/
int perso_atk_magique(Perso hero){
		/* min est le minimum en terme de pourcentage que l'attaque du joueur doit représenter par rapport à l'attaque totale du joueur*/
		float min;
		/* facteur est le nombre de pourcentage en plus du minimum que l'attaque du joueur va faire*/
		/* l'attaque peut atteindre 120% de la puissance initiale*/
		float facteur;
		/* variable qui contient le total des dégats réalisés par le joueur en prenant en compte les facteurs aléatoires*/
		int hero_damage;
		/* variable indiquant si l'attaque sera critique ou non*/
		int critique;
		min = 80;
		facteur = rand() % 41;
		critique = critique_hero(hero);
		/* on divise par 100 le facteur et le min pour arriver à un pourcentage : 1,20 (120%) au maximum ou 0,80 (80%)au minimum*/
		hero_damage= 2*((hero.inte)*((facteur+min)/100));
		if(critique == TRUE)
			return hero_damage*3;
		return hero_damage;
}

/* fonction qui gère la perte de vie du monstre en fonction de la puissance d'attaque magique du joueur*/
/* elle renvoie true or false selon si l'attaque est autorisée, c'est à dire si le joueur a assez suffisamment d'mp ou non*/
int perso_atk_magique_monster(Perso *hero, Monster * monster , int * degats){
	int boost_joueur;
	if(hero->mp < 20)
		return FALSE;
	*degats = perso_atk_magique(*hero);
	monster->hp -= *degats;
	hero->mp -= 20;
	if(monster->hp <= 0){
		monster->hp = 0;
		boost_joueur = (hero->boost_exp +100);
		hero->exp += ((monster->gain_exp)*boost_joueur)/100;
		level_up(hero);
	}
	return TRUE;
}

/* fonction qui gère l'ajout d'un équipement dans l'inventaire*/
void add_equipement_invent(Perso * hero, Equipement eq1,int x, int y){
	/*show_equipement(eq1);*/
	hero->invent[x][y].eq = eq1;
}
/* fonction qui gère l'ajout d'une potion dans l'inventaire*/
void add_potion_invent(Perso * hero, Potion pot1,int x, int y){
	/*show_potion(pot1);*/
	hero->invent[x][y].pot = pot1;
}

/* retire l'objet associé aux cases x et y de l'inventaire des potions*/
void retire_potion_invent(Perso *hero, int y){
	hero->invent[1][y].pot = generateur_potion_null();
	printf("L'objet a été retiré de l'inventaire");
}

/* retire l'objet associé aux cases x et y de l'inventaire des équipements*/
void retire_equipement_invent(Perso *hero, int y){
	hero->invent[0][y].eq = generateur_arme_null();
	printf("L'objet a été retiré de l'inventaire");

}



/* fonction qui gère le temps durant lequel une potion applique ses effets et s'assure que l'effet s'applique correctement*/
/*void active_potion(Perso *hero, Potion pot){

}*/

/* fonction qui gère l'échange entre un équipement que le héros portait et le nouvel équipement qu'il veut maintenant porter*/
void changer_equipement(Perso *hero, int i, int j){
	Equipement eq1;
	int old_hp;
	int old_mp;
	old_hp = hero->hp;
	old_mp = hero-> mp;
	/* cas où les coordonnées ne correspondent pas à un équipement*/
	/* ce n'est pas censé arriver*/
	if(i != 0)
		return;
	/*printf("On affiche les équipements que le joueur va retirer \n");*/
	/* cas où on échange des armes*/
	if(hero->invent[i][j].eq.type == ARME && hero->invent[i][j].eq.exists == TRUE){
		/* si le héros n'est pas équipé on lui ajoute une arme*/
		if(hero->arme.exists == FALSE){
			hero->arme = hero->invent[i][j].eq;
			/* l'ancien emplacement est vidé*/
			hero->invent[i][j].eq = generateur_arme_null();
		}
		/* si le héros est équipé on échange les armes*/
		else{
			eq1 = hero->invent[i][j].eq;
			hero->invent[i][j].eq = hero->arme;
			hero->arme = eq1;
		}
		/*printf("Vous avez changé d'équipement ! \n");*/

	}
	/* cas où on échange des baguettes*/
	else if(hero->invent[i][j].eq.type == BAGUETTE && hero->invent[i][j].eq.exists == TRUE){
		/* si le héros n'est pas équipé on lui ajoute une baguette*/
		if(hero->baguette.exists == FALSE){
			hero->baguette = hero->invent[i][j].eq;
			/* l'ancien emplacement est vidé*/
			hero->invent[i][j].eq = generateur_baguette_null();
			hero->inte+= hero->baguette.inte;
		}
		/* si le héros est équipé on échange les baguettes*/
		else{
			eq1 = hero->invent[i][j].eq;
			/* on retire l'intelligence conférée par la baguette*/
			hero->inte-= hero->baguette.inte;
			hero->invent[i][j].eq = hero->baguette;
			hero->baguette = eq1;
			hero->inte+= hero->baguette.inte;
			/* on retire l'intelligence anciennement conféré par la baguette*/

		}
		/*printf("Vous avez changé d'équipement ! \n");*/
	}
	/* cas où on échange des armures*/
	else if(hero->invent[i][j].eq.type == ARMURE && hero->invent[i][j].eq.exists == TRUE){
		/* si le héros n'est pas équipé on lui ajoute une armure*/
		if(hero->armure.exists == FALSE){
			hero->armure = hero->invent[i][j].eq;
			/* l'ancien emplacement est vidé*/
			hero->invent[i][j].eq = generateur_armure_null();
			hero->def+= hero->armure.def;

		}
		/* si le héros est équipé on échange les armure*/
		else if(hero->armure.exists == TRUE){
			eq1 = hero->invent[i][j].eq;
			/* on retire la défense conférée par l'armure */
			hero->def-= hero->armure.def;
			hero->invent[i][j].eq = hero->armure;
			hero->armure = eq1;
			hero->def+= hero->armure.def;
		}
		/*printf("Vous avez changé d'équipement ! \n");*/
	}
	if(max_hp(*hero)<old_hp){
		hero->hp = max_hp(*hero);
	}
	else{
		hero->hp = old_hp;
	}
	if(max_mp(*hero) < old_mp){
		hero->mp = max_mp(*hero);
	}
	else{
		hero->mp = old_mp;
	}

}


/* fonction qui gère l'activation d'une potion*/
void active_potion(Perso * hero,Potion *pot){
	/* cas où on tombe sur une potion vide*/
	if(pot->exists != TRUE)
		return;
	/*printf("Vous buvez actuellement : \n");*/
	show_potion(*pot);
	if(pot->tour <= 0){
		*pot = generateur_potion_null();

		return;
	}
	/* question ??: est-ce que le temps va s'écouler pour toutes les potions lorsque j'en boirai une ??*/
	/* on augmente le temps écoulé car utiliser cette fonction revient à faire passer 1 seconde*/
	pot->temps_e++;
	/* cas où la potion ne peut pas faire son effet maintenant car il faut encore attendre*/
	if(pot->delai > pot->temps_e){
		/* on diminue le nombre de tour pour lesquels la potion peut s'appliquer*/
		pot->tour--;
		/* la potion devient null*/
		if(pot->tour <= 0){
			*pot = generateur_potion_null();
			return;
		}
		return;
		
	}

	/* cas où la potion peut  faire son effet maintenant car il suffisamment de temps s'est écoulé*/
	if(pot->pourcentage == TRUE){
		/* on ajoute des hp en fonction du pourcentage de la potion*/
		hero->hp += (max_hp(*hero)*(pot->hp))/100;
		/* on évite de dépasser le nombre max de hp*/
		if(hero->hp > max_hp(*hero))
			hero->hp = max_hp(*hero);
		/* on ajoute des mp en fonction du pourcentage de la potion*/
		hero->mp += (max_mp(*hero)*(pot->mp))/100;
		/* on évite de dépasser le nombre max de mp*/
		if(hero->mp > max_mp(*hero))
			hero->mp = max_mp(*hero);
		/* on change le pourcentage de chance de faire une attaque critique*/
		hero->boost = pot->critique;
	}

	else if(pot->pourcentage == FALSE){
		/* on ajoute des hp en fonction du pouvoir de la potion*/
		hero->hp += pot->hp;
		if(hero->hp > max_hp(*hero))
			hero->hp = max_hp(*hero);
		/* on ajoute des mp en fonction du pouvoir de la potion*/
		hero->mp += pot->mp;
		if(hero->mp > max_mp(*hero))
			hero->mp = max_mp(*hero);
		/* on change le pourcentage de chance de faire une attaque critique*/
		hero->boost = pot->critique;

	}

	if(pot->type == APPRENTISSAGE){
		/*printf(" *gloup gloup* Vous avez utilisé une potion d'apprentissage qui monte l'exp \n");*/
		hero->boost_exp = pot->exp;
	}

	if(pot->type == PRECISION_POT){
		/*printf(" *gloup gloup * Vous avzez utilisé une potion de precision qui monte la precision \n");*/
		hero->boost = pot->critique;
		/*printf("le boost du héros vaut maitenant : %d \n" , hero->boost);*/
	}
	/* le temps écoulé revient à 0*/
	pot->temps_e = 0;

	/* on diminue le nombre de tour pour lesquels la potion peut s'appliquer*/
	pot->tour--;
	/* la potion devient null*/
	if(pot->tour <= 0){
		if(pot->type == PRECISION_POT){
			/*printf("Les effets de la potion de précision se sont dissipés !  \n");*/
			hero->boost = 5;
		}
		else if(pot->type == APPRENTISSAGE){
			/*printf("Les effets de la potion d'apprentissage se sont dissipés ! \n");*/
			hero->boost_exp = 0;
		}
		/*printf("La potion est maintenant vide : \n");*/
		*pot = generateur_potion_null();
		/*show_potion(*pot);*/
		return;
	}

	return;
	
}

/* fonction qui gère l'activation des potions du tableau des potions*/
void active_tab_potion(Perso * hero, Potion tab_potion[MAX_USED_POTION]){
	int i;

	if(tab_potion == NULL){
		return;
	}

	for(i = 0; i< MAX_USED_POTION; i++){
		if(tab_potion[i].exists == TRUE){
			/* on récupère le nouvel état de la potion*/
			active_potion(hero, &tab_potion[i]);
			mise_a_jour_stuff(hero, tab_potion);
		}
	}
}

/* fonction qui gère l'activation de la dernière potion bu par le héros sans attendre un tour*/
void active_last_potion(Perso * hero, Potion tab_potion[MAX_USED_POTION]){
	int i;
	i = 0;
	while(tab_potion[i].exists == TRUE && i < MAX_USED_POTION){
		i++;
	}
	/* on recule à la case de la première vraie potion*/
	i--;
	/* si on est toujours dans le tableau, normalement c'est le cas*/
	if(i>=0 && i <= 4)
		if(tab_potion[i].exists == TRUE)
			/* on active l'effet de la potion le nouvel état de la potion*/
			active_potion(hero, &tab_potion[i]);
}

/* vérifie si un type de potion est déjà utilisé par le joueur*/
/* true (1)si la potion est déjà utilisée, false (0) sinon*/
int already_used(Potion pot, Potion tab_potion[MAX_USED_POTION]){
	int i;
	/* cas où une potion de ce type est déjà utilisé*/
	for(i = 0; i< MAX_USED_POTION;i++){
		if(tab_potion[i].type == pot.type && tab_potion[i].exists == TRUE){
			/*printf("la potion qui existe déjà est : \n");*/
			show_potion(tab_potion[i]);
			/*printf("Vous utilisez déjà ce type de potion ! \n");*/
			return TRUE;
		}
	}
	/* cas où une potion de ce type n'est pas utilisé*/
	return FALSE;
}

/* fonction qui vérifie que le personnage n'a pas déjà le maximum du champ qu'il souhaite augmenter*/
/* return true s'il est déjà au max, sinon false*/
int already_full(Potion pot, Perso hero){
	/* le héros a déjà tous ses hp*/
	if(pot.type == SOIN && hero.hp == max_hp(hero)){
		/*printf("Vous avez déjà tous vos hps ! \n");*/
		return TRUE;
	}
	/* le héros a déjà tous ses mp*/
	else if(pot.type == MAGIE && hero.mp == max_mp(hero)){
		/*printf("Vous avez déjà tous vos mps ! \n");*/
		return TRUE;
	}
	/* le héros a déjà tous ses mp et tous ses hp*/
	else if(pot.type == REGENERATION && hero.hp == max_hp(hero) && hero.mp == max_mp(hero)){
		/*printf("Vous avez déjà tous vos hp et tous vos mps ! \n");*/
		return TRUE;
	}
	return FALSE;


}
/* fonction qui gère le fait que le héros choisit une potion qu'il veut boire et l'ajoute dans la liste des potions à boire*/
/* renvoie TRUE (0) si oui , renvoie FALSE (1) sinon*/
int bois_potion(Perso * hero, int i, int j, Potion tab_potion[MAX_USED_POTION]){
	Potion pot1;
	int k;
	/* cas où on est pas dans le bon inventaire*/
	if(i != 1)
		return FALSE;
	/* cas où on dépasse la taille de l'inventaire des potions*/
	if(j>=SIZE_INVENTAIRE)
		return FALSE;
	pot1 = hero->invent[i][j].pot;
	/*Cas où le user essaye de boire un objet vide*/
	if(pot1.exists == FALSE){
		return FALSE;
	}
	/* cas où le user essaye de boire une potion alors qu'il utilise déjà ce type de potion (typiquement exp ou précision)*/
	if(already_used(pot1, tab_potion) == TRUE){
		/*printf("Vous utilisez déjà ce type de potion !\n");*/
		return FALSE;
	}
	/* cas où le user essaye de boire une potion alors qu'il a déjà le maximum de 
	ce qu'il souhaite augmenter*/
	if(already_full(pot1, *hero) == TRUE){
		return FALSE;
	}
	k = empty_place(tab_potion);
	tab_potion[k] = pot1;
	active_last_potion(hero, tab_potion);
	/*printf("Vous avez bu une nouvelle potion \n");*/
	hero->invent[i][j].pot = generateur_potion_null();
	mise_a_jour_stuff(hero, tab_potion);

	return TRUE;

}


/* fonction qui gère le fait que le héros s'équipe d'un objet*/
void equipe_equipement(Perso *hero, int i, int j, Potion tab_potion[MAX_USED_POTION]){
	/* cas où les coordonnées ne correspondent pas à un équipement*/
	/* ce n'est pas censé arriver*/
	if(i != 0){
		return;
	}
	changer_equipement(hero, i, j);
	mise_a_jour_stuff(hero, tab_potion);
}

/* Trouve le premier emplacement vide du tableau de potion*/
int empty_place(Potion tab_potion[MAX_USED_POTION]){
		int i;

		for(i = 0; i< MAX_USED_POTION; i++){
			/* cas où l'emplacement est vide*/
			if(tab_potion[i].exists == FALSE)
				return i;
		}
		return -1;

}

/* tableau qui initialise les potions que le joueur peut boire en même temps*/
void initialise_tab_potion(Potion tab_potion[MAX_USED_POTION]){
	memset(tab_potion, 0,(size_t)MAX_USED_POTION* sizeof(POTION));
	int i;
	for(i = 0; i < MAX_USED_POTION; i++){
		tab_potion[i] = generateur_potion_null();
	}


}

/* jette la potion choisie par le user*/
void jeter_potion(Perso * perso, int i, int j){
	/* cas où on est pas dans l'inventaire des potions*/
	if(i!=1)
		return;
	if(perso->invent[i][j].pot.exists == FALSE){
		printf("Il n'y a rien à jeter ici !");
		return;
	}
	perso->invent[i][j].pot = generateur_potion_null();
	printf("La potion a été jetée ");

}

/* jette l'équipement 'choisie par le user*/
void jeter_equipement(Perso * perso, int i, int j){
	/* cas où on est pas dans l'inventaire des équipements */
	if(i!=0)
		return;
	if(perso->invent[i][j].eq.exists == FALSE){
		printf("Il n'y a rien à jeter ici !");
		return;
	}
	perso->invent[i][j].eq = generateur_arme_null();
	printf("L'équipement a été jetée ");

}


/* fonction qui gère l'action de ranger une arme dans l'inventaire*/
void ranger_equipement(Perso * perso, int i, int j){
	/* récupère là où on va ranger l'arme*/
	int x,y;
	int old_hp;
	int old_mp;

	old_mp = perso->mp;
	old_hp = perso->hp;
	/* cas où le user tenterai de jeter une potion qu'il boit*/
	if(i !=  2 || j > 2){
		/*printf("Vous ne pouvez pas jeter une potion que vous êtes en train de boire !!! \n");*/
		return;
	}
	/* cas où l'inventaire des équipements est plein*/
	else if(find_empty_place_1(*perso, &x, &y) == FALSE){
		/*printf("Veuillez vider votre inventaire des équipements avant de vouloir retirer votre équipement ! \n");*/
		return;
	}
	else if(perso->invent[i][j].eq.exists == FALSE){
		/*printf("Vous essayez de retirer un équipement alors qu'il n'y en a pas ici! \n");*/
		return;
	}
	/* on met l'équipement dans l'inventaire*/
	if(perso->invent[i][j].eq.type == ARME){
		perso->invent[x][y].eq = perso->invent[i][j].eq;
		/* on désarme le joueur*/
		perso->arme = generateur_arme_null();
	}

	else if(perso->invent[i][j].eq.type == BAGUETTE){
		perso->invent[x][y].eq = perso->invent[i][j].eq;
		/* on retire l'intelligence gagnée grâce à l'armure*/
		perso->inte -= perso->baguette.inte;
		/* on désarme le joueur*/
		perso->baguette = generateur_baguette_null();
	}
	else if(perso->invent[i][j].eq.type == ARMURE){
		perso->invent[x][y].eq = perso->invent[i][j].eq;
		/* on retire la défense gagnée grâce à l'armure*/
		perso->def -= perso->armure.def;
		/* on désarme le joueur*/
		perso->armure = generateur_armure_null();
	}
	/* on change les hp et mp du héros en fonction des effets de la perte du bonus des équipements*/
	
	if(max_hp(*perso)<old_hp){
		perso->hp = max_hp(*perso);
	}
	else{
		perso->hp = old_hp;
	}
	if(max_mp(*perso) < old_mp){
		perso->mp = max_mp(*perso);
	}
	else{
		perso->mp = old_mp;
	}

}

/* compare les armes du joueur selon leurs attaques pour lui faire porter la meilleure*/
/* elle renvoie 0 si il faut changer et 1 sinon*/
/* les coordonnées de la nouvelle meilleure armes sont dans i et j*/
int compare_arme(int *i, int *j, Perso hero){
	int j2;
	/* variable qui dit si il faut oui ou non changer d'arme*/
	int chg;
	Equipement best_eq;
	chg = 1;
	if(hero.arme.exists == FALSE)
		return 1;
	for(j2 = 0; j2 < SIZE_INVENTAIRE ; j2++){
		if(hero.invent[0][j2].eq.type == ARME){
			/* si on ne sait pas si on doit prendre une autre arme que celle équipée*/
			if(chg == 1){
				if(hero.arme.atk < hero.invent[0][j2].eq.atk){
					/* on récupère les données du meilleur équipement*/
					*i = 0;
					*j = j2;
					best_eq = hero.invent[0][j2].eq;
					chg = 0;
				}
			}
			/*si on doit utiliser une arme différente de celle portée par le joueur*/
			else if(chg ==0){
				if(best_eq.atk < hero.invent[0][j2].eq.atk){
					/* on récupère les données du meilleur équipement*/
					*i = 0;
					*j = j2;
					best_eq = hero.invent[0][j2].eq;
					chg = 0;
				}

			}
		}

	}
	/*printf("on change automatiquement d'arme pour une meilleure \n");*/
	return chg;
}

/* compare les armes du joueur selon leurs intelligence pour lui faire porter la meilleure*/
/* elle renvoie 0 si il faut changer et 1 sinon*/
/* les coordonnées de la nouvelle meilleure armes sont dans i et j*/
int compare_baguette(int *i, int *j, Perso hero){
	int j2;
	/* variable qui dit si il faut oui ou non changer d'arme*/
	int chg;
	Equipement best_eq;
	chg = 1;
	if(hero.baguette.exists == FALSE)
		return 1;
	for(j2 = 0; j2 < SIZE_INVENTAIRE ; j2++){
		if(hero.invent[0][j2].eq.type == BAGUETTE){
			/* si on ne sait pas si on doit prendre une autre arme que celle équipée*/
			if(chg == 1){
				if(hero.arme.inte < hero.invent[0][j2].eq.inte){
					/* on récupère les données du meilleur équipement*/
					*i = 0;
					*j = j2;
					best_eq = hero.invent[0][j2].eq;
					chg = 0;
				}
			}
			/*si on doit utiliser une arme différente de celle portée par le joueur*/
			else if(chg ==0){
				if(best_eq.inte < hero.invent[0][j2].eq.inte){
					/* on récupère les données du meilleur équipement*/
					*i = 0;
					*j = j2;
					best_eq = hero.invent[0][j2].eq;
					chg = 0;
				}

			}
		}

	}
	/*printf("on change automatiquement d'épée pour une meilleure \n");*/
	return chg;
}

/* compare les armes du joueur selon leurs défenses pour lui faire porter la meilleure*/
/* elle renvoie 0 si il faut changer et 1 sinon*/
/* les coordonnées de la nouvelle meilleure armes sont dans i et j*/
int compare_armure(int *i, int *j, Perso hero){
	int j2;
	/* variable qui dit si il faut oui ou non changer d'armure*/
	int chg;
	Equipement best_eq;
	chg = 1;
	if(hero.armure.exists == FALSE)
		return 1;
	for(j2 = 0; j2 < SIZE_INVENTAIRE ; j2++){
		if(hero.invent[0][j2].eq.type == ARMURE){
			/* si on ne sait pas si on doit prendre une autre armure que celle équipée*/
			if(chg == 1){
				if(hero.arme.def < hero.invent[0][j2].eq.def){
					/* on récupère les données du meilleur équipement*/
					*i = 0;
					*j = j2;
					best_eq = hero.invent[0][j2].eq;
					chg = 0;
				}
			}
			/*si on doit utiliser une arme différente de celle portée par le joueur*/
			else if(chg ==0){
				if(best_eq.def < hero.invent[0][j2].eq.def){
					/* on récupère les données du meilleur équipement*/
					*i = 0;
					*j = j2;
					best_eq = hero.invent[0][j2].eq;
					chg = 0;
				}

			}
		}

	}
	/*printf("on change automatiquement d'armure pour un meilleur. \n");*/
	return chg;
}
/* donne au joueur les meilleurs équipements qu'il peut avoir*/
void meilleur_equipement(Perso *hero){
	int i,j;
	int i2, j2;
	int i3, j3;
	if(compare_arme(&i, &j, *hero) == 0){
		changer_equipement(hero, i, j);
	}
	if(compare_armure(&i2, &j2, *hero) == 0){
		
		changer_equipement(hero, i2, j2);
	}
	if(compare_baguette(&i3, &j3, *hero) == 0){
		changer_equipement(hero, i3, j3);
	}


}