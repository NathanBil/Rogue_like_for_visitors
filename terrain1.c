#include "../inc/terrain.h"

/*

PENSER À FAIRE UNE FONCTION D ELIBÉRATION DE LISTE !!!


*/


void initialise_liste(TuplesList * list){
	list->size = 0;
	list->premier = NULL;
}


int distance(Tuple a, Tuple b){
	return abs(b.i - a.i) + abs(b.j - a.j);
}


int is_admissible(Tuple cell, Terrain chemin){


	int i, j, nb_room1, nb_room2;

	Tuple cell_near;

	nb_room1 = 0;
	nb_room2 = 0;

	if(chemin.terrain[cell.i][cell.j].type != WALL){
		return 0;
	}

	for(i  = -3 ; i < 3; i++){
		for(j  = -3 ; j < 3; j++){


			cell_near.i = cell.i + i;
			cell_near.j = cell.j + j;
			/* on s'assure qu'on n'essaye pas de lire une case inaccessible*/
			if(cell_near.i >= 0 && cell_near.i < LONGUEUR && cell_near.j >= 0 && cell_near.j < LARGEUR){
				if(distance(cell, cell_near) == 1 && chemin.terrain[cell_near.i][cell_near.j].type != WALL){
					nb_room1 ++;
				}
				/*
				à supprimer

				type = chemin.terrain[cell_near.i][cell_near.j].type;*/
				/*printf("near i vaut : %d \n"  ,cell_near.i);
				printf("near j vaut : %d \n" ,cell_near.j);
				printf("la val problématique dans admissible vaut  : chemin [%d][%d].val vaut : %d \n" ,cell_near.i,cell_near.j ,chemin.terrain[cell_near.i][cell_near.j].type); *//* tombe parfois sur des valeurs abérrantes type 
				79338612 pour le type */
				if(distance(cell, cell_near) == 2 && chemin.terrain[cell_near.i][cell_near.j].type != WALL){
					nb_room2 ++;
				}
			}
		}
	}

	/*distance 1*/
	if(nb_room1 != 1){
		return 0;
	}

	/*distance 2*/
	if(nb_room2 > 2){
		return 0;
	}

	return 1; 
}



Tuple pick_case_al(TuplesList list){

	int indice, i, verified;
	Tuple c;

	Tuple * tmp;

	tmp = list.premier;

	c.i = 0;
	c.j = 0;


	i = 0;

	if(list.size == 0){
		return c;
	}

	indice = rand() % list.size;

	verified = 0;

	while(tmp != NULL && verified != 1){

		if(i == indice){

			c.i = tmp->i;
			c.j = tmp->j;
			c.suivant = NULL;

			verified = 1;
		}

		tmp = tmp->suivant; 
		i++;

	}

	return c;
}




void initialise_cases_mur(Terrain * chemin, int dim_x, int dim_y){
	int i, j;

	for(i = 0; i < dim_x ; i++){
		for(j = 0; j < dim_y ; j++){

			if(i == dim_x / 2 && j == dim_y / 2){
				chemin->terrain[i][j].type = STAIR_UP;

			}else{
				chemin->terrain[i][j].type = WALL;
			}
		}
	}
}




int is_list_vide(TuplesList list){

	if(list.premier == NULL){
		return 1;
	}

	return 0;
}




int already_in_list(TuplesList list, Tuple c){

	Tuple * tmp;

	tmp = list.premier;

	while(tmp != NULL){

		if(tmp->i == c.i && tmp->j == c.j){
			return 1;
		}

		tmp = tmp->suivant;
	}

	return 0;
}


void add_case_in_list(TuplesList * list, int x, int y){

	Tuple * elem = (Tuple *) malloc(sizeof(Tuple));

	if(elem == NULL){
		exit(EXIT_FAILURE);
	}

	elem->i = x;
	elem->j = y;

	elem->suivant = list->premier;
	list->premier = elem;

	list->size += 1;
}



void find_cases_mur(TuplesList * list, Terrain chemin, int dim_x, int dim_y){

	int i, j, nb_mur;

	for(i = 1; i < dim_x - 1; i++){
		for(j = 1; j < dim_y - 1; j++){

			nb_mur = 0;

			if(chemin.terrain[i + 1][j].type == WALL){
				nb_mur ++;
			}

			if(chemin.terrain[i][j + 1].type == WALL){
				nb_mur ++;
			}

			if(chemin.terrain[i - 1][j].type == WALL){
				nb_mur ++;
			}

			if(chemin.terrain[i][j - 1].type == WALL){
				nb_mur ++;
			}

			if(nb_mur == 3){
				add_case_in_list(&(*list), i, j);
			}

		}
	}
}




