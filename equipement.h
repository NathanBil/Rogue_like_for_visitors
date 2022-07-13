#ifndef __EQUIPEMENT__
#define __EQUIPEMENT__
#include <time.h>
#include "stdio.h"
#include "stdlib.h"
#include "boolean.h"
#define FACTEUR_DEF 20
#define FACTEUR_ATK 50
#define FACTEUR_ATK_MAG 50
	typedef enum {
		ARME,
		ARMURE, 
		BAGUETTE

	} typeEquipement ;
	
	typedef enum {
		MAUVAIS, 
		MOYEN, 
		BON, 
		EXCELLENT, 
		RARE

	} typeQualite ;

	typedef struct equipement {
		typeEquipement type;
		int atk ;
		int def ;
		int inte;
		typeQualite qual;
		/*indique si l'equipement existe ou si il correspond à l'absence d'équipement*/
		/* true (1) = l'équipement existes, false = cela correpsond à l'absence d'équipement*/
		int exists;
	} Equipement;

/* genère le type d'un équipement de façon aléatoire*/
int gen_equipe_random(void);

/* genère une qualité pour un équipement de manière aléatoire*/
/* les chances d'obtenir un équipement d'une certaine qualité dépende de l'étage où se situe le user*/
/* la variable étage correspond à l'étage où l'équipement se situe*/
int gen_qualite_random(int etage);
/* génère un équiment aléatoirement en fonction de l'étage*/
/* renvoie l'équipement produit*/
/* la variable étage correspond à l'étage où l'équipement se créé*/
Equipement generateur_equipement(int etage);

/* génère l'arme de base du personnage, celle qu'il a en début de première partie au premier étage*/
/* renvoie l'arme produite*/
Equipement generateur_first_arme(void);

/* génère la baguette de base du personnage, celle qu'il a en début de première partie au premier étage*/
/* renvoie la baguette produite*/
Equipement generateur_first_baguette(void);
/* génère l'armure de base du personnage, celle qu'il a en début de première partie au premier étage*/
/* renvoie l'arrmure produite*/
Equipement generateur_first_armure(void);

/* génère une arme aux stats égaux à 0, cela correspond à l'état du joueur lorsqu'il ne porte rien comme arme*/
Equipement generateur_arme_null(void);
/* génère une armure aux stats égaux à 0, cela correspond à l'état du joueur lorsqu'il ne porte rien comme armure*/
Equipement generateur_armure_null(void);
/* génère une baguette aux stats égaux à 0, cela correspond à l'état du joueur lorsqu'il ne porte rien comme baguette*/
Equipement generateur_baguette_null(void);
/* affiche les caractéristiques d'un équipement dans le terminal*/
void show_equipement(Equipement eq1);

#endif