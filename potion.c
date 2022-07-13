#include "../inc/potion.h"

/* genère le type d'une potion de façon aléatoire*/
int gen_type_potion_random(void){
	int x = rand() % 100;
	if(x > 0 && x <= 19)
		return SOIN;
	else if(x > 0 && x <= 39)
		return MAGIE;
	/*40 à 59*/
	else if(x > 40 && x <= 59)
		return REGENERATION;
	/* 60 à 79*/
	else if(x > 60 && x <= 79)
		return PRECISION_POT;
	return APPRENTISSAGE;
}

/* génère une potion aléatoirement*/
Potion generateur_potion(void){
	Potion pot1;
	pot1.type = 0;
	pot1.hp = 0;
	pot1.mp = 0;
	pot1.pourcentage = FALSE;
	pot1.critique = 0;
	pot1.exp =0;
	/* tour = le nombre de tour restant pour la potion*/
	pot1.tour = 0;
	/* le temps entre deux utilisations de la potion */
	pot1.delai = 1;
	pot1.exists = TRUE;
	/* le temps qui sépare la dernière utilisation de la potion avec mtnt */
	pot1.temps_e = 0;
	/* on initialise les champs de l'équipement*/
	pot1.type = gen_type_potion_random();
	/* on augmente le champs de l'équipement selon son type*/
	/* cas où on a génère une potion de soin*/
	if(pot1.type == SOIN){
		pot1.hp = 10;
		pot1.pourcentage = TRUE;
		pot1.tour = 1;
	}
	/* cas où on a génère une potion de magie*/
	else if(pot1.type == MAGIE){
		pot1.mp = 10;
		pot1.pourcentage = TRUE;
		pot1.tour = 1;
	}
	/* cas où on génère une potion de régénération*/
	else if(pot1.type == REGENERATION){
		pot1.hp = 20;
		pot1.mp = 10;
		pot1.tour = 30;
		pot1.pourcentage = FALSE;
		pot1.delai = 3;
		/* lors de la première utilisation la potion appliquera directement son effet*/
		pot1.temps_e = 2;
	}
	/* cas où on génère une potion de précision*/
	else if(pot1.type == PRECISION_POT){
		pot1.critique = 15;
		pot1.tour = 30;
		pot1.pourcentage = TRUE;
	}
	/* cas où on génère une potion d'apprentissage*/
	else if(pot1.type == APPRENTISSAGE){
		pot1.exp = 30;
		pot1.tour = 30;
		pot1.pourcentage = TRUE;
	}

	return pot1;

}

/* génère une potion aux stats égaux à 0, cela correspond à l'état de l'inventaire des potion 'lorsque le joueur n'a pas rempli une place avec une potion*/
Potion generateur_potion_null(void){
	Potion pot1;
	pot1.type = 0;
	pot1.hp = 0;
	pot1.mp = 0;
	pot1.pourcentage = FALSE;
	pot1.critique = 0;
	pot1.exp =0;
	pot1.tour = 0;
	pot1.delai = 0;
	pot1.exists = FALSE;
	pot1.temps_e = 0;
	return pot1;

}

/* affiche les caractéristiques d'une potion dans le terminal*/
void show_potion(Potion pot1){
	if(pot1.exists == FALSE)
		return;
	printf(" hp : %d \n" , pot1.hp);
	printf(" mp : %d \n" , pot1.mp);
	printf(" pourcentage : %d \n", pot1.pourcentage);
	printf(" exp : %d \n" ,pot1.exp);
	printf(" tour : %d \n" ,pot1.tour);
	printf(" délai : %d \n" ,pot1.delai);
	printf(" critique: %d \n" ,pot1.critique);
	if(pot1.exists == TRUE)
		printf(" exists: TRUE \n");
	else 
		printf(" exists: FALSE \n");

}