void put_cases_mur(TuplesList * list, Terrain * chemin){

	Tuple * tmp;

	tmp = list->premier;

	while(tmp != NULL){

		(*chemin).terrain[tmp->i][tmp->j].type = WALL;

		tmp = tmp->suivant;
	}
}



int supprime_elem_list(TuplesList * list, Tuple cell){

	int find = 0;
	Tuple * tmp;

	tmp = list->premier;
	
	if(list->size == 0){
		return 0;
	}


	if(tmp->i == cell.i && tmp->j == cell.j){

		list->premier = list->premier->suivant;

		list->size -= 1;


		return 1;
	}

	while(tmp != NULL && find == 0){

		if(tmp->suivant != NULL){
			if(tmp->suivant->i == cell.i && tmp->suivant->j == cell.j){
				
				tmp->suivant = tmp->suivant->suivant;

				list->size -= 1;

				return 1;
			}
		}
		
		
		tmp = tmp->suivant;
	}

	return 0;
}


void print_list(TuplesList list){

	Tuple * ptr = list.premier;

	printf("Liste : %d\n\n", list.size);

	if(list.premier == NULL){
		printf("Liste nulle\n");
		return;
	}

	while(ptr != NULL){
		printf("(%d - %d) -> ", ptr->i, ptr->j);
		ptr = ptr->suivant;
	}

	printf("NULL\n\n");
}










void generate_stairs_down(Terrain * chemin, int dim_x, int dim_y){
	int i, j;

	TuplesList potential_stairs_down;
	Tuple ptr, stairs_up, result;

	initialise_liste(&potential_stairs_down);

	stairs_up.i = dim_x / 2;
	stairs_up.j = dim_y / 2;


	for(i = 0; i < dim_x; i++){
		for(j = 0; j < dim_y; j++){

			ptr.i = i;
			ptr.j = j;

			if(distance(ptr, stairs_up) >= 25 && (*chemin).terrain[ptr.i][ptr.j].type == ROOM){
				add_case_in_list(&potential_stairs_down, ptr.i, ptr.j);
			}
		}
	}

	result = pick_case_al(potential_stairs_down);

	(*chemin).terrain[result.i][result.j].type = STAIR_DOWN;


}


/*MANQUE À AJOUTER CE QU'EST EXACTEMENT LE TRESOR + MONSTRE


ajouter generation de monstres : HP et Atk tirés aléatoirement + on est loin dans le donjon plus le monstre est fort donc faire grâce à la valeur étage !!!!


*/




void generate_treasures_map(Terrain * chemin, int dim_x, int dim_y, int etage){
	
	int i, j;

	TuplesList  tab;

	Tuple random_room, room_monster;

	initialise_liste(&tab);


	if(etage == 0){

		if((*chemin).terrain[(dim_x/2) + 1][(dim_y / 2)].type == ROOM){
			add_case_in_list(&tab, (dim_x / 2) + 1, dim_y / 2);
		}

		if((*chemin).terrain[(dim_x / 2)][(dim_y / 2) + 1].type == ROOM){
			add_case_in_list(&tab, dim_x / 2, (dim_y / 2) + 1);
		}


		if((*chemin).terrain[(dim_x/2) - 1][dim_y / 2].type == ROOM){
			add_case_in_list(&tab, (dim_x/2) - 1, dim_y / 2);
		}

		if((*chemin).terrain[(dim_x / 2)][(dim_y / 2) - 1].type == ROOM){
			add_case_in_list(&tab, dim_x / 2, (dim_y / 2) - 1);
		}

		random_room = pick_case_al(tab);

		(*chemin).terrain[random_room.i][random_room.j].type = TREASURE;
		

	}


	for(i = 0; i < dim_x ;i++){
			for(j = 0; j < dim_y ;j++){

				initialise_liste(&tab);



				if((*chemin).terrain[i + 1][j].type != WALL){
					add_case_in_list(&tab, i + 1, j);
				}

				if((*chemin).terrain[i][j + 1].type != WALL){
					add_case_in_list(&tab, i, j + 1);
				}


				if((*chemin).terrain[i - 1][j].type != WALL){
					add_case_in_list(&tab, i - 1, j);				
				}

				if((*chemin).terrain[i][j - 1].type != WALL){
					add_case_in_list(&tab, i, j - 1);
				}

				if(tab.size == 1 && (*chemin).terrain[i][j].type == ROOM && rand() % RANDOM_TREASURE_MAX == 0) {

					(*chemin).terrain[i][j].type = TREASURE;
					(*chemin).terrain[room_monster.i][room_monster.j].entity.treasure = generate_treasure(etage);

					room_monster = pick_case_al(tab);

					(*chemin).terrain[room_monster.i][room_monster.j].type = MONSTER;
					(*chemin).terrain[room_monster.i][room_monster.j].entity.monster = generate_monster(etage);


				}
				
			}
		}

	
}


int floor_up(Donjon * dongeon, Terrain * chemin, Perso hero){
	
	if(!(chemin->terrain[hero.coord.x][hero.coord.y].type == STAIR_DOWN)){
		return 0;
	}

	if((*dongeon).etage_courant < (*dongeon).size - 1){
		(*chemin) = (*dongeon).etages[(*dongeon).etage_courant + 1];
		(*dongeon).etage_courant += 1;
		return 1;
	}
	
	return 2;
}



int floor_down(Donjon * dongeon, Terrain * chemin, Perso hero){
	
	if(!(chemin->terrain[hero.coord.x][hero.coord.y].type == STAIR_UP)){
		return 0;
	}

	if((*dongeon).etage_courant > 0){
		(*chemin) = (*dongeon).etages[(*dongeon).etage_courant - 1];
		(*dongeon).etage_courant -= 1;
		return 1;
	}
	
	return 2;
}





void generate_terrain_al(Terrain * chemin, int dim_x, int dim_y, int etage){

	int i, etape_2;

	TuplesList toexpand, cases_mur;
	Tuple c, c_adjacente;


	initialise_liste(&toexpand);


	/*ETAPE 0*/
	initialise_cases_mur(chemin, dim_x, dim_y);

	/*ETAPE 1*/
	add_case_in_list(&toexpand, (dim_x/2) + 1, (dim_y/2));

	add_case_in_list(&toexpand, (dim_x/2), (dim_y/2) + 1);
	add_case_in_list(&toexpand, (dim_x/2) - 1, (dim_y/2));

	add_case_in_list(&toexpand, (dim_x/2), (dim_y/2) - 1);	


	/*ETAPE 5*/
	while(toexpand.size > 0){

		etape_2 = 0;

		/*ETAPE 2*/
		while(etape_2 == 0){

			c = pick_case_al(toexpand);
			supprime_elem_list(&toexpand, c);
			
			if(is_admissible(c, *chemin) || toexpand.size == 0){
				etape_2 = 1;
			}
		}


		/*ETAPE 3*/
		(*chemin).terrain[c.i][c.j].type = ROOM;

		/*ETAPE 4*/
		for(i = 0; i < 4; i++){

			switch(i){

				case 0:{
					c_adjacente.i = c.i + 1;
					c_adjacente.j = c.j ;
					break;
				}

				case 1:{
					c_adjacente.i = c.i;
					c_adjacente.j = c.j + 1;
					break;
				}

				case 2:{

					c_adjacente.i = c.i;
					c_adjacente.j = c.j - 1;
					break;
				}

				case 3:{
					c_adjacente.i = c.i - 1;
					c_adjacente.j = c.j;
					break;
				}
			}


			if(!(already_in_list(toexpand, c_adjacente)) && is_admissible(c_adjacente, *chemin) && c_adjacente.i != 0 && c_adjacente.j != 0 && c_adjacente.i != dim_x - 1 && c_adjacente.j != dim_y - 1){

				add_case_in_list(&toexpand, c_adjacente.i, c_adjacente.j);
			}

		}
	}

	/*Etape 6*/

	initialise_liste(&cases_mur);
	
	find_cases_mur(&cases_mur, *chemin, dim_x, dim_y);

	put_cases_mur(&cases_mur, &(*chemin));


	(*chemin).terrain[dim_x/2][dim_y/2].type = STAIR_UP;


	generate_treasures_map(chemin, dim_x, dim_y, etage);

	generate_stairs_down(chemin, dim_x, dim_y);
}



void initialise_dongeon(Donjon * dongeon, int dim_x, int dim_y, int dongeon_size, Terrain * chemin){
	int i;
	/*printf("le type du terrain est : %d \n" chemin[])*/
	if(dongeon_size > TAILLE_DONGEON_MAX){
		return;
	}

	(*dongeon).size = dongeon_size;

	(*dongeon).etages = (Terrain*) malloc(sizeof(Terrain) * dongeon_size);
	/* à supprimer*/
	/*printf("L'allocation s'est bien fait : %p \n", (void *)(*dongeon).etages);*/

	for(i = 0; i < dongeon_size ;i++){

		generate_terrain_al(chemin, 63, 43, i); /* lecture inacceptable*/

		(*dongeon).etages[i] = (*chemin);
	}

	(*dongeon).etage_courant = 0;

	(*chemin) = (*dongeon).etages[(*dongeon).etage_courant];
}









/***********************************************************************************************************************/




/*


Plusieurs niveaux les niveaux ()


chaque escaliers central est lié par un chemin à un escalier descendant

murs, monstres, trésors sont gen aléatoirement
























*/