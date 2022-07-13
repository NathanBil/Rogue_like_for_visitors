#include "../inc/equipement.h"

/* genère le type d'un équipement de façon aléatoire*/
int gen_equipe_random(void){
	int x = rand() % 101;
	/* génération d'épée 33%*/
	if(x >= 0 && x <= 32){
		return 0;
	}
	/* génération d'armure 33%*/
	else if(x >= 33 && x <= 65){
		return 1;
	}
	/* génération de baguette 34%*/
	return 2;
}


/* genère une qualité pour un équipement de manière aléatoire*/
/* les chances d'obtenir un équipement d'une certaine qualité dépende de l'étage où se situe le user*/
/* la variable étage correspond à l'étage où l'équipement se situe*/
int gen_qualite_random(int etage){
	return rand() % (etage + 1);
}

/* génère un équipement aléatoirement en fonction de l'étage*/
/* renvoie l'équipement produit*/
/* la variable étage correspond à l'étage où l'équipement se créé*/
Equipement generateur_equipement(int etage){
	Equipement eq1;
	/* on initialise les champs de l'équipement*/
	eq1.def = 0;
	eq1.atk = 0;
	eq1.inte = 0;
	eq1.exists = TRUE;
	eq1.type = gen_equipe_random();
	eq1.qual = gen_qualite_random(etage);
	/* on augmente le champs de l'équipement selon son type*/
	if(eq1.type == 0)
		eq1.atk = (eq1.qual+1)*FACTEUR_ATK;
	else if(eq1.type == 1)
		eq1.def = (eq1.qual+1)*FACTEUR_DEF;
	else if(eq1.type == 2)
		eq1.inte = (eq1.qual+1)*FACTEUR_ATK_MAG;

	return eq1;

}

/* génère l'arme de base du personnage, celle qu'il a en début de première partie au premier étage*/
/* renvoie l'arme produite*/
Equipement generateur_first_arme(void){
	Equipement eq1;
	/* on initialise les champs de l'équipement*/
	eq1.def = 0;
	eq1.atk = 0;
	eq1.inte = 0;
	eq1.type = ARME;
	eq1.qual = MAUVAIS;
	/* on augmente le champs de l'équipement selon son type*/
	eq1.atk = (eq1.qual+1)*FACTEUR_ATK;
	eq1.exists = TRUE;
	return eq1;

}

/* génère la baguette de base du personnage, celle qu'il a en début de première partie au premier étage*/
/* renvoie la baguette produite*/
Equipement generateur_first_baguette(void){
	Equipement eq1;
	/* on initialise les champs de l'équipement*/
	eq1.def = 0;
	eq1.atk = 0;
	eq1.inte = 0;
	eq1.type = BAGUETTE;
	eq1.qual = MAUVAIS;
	/* on augmente le champs de l'équipement selon son type*/
	eq1.inte = (eq1.qual+1)*FACTEUR_ATK_MAG;
	eq1.exists = TRUE;

	return eq1;

}

/* génère l'armure de base du personnage, celle qu'il a en début de première partie au premier étage*/
/* renvoie l'arrmure produite*/
Equipement generateur_first_armure(void){
	Equipement eq1;
	/* on initialise les champs de l'équipement*/
	eq1.def = 0;
	eq1.atk = 0;
	eq1.inte = 0;
	eq1.type = ARMURE;
	eq1.qual = MAUVAIS;
	/* on augmente le champs de l'équipement selon son type*/
	eq1.def = (eq1.qual+1)*FACTEUR_DEF;
	eq1.exists = TRUE;
	return eq1;

}

/* génère une arme aux stats égaux à 0, cela correspond à l'état du joueur lorsqu'il ne porte rien comme arme*/
Equipement generateur_arme_null(void){
	Equipement eq1;
	/* on initialise les champs de l'équipement*/
	eq1.def = 0;
	eq1.atk = 0;
	eq1.inte = 0;
	eq1.type = ARME;
	eq1.qual =  MAUVAIS;
	eq1.exists = FALSE;
	return eq1;
}
/* génère une armure aux stats égaux à 0, cela correspond à l'état du joueur lorsqu'il ne porte rien comme armure*/
Equipement generateur_armure_null(void){
	Equipement eq1;
	/* on initialise les champs de l'équipement*/
	eq1.def = 0;
	eq1.atk = 0;
	eq1.inte = 0;
	eq1.type = ARMURE;
	eq1.qual =  MAUVAIS;
	eq1.exists = FALSE;
	return eq1;

}
/* génère une baguette aux stats égaux à 0, cela correspond à l'état du joueur lorsqu'il ne porte rien comme baguette*/
Equipement generateur_baguette_null(void){
	Equipement eq1;
	/* on initialise les champs de l'équipement*/
	eq1.def = 0;
	eq1.atk = 0;
	eq1.inte = 0;
	eq1.type = BAGUETTE;
	eq1.qual =  MAUVAIS;
	eq1.exists = FALSE;
	return eq1;

}

/* affiche les caractéristiques d'un équipement dans le terminal*/
void show_equipement(Equipement eq1){
	/*if(eq1.exists != true)
		return;*/
	printf(" atk : %d \n", eq1.atk);
	printf(" def : %d \n", eq1.def);
	printf(" int : %d \n", eq1.inte);
	printf(" qual : %d \n", eq1.qual);
	if(eq1.type == 0)
		printf(" type : ARME \n");
	if(eq1.type == 1)
		printf(" type : ARMURE \n");
	if(eq1.type == 2)
		printf(" type : BAGUETTE \n");
}