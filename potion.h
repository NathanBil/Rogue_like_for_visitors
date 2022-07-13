#ifndef __POTION__
#define __POTION__

	#include <stdlib.h>
 	#include <stdio.h>
	#include <stdbool.h>
	#include "boolean.h"
	
	typedef enum {SOIN, MAGIE, REGENERATION, PRECISION_POT, APPRENTISSAGE} typePotion ;
	
	typedef struct {
		typePotion type;
		int hp ;
		int mp ;
		/* permet de savoir si l'objet fonctionne en pourcentage ou en augmentation d'une valeur des hp/mp*/
		int pourcentage;
		/* correspond au pourcentage d'augmentation de coup critique avec cette potion*/
		int critique;
		/* correspond au pourcentage d'augmentation d'exp avec cette potion*/
		int exp;
		/* correspond au nombre de tour où la potion peut encore être effective*/
		int tour;
		/* correspond à l'intervalle entre deux applications d'une potion qui s'applique sur plusiueurs tours*/
		int delai;
		/* correspond aux tours écoulés depuis la dernière utilisation de la potion*/
		int temps_e;

		int exists;
	} Potion;

	/* génère une potion aléatoirement*/
	Potion generateur_potion();
	/* affiche les caractéristiques d'une potion dans le terminal*/
	void show_potion(Potion pot1);
	/* génère une potion aux stats égaux à 0, cela correspond à l'état de l'inventaire des potion 'lorsque le joueur n'a pas rempli une place avec une potion*/
	Potion generateur_potion_null(void);

	/* affiche les caractéristiques d'une potion dans le terminal*/
	void show_potion(Potion pot1);



#endif