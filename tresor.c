#include "../inc/tresor.h"



/* fonction qui détermine aléatoirement si l'objet dans le coffre sera une potion ou un équipement*/
int gen_tresor_random(void){
	int x = rand() % 100;
	/*génération d'une potion avec 30% de chance*/
	if(x >= 0 && x <= 29){
		return 0;
	}
	/*génération d'un équipement avec 70% de chance*/
	return 1;
}





Treasure generate_treasure(int etage){

	Treasure tresor;

	if(gen_tresor_random() == 0){
		tresor.item.pot = generateur_potion();
		tresor.type_tresor = POTION;
	}
	else{
		tresor.item.eq = generateur_equipement(etage);
		tresor.type_tresor = EQUIPEMENT;
	}
	
	return tresor;

}

/* Ajoute des trésors dans un coffre*/
void add_treasure(int etage, Treasure tresor[NB_TRESOR]){
	int i;
	for(i=0;i< NB_TRESOR;i++){
		tresor[i] = generate_treasure(etage);
	}
}

void show_tresor(Treasure tresor){
	if(tresor.type_tresor == EQUIPEMENT){
		show_equipement(tresor.item.eq);
	}
	else if(tresor.type_tresor == POTION){
		show_potion(tresor.item.pot);
	}
	else if(tresor.type_tresor == VIDE)
		printf("Il n'y pas de à cet emplacement \n");

}

/* copie le contenu d'un coffre vers un autre*/
void copie_coffre_tresor(Treasure dest[NB_TRESOR], Treasure send[NB_TRESOR]){
	int i;
	for(i=0;i<NB_TRESOR;i++){
		dest[i] = send[i];		
	}

}