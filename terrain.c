 #include "../inc/terrain.h"

/*

PENSER À FAIRE UNE FONCTION D ELIBÉRATION DE LISTE !!!


*/
/* libère une liste de tuple*/

/* fonction qui permet de libérer chaque étages du dongeon ayant été utilisé donc le dongeon lui-même*/
void free_dongeon(Donjon * dongeon){
	free(dongeon->etages);
}

void free_tupleList(TuplesList * list){
	Tuple * tmp;
	if(list->premier == NULL)
		return;	
	tmp = list->premier->suivant;
	while(list->premier->suivant != NULL){
		free(list->premier);
		list->premier = tmp;
		tmp = tmp->suivant;

	}
	/* on libère le dernier élément de la liste*/
	free(list->premier);
	list->premier = NULL;
}


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
	Tuple * tmp_next;
	tmp = list->premier;
	
	if(list->size == 0){
		return 0;
	}


	if(tmp->i == cell.i && tmp->j == cell.j){

		tmp = list->premier->suivant;
		free(list->premier);
		list->premier = tmp;
		list->size -= 1;
		return 1;
	}

	while(tmp != NULL && find == 0){

		if(tmp->suivant != NULL){
			if(tmp->suivant->i == cell.i && tmp->suivant->j == cell.j){
				
				tmp_next = tmp->suivant->suivant;
				free(tmp->suivant);
				tmp->suivant = tmp_next;

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

	free_tupleList(&potential_stairs_down);


}

/* fonction qui associe à chaque monstre l'expérience qu'il donne après sa mort*/
/* les monstres d'un étage rapporte tous le même nombre d'exp*/
/* la somme de leur exp fait augmenter deux niveaux au joueur selon l'étage */
/* tuer tous les monstres de l'étage 1 une fois permet d'atteindre le niveau 3, pour l'étage 2 le niveau 5, etc...*/
void experience_monstre(Terrain * chemin, int dim_x, int dim_y, int etage){
	int i,j;
	for(i = 0; i < dim_x ;i++){
			for(j = 0; j < dim_y ;j++){

				if((*chemin).terrain[i][j].type == MONSTER){
					(*chemin).terrain[i][j].entity.monster.gain_exp = (650+((etage+1)*FACTEUR_EXP))/ (*chemin).nb_monster;
				}

				
			}
	}
}


/*MANQUE À AJOUTER CE QU'EST EXACTEMENT LE TRESOR + MONSTRE


ajouter generation de monstres : HP et Atk tirés aléatoirement + on est loin dans le donjon plus le monstre est fort donc faire grâce à la valeur étage !!!!


*/



/* partie qui pose pb*/
void generate_treasures_map(Terrain * chemin, int dim_x, int dim_y, int etage){
	
	int i, j;
	Tuple random_room, room_monster;
	TuplesList  tab;
	(*chemin).nb_monster = 0;
	

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
		add_treasure(etage,(*chemin).terrain[random_room.i][random_room.j].entity.treasure);
		free_tupleList(&tab);
		

	}


	for(i = 0; i < dim_x ;i++){
			for(j = 0; j < dim_y ;j++){

				initialise_liste(&tab);



				if(i < (dim_x -1) && ((*chemin).terrain[i + 1][j].type != WALL)){
					add_case_in_list(&tab, i + 1, j);
				}

				if(j < (dim_y -1) && ((*chemin).terrain[i][j + 1].type != WALL)){
					add_case_in_list(&tab, i, j + 1);
				}
					
				if( i > 0 && ((*chemin).terrain[i - 1][j].type != WALL)){
					add_case_in_list(&tab, i - 1, j);				
				}
				

				if(j > 0 && ((*chemin).terrain[i][j - 1].type != WALL)){
					add_case_in_list(&tab, i, j - 1);
				}

				if(tab.size == 1 && (*chemin).terrain[i][j].type == ROOM && rand() % RANDOM_TREASURE_MAX == 0) {

					(*chemin).terrain[i][j].type = TREASURE;
					add_treasure(etage, (*chemin).terrain[i][j].entity.treasure);

					room_monster = pick_case_al(tab);

					(*chemin).terrain[room_monster.i][room_monster.j].type = MONSTER;
					(*chemin).terrain[room_monster.i][room_monster.j].entity.monster = generate_monster(etage);
					(*chemin).nb_monster++;
					

				}

				free_tupleList(&tab);
				
			}
	}
	free_tupleList(&tab);
	experience_monstre(chemin, dim_x, dim_y, etage);

	
}

/* fonction qui gère la montée du joueur d'un étage */
int floor_up(Donjon * dongeon, Terrain * chemin, Perso  * hero, int lim_x, int lim_y){
	
	if(!(chemin->terrain[hero->coord.x][hero->coord.y].type == STAIR_DOWN)){
		return 0;
	}

	if((*dongeon).etage_courant < (*dongeon).size - 1){
		(*chemin) = (*dongeon).etages[(*dongeon).etage_courant + 1];
		(*dongeon).etage_courant += 1;

		hero->coord.x = lim_x / 2;
		hero->coord.y = lim_y / 2;
		return 1;
	}
	
	return 2;
}

/* fonction qui gère la descente du joueur d'un étage */
int floor_down(Donjon * dongeon, Terrain * chemin, Perso * hero, int lim_x, int lim_y){
	int i,j;
	int x_j;
	int y_j;
	int stop;
	stop = 0;
	if(!(chemin->terrain[hero->coord.x][hero->coord.y].type == STAIR_UP)){
		return 0;
	}

	if((*dongeon).etage_courant > 0){
		(*chemin) = (*dongeon).etages[(*dongeon).etage_courant - 1];
		(*dongeon).etage_courant -= 1;
		for(i=0; i < lim_x;i++){
			if(stop == 1)
				break;
			/*on cherche l'échelle inférieure*/
			for(j=0; j < lim_y ; j++){
				/* on trouve l'échelle montante de l'étage inférieur*/
				if(chemin->terrain[i][j].type == STAIR_DOWN){
					printf("on a trouvé une room up !!\n");
					x_j = i;
					y_j = j;
				stop = 1;
				break;
				}
				

			}
		}
		/* le joueur récupère ses nouvelles coordonnées*/
		hero->coord.x = x_j;
		hero->coord.y = y_j;
		return 1;
	}
	
	return 2;
}

/* vérifie si un combat doit être lancé*/
/* renvoie 1 si un combat doit être lancé*/
/* renvoie 0 si aucun combat ne doit être lancé*/

int test_fight(Perso hero, Terrain * chemin, Coord monster_coords[MAX_MONSTER]){
	/* variable qui dit si oui ou non il y doit y avoir un fight*/
	/* 1 signifie oui, 0 signifie non */
	int fight;
	Coord monster;
	fight = 0;
	/* si le héros est déjà en plein combat on sort de la fonction*/
	/*if(is_empty_tab_monster(monster_coords) == 0)
		return 1;*/
	/*for(i = 0; i<MAX_MONSTER; i++){
		monster.x = monster_coords[i].x;
		monster.y = monster_coords[i].y;*/
		/* on verifie qu'il y a un monstre à côté du héros, ici en haut*/
		if(chemin->terrain[hero.coord.x][hero.coord.y + 1].type == MONSTER){
			/*printf("il y a un monstre en dessous \n");*/
			/* on vérifie que le héros est orienté dans le sens du monstre*/
			if(hero.direction == SUD){
				monster.x = hero.coord.x;
				monster.y =  hero.coord.y + 1;
				add_monster(monster_coords, monster);
				fight = 1;
			}
			
		}
		/* on verifie qu'il y a un monstre à côté du héros, ici en bas*/
		if(chemin->terrain[hero.coord.x][hero.coord.y - 1].type == MONSTER){
			/*printf("il y a un monstre au desssus \n");*/
			/* on vérifie que le héros est orienté dans le sens du monstre*/
			if(hero.direction == NORD){
				monster.x = hero.coord.x;
				monster.y = hero.coord.y - 1;
				add_monster(monster_coords, monster);
				fight = 1;
			}
			
		}
		/* on verifie qu'il y a un monstre à côté du héros, ici à sa gauche*/
		if(chemin->terrain[hero.coord.x - 1][hero.coord.y].type == MONSTER){
			/*printf("il y a un monstre à gauche \n");*/
			/* on vérifie que le héros est orienté dans le sens du monstre*/
			if(hero.direction == OUEST){
				monster.x = hero.coord.x-1;
				monster.y = hero.coord.y;
				add_monster(monster_coords, monster);
				fight = 1;
			}
		}

		/* on verifie qu'il y a un monstre à côté du héros, ici à sa droite*/
		if(chemin->terrain[hero.coord.x + 1][hero.coord.y].type == MONSTER){
			/*printf("il y a un monstre à droite \n");*/
			/* on vérifie que le héros est orienté dans le sens du monstre*/
			if(hero.direction == EST){
				monster.x = hero.coord.x+1;
				monster.y = hero.coord.y;
				add_monster(monster_coords, monster);
				fight = 1;
			}
		}
	/*}*/

	return fight;
}


/* vérifie si un combat doit être lancé*/
/* renvoie 1 si un combat doit être lancé*/
/* renvoie 0 si aucun combat ne doit être lancé*/
/* trouve le monstre ciblé par le joueur et enregistre ses coordonnées dans i et j*/
int find_one_monster(Perso hero, Terrain * chemin, Coord * monster_coords){
	/* on verifie qu'il y a un monstre à côté du héros, ici en haut*/
	if(chemin->terrain[hero.coord.x][hero.coord.y + 1].type == MONSTER){
		/* on vérifie que le héros est orienté dans le sens du monstre*/
		if(hero.direction == SUD){
			(*monster_coords).x = hero.coord.x;
			(*monster_coords).y = hero.coord.y + 1;
			return 1;
		}
		
	}
	/* on verifie qu'il y a un monstre à côté du héros, ici en bas*/
	if(chemin->terrain[hero.coord.x][hero.coord.y - 1].type == MONSTER){
		/* on vérifie que le héros est orienté dans le sens du monstre*/
		if(hero.direction == NORD){
			(*monster_coords).x = hero.coord.x;
			(*monster_coords).y = hero.coord.y - 1;
			return 1;
		}
		
	}
	/* on verifie qu'il y a un monstre à côté du héros, ici à sa gauche*/
	if(chemin->terrain[hero.coord.x - 1][hero.coord.y].type == MONSTER){
		/* on vérifie que le héros est orienté dans le sens du monstre*/
		if(hero.direction == OUEST){
			(*monster_coords).x = hero.coord.x - 1;
			(*monster_coords).y = hero.coord.y;
			return 1;
		}
	}

	/* on verifie qu'il y a un monstre à côté du héros, ici à sa droite*/
	if(chemin->terrain[hero.coord.x + 1][hero.coord.y].type == MONSTER){
		/* on vérifie que le héros est orienté dans le sens du monstre*/
		if(hero.direction == EST){
			(*monster_coords).x = hero.coord.x + 1;
			(*monster_coords).y = hero.coord.y;
			return 1;
		}
	}

	return 0;

}


/* vérifie si un tresor a été trouvé être lancé*/
/* renvoie 1 si un trésor peut être récupéré*/
/* renvoie 0 si aucun trésor ne peut être récupéré*/
/* enregistre les coordonnées du trésor dans tresor_coords*/
int test_treasure(Perso hero, Terrain * chemin, Coord * tresor_coords){

	if(chemin->terrain[hero.coord.x][hero.coord.y + 1].type == TREASURE){
		if(hero.direction == SUD){
			(*tresor_coords).x = hero.coord.x;
			(*tresor_coords).y = hero.coord.y + 1;
			return 1;
		}
		
	}

	if(chemin->terrain[hero.coord.x][hero.coord.y - 1].type == TREASURE){
		if(hero.direction == NORD){
			(*tresor_coords).x = hero.coord.x;
			(*tresor_coords).y = hero.coord.y - 1;

			return 1;
		}
	}

	if(chemin->terrain[hero.coord.x - 1][hero.coord.y].type == TREASURE){
		if(hero.direction == OUEST){
			(*tresor_coords).x = hero.coord.x - 1;
			(*tresor_coords).y = hero.coord.y;
			return 1;
		}
	}

	if(chemin->terrain[hero.coord.x + 1][hero.coord.y].type == TREASURE){
		if(hero.direction == EST){
			(*tresor_coords).x = hero.coord.x + 1;
			(*tresor_coords).y = hero.coord.y;
			return 1;
		}
	}

	return 0;
}


void generate_terrain_al(Terrain * chemin, int dim_x, int dim_y, int etage){

	int i, etape_2;
	/*int j;*/

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


	generate_treasures_map(&(*chemin), dim_x, dim_y, etage);

	generate_stairs_down(chemin, dim_x, dim_y);

	free_tupleList(&toexpand);

	free_tupleList(&cases_mur);

}



void initialise_dongeon(Donjon * dongeon, int dim_x, int dim_y, int dongeon_size, Terrain * chemin){
	int i;
	/* strcture de dongeon claire pour supprimer le warning de valgrind*/
	/*memset(dongeon->etages,0,sizeof(Terrain));*/
	memset(dongeon,0,sizeof(Donjon));
	
	if(dongeon_size > TAILLE_DONGEON_MAX){
		return;
	}
	(*dongeon).size = dongeon_size;
	/*memset(dongeon,0,sizeof(Donjon));*/
	(*dongeon).etages = (Terrain*) malloc(sizeof(Terrain) * dongeon_size);

	for(i = 0; i < dongeon_size ;i++){

		generate_terrain_al(chemin, LONGUEUR, LARGEUR, i);

		(*dongeon).etages[i] = (*chemin);
	}

	(*dongeon).etage_courant = 0;

	/* strcture de terrain claire pour supprimer le warning de valgrind*/
	memset(chemin,0,sizeof(Terrain));

	(*chemin) = (*dongeon).etages[(*dongeon).etage_courant];
}




/* copie le contenue de send dans dest*/
void copie_Cell(Cell * dest, Cell * send){
	dest->type = send->type;
	if(send->type == MONSTER){
		dest->type =  send->type;
		dest->entity.monster = send->entity.monster;
	}
	else if(send->type == TREASURE){
		dest->type =  send->type;
		copie_coffre_tresor(dest->entity.treasure, send->entity.treasure);

	}
	else if(send->type == ROOM){
		dest->type = send->type;
	}
	else if(send->type == STAIR_UP){
		dest->type =  send->type;
	}
	else if(send->type == WALL){
		dest->type =  send->type;
	}

}
/* copie le contenue de send dans dest*/
void copie_terrain(Terrain * dest, Terrain * send){
	int i,j;
	dest->nb_monster = send->nb_monster;
	dest->x_esc_mont = send->x_esc_mont;
	dest->y_esc_mont = send->y_esc_mont;
	for(i=0; i < LONGUEUR;i++){
		for(j=0;j<LARGEUR;j++){
			copie_Cell(&(dest->terrain[i][j]), &(send->terrain[i][j]));
		}
	}

}
/* fonction de test, vérifie qu'il existe bien un escalier montant*/
void down_exists(Terrain chemin){
	int x_j;
	int y_j;
	int i,j;
	int stop;
	stop = 0;
	x_j = -1;
	y_j = -1;
	for(i =0; i < LONGUEUR; i++){
		if(stop == 1)
			break;
		for(j=0; j < LARGEUR; j++){
					/* on trouve l'échelle montante de l'étage inférieur*/
					if(chemin.terrain[i][j].type == STAIR_DOWN){
						printf("on a trouvé une room up !!\n");
						x_j = i;
						y_j = j;
					stop = 1;
					break;
					}
		}
	}

	printf("Les coordonnées pour room up sont x : %d, y : %d \n", x_j, y_j);

	if(stop ==0)
		printf("on a rien trouvé  pour descendre \n");
}

/***********************************************************************************************************************/




/*


Plusieurs niveaux les niveaux ()


chaque escaliers central est lié par un chemin à un escalier descendant

murs, monstres, trésors sont gen aléatoirement
























*/