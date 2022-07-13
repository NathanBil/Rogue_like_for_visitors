#ifndef __TRESOR__
#define __TRESOR__

	#include "equipement.h"
	#include "potion.h"
	#include "coordonnees.h"
	#include "boolean.h"
	#define NB_TRESOR 2

	union Item {
		Equipement eq;
		Potion pot;
	};



	/*Représente le type d'une case*/
	typedef enum treasuretype {
		EQUIPEMENT,
		POTION,
		/* type quand le coffre a été ouvert*/
		VIDE

	} Treasuretype;

	typedef struct tresor {
		union Item item;
		Treasuretype type_tresor;
	} Treasure;

	Treasure generate_treasure(int etage);


	/* affiche un trésor, selon son type*/
	void show_tresor(Treasure tresor);

	void add_treasure(int etage, Treasure tresor[NB_TRESOR]);

	/* copie le contenu d'un coffre vers un autre*/
	void copie_coffre_tresor(Treasure tresor[NB_TRESOR], Treasure tresor2 [NB_TRESOR]);


	/*Les trésors contiennent des objets 

	- potion
	- armures
	- baguettes magique 



	*/


#endif
