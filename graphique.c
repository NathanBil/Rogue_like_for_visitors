#include "../inc/graphique.h"

void initialise_window(){
	MLV_create_window("DONGEON", "DONGEON", X, Y);
}




/*


1 => FOUILLE

2 => MAGIE

3 => ATTAQUE

4 => SAUVEGARDE

5 => INVENTAIRE


*/







int clic_window(int x, int y){



	
	/*MLV_draw_rectangle((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) - 40, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30, 50, 15, MLV_COLOR_DEEPPINK4);


	MLV_draw_rectangle((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) + 20, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30, 50, 15, MLV_COLOR_DEEPPINK4);


	MLV_draw_rectangle((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) +  80, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30, 50, 15, MLV_COLOR_DEEPPINK4);
*/	int x_bouton_inventaire, y_bouton_inventaire, taille_carre;


  	taille_carre = ((X / 2) -  10) / SIZE_INVENTAIRE;

	x_bouton_inventaire =(((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) - 40; 
	y_bouton_inventaire = taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30;


	MLV_draw_filled_rectangle(10, Y - 105, 35, 30 , MLV_COLOR_CYAN);
	MLV_draw_text(10 + (35 / 2) - 2, (Y - 105) + (30 / 4), "S",MLV_COLOR_BLACK);



	MLV_draw_filled_rectangle(10, Y - 160, 35, 30 , MLV_COLOR_ORANGE);
	MLV_draw_text(10 + (35 / 2) - 2, (Y - 160) + (30 / 4), "I",MLV_COLOR_BLACK);

	if(is_in_square(x, y, 10, 100, Y - 20, (Y - 20) + 15) == TRUE){
		printf("\n\nFOUILLE\n\n");
		return 1;
	}

	if(is_in_square(x, y, 10, 10 + JAUGE_ATTAQUE, Y - 65, (Y - 65) + 15) == TRUE){
		printf("\n\nMAGIE\n\n");
		return 2;
	}

	if(is_in_square(x, y, 10, 10 + JAUGE_ATTAQUE , Y - 45, (Y - 45) + 15) == TRUE){
		printf("\n\nATTAQUE\n\n");
		return 3;
	}

	if(is_in_square(x, y, 10, 10 + 35 , Y - 105, (Y - 105) + 30) == TRUE){
		printf("\n\nINVENTAIRE\n");
		return 4;
	}

	if(is_in_square(x, y, 10, 10 + 35 , Y - 160, (Y - 160) + 30) == TRUE){
		printf("\n\nINVENTAIRE\n");
		return 5;
	}

	if(is_in_square(x, y, x_bouton_inventaire, x_bouton_inventaire + 50 , y_bouton_inventaire, y_bouton_inventaire + 15) == TRUE){
		printf("\n\nJETER\n\n");
		return 6;
	}

	if(is_in_square(x, y, x_bouton_inventaire + 60, x_bouton_inventaire + 60 + 50 , y_bouton_inventaire, y_bouton_inventaire + 15) == TRUE){
		printf("\n\nEQUIPER\n\n");
		return 7;
	}


	if(is_in_square(x, y, x_bouton_inventaire + 120, x_bouton_inventaire + 120 + 50 , y_bouton_inventaire, y_bouton_inventaire + 15) == TRUE){
		printf("\n\nRETIRER\n\n");
		return 8;
	}


	/*printf("\n\nUNDEFINED\n\n");*/

	return -1;
}


/*Affiche un menu graphique*/
int menu(){

	MLV_Keyboard_button touche;

	MLV_draw_filled_rectangle((X / 2) - 70, (Y / 2) - 50, 150, 20, MLV_COLOR_YELLOW);
	MLV_draw_filled_rectangle((X / 2) - 70, (Y / 2) + 30, 150, 20, MLV_COLOR_YELLOW);

	MLV_draw_text((X / 2) - 57, (Y / 2) - 50, "1 - Nouvelle partie", MLV_COLOR_BLACK);
	MLV_draw_text((X / 2) - 57, (Y / 2) + 30, "2 - Charger partie", MLV_COLOR_BLACK);

	MLV_actualise_window();

	do{
		MLV_wait_keyboard(&touche, NULL, NULL);

		printf("%d\n", touche);
	}while(touche != 257 && touche != 258 && touche != 38 && touche != 233);

	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_actualise_window();

	if(touche == 257 || touche == 38){
		return 1;
	}

	return 2;

}


void erase_lvl(){

}

void show_perso_lvl(int lvl){

	MLV_draw_filled_ellipse(X - 25, 40, 20, 20, MLV_COLOR_ORANGE);

	MLV_draw_text(X - 28, 30, "%d", MLV_COLOR_SNOW, lvl);


}

/* Donne la possibilité au user de choisir comment il veut améliorer son personnage après une une montée de niveau*/
void choice_level_up(Perso *p1){
	int i;
	int atk;
	int def;
	int inte;
	/* vérifie que le joueur est satisfait de son choix pour les stats à améliorer */
	char valide;
	char choix;
	printf("Félicitation vous êtes monté en niveau, veuillez choisir les stats que vous souhaitez améliorer pour votre personnage: \n");
	/* variable permettant de connnaitre à*/
	
	
	/* Tant que le joueur n'est pas satisfait de son choix d'amélioration des stats, il recommence */
	do{
		atk = 0;
		def = 0;
		inte = 0;
		/* on laisse le joueur incrémenter de LEVEL_UP (3) points les stats qu'il souhaite*/
		for(i=0; i< POINT_LEVEL_UP ;){
			printf("Ecrivez 'Intelligence' pour augmenter l'intelligence, 'Attaque' pour l'attaque, 'Defense' pour la défense (et les hps), 'Recommencer' pour recommencer : \n");
			printf("Vous pouvez encore utiliser %d points \n" ,(POINT_LEVEL_UP-i));
			choix = show_lvl_up();
			if(choix == 'i'){
				inte+= 1;
				i++;
			}
			else if(choix == 'a'){
				atk+= 1;
				i++;
			}
			else if(choix == 'd'){
				def+= 1;
				i++;
			}
			else if(choix == 'r'){
				/* le joueur veut recommencer on réinitialises les points à 0*/
				atk = 0;
				def = 0;
				inte = 0;
				i = 0;
			}
			else{
				printf("Erreur : cette touche est incorrecte !! \n" );
			}
			printf("le résultat du scanf : %c \n", choix);
		}
		/* récapitulatif des choix du joueur*/
		printf("Vous avez donc choisi : \n");
		printf("atk : %d + %d, def : %d + %d, inte : %d + %d \n", p1->atk, atk, p1->def, def, p1->inte, inte);
		/*printf("Veuillez confirmer votre choix 'O' pour 'oui', 'N' ou un autre caractère pour 'non' : \n");*/
		valide = 'O';


	}while(toupper(valide) != 'O');
	/* on incrémente les stats du joueur comme il le souhaitait*/
	(p1)->atk += atk;
	(p1)->inte += inte;
	(p1)->def += def;
	update_perso(p1);
}

/*  vérifie si le personnage doit augmenter en niveau  */
int level_up(Perso *p1){
	int lvl_up;
	lvl_up = 350+(50*p1->lv);
	/* cas où le user augmente en niveau*/
	if(p1->exp >= lvl_up){
		p1->exp -= 350+(50*p1->lv);
		p1->lv +=1;
		printf("le niveau du personnage est maintenant : %d ", p1->lv);
		printf("Son expérience est maintenant : %d \n", p1->exp);
		choice_level_up(p1);
		update_perso(p1);
		return 1;
	}
	/* cas où le user n'augmente pas en niveau*/
	return 0;
}



/*affiche les infos du personnage (barre de vie, de mp)*/
void show_perso(Perso hero){
	/* hp */
	/* contour jauge hp*/
	MLV_draw_rectangle(9, 9, (JAUGE_SIZE) + 1, 16 , MLV_COLOR_WHITE);
	/* jauge d'hp */
	MLV_draw_filled_rectangle(10, 10, ((hero.hp*JAUGE_SIZE)/max_hp(hero)), 15 , MLV_COLOR_GREEN);
	/* affiche le nombre d'hp restant au joueur*/
	MLV_draw_text(15, 8, "%d / %d hp", MLV_COLOR_WHITE, hero.hp, max_hp(hero));
	/* mp */
	MLV_draw_rectangle(9, 24, (JAUGE_SIZE) + 1, 16 , MLV_COLOR_WHITE);
	/* jauge d'mp */
	MLV_draw_filled_rectangle(10, 25, ((hero.mp*JAUGE_SIZE)/max_mp(hero)), 15 , MLV_COLOR_CYAN);
	/* affiche le nombre d'mp restant au joueur*/
	MLV_draw_text(15, 26, "%d / %d mp", MLV_COLOR_WHITE, hero.mp, max_mp(hero));
	/*exp*/
	/* contour jauge expérience*/
	MLV_draw_rectangle(9, 40, (JAUGE_SIZE) + 1, 16 , MLV_COLOR_WHITE);
	/* jauge d'expérience*/
	MLV_draw_filled_rectangle(10, 40, (pourcentage_xp(hero)*JAUGE_SIZE)/100 , 15 , MLV_COLOR_ORANGE);
	/* affiche l'exp nécessaire pour le joueur*/
	MLV_draw_text(15, 42, " %d %% exp"  , MLV_COLOR_WHITE, pourcentage_xp(hero));

	show_perso_lvl(hero.lv);

	MLV_actualise_window();
}

void attente(void){
		MLV_wait_milliseconds(200);
}


void affiche_terrain(int dim_x, int dim_y, Terrain chemin, Perso hero){
	int i, j;

	MLV_Color couleur;

	MLV_clear_window(MLV_COLOR_BLACK);

	couleur = MLV_COLOR_SNOW;

	for(i = 0; i < dim_x ;i++){
		for(j = 0; j < dim_y ;j++){

			if(chemin.terrain[i][j].type == STAIR_UP){
				couleur = MLV_COLOR_GREEN;
			}

			if(chemin.terrain[i][j].type == STAIR_DOWN){
				couleur = MLV_COLOR_PURPLE;
			}

			if(chemin.terrain[i][j].type == WALL){
				couleur = MLV_COLOR_BLACK;
			}

			if(chemin.terrain[i][j].type == ROOM){
				couleur = MLV_COLOR_SNOW;
			}

			if(chemin.terrain[i][j].type == TREASURE){
				couleur = MLV_COLOR_YELLOW;
			}

			if(chemin.terrain[i][j].type == MONSTER){
				printf("Monstre : %d\n", chemin.terrain[i][j].entity.monster.atk);
				couleur = MLV_COLOR_RED;
			}

			if(hero.coord.x == i && hero.coord.y == j){
				couleur = MLV_COLOR_CYAN;
			}



			MLV_draw_rectangle(i*(X/dim_x) + 3, j*(Y/dim_y) + 20, (X/dim_x), (Y/dim_y), couleur);
		}
	}


	show_perso(hero);

	MLV_actualise_window();
}


void show_game(int dim_x, int dim_y, Terrain chemin, Perso hero){

	int i, j, i_bis, j_bis;

	MLV_Color couleur;

	MLV_Image * image_mur, * image_esc_desc, * image_esc_mont, *image_monster, *image_treasure, *image_sol;

	MLV_clear_window(MLV_COLOR_BLACK);

	couleur = MLV_COLOR_BLACK;

	

	image_mur = MLV_load_image("Personnage_dongeon/Mursprite.png");
	image_esc_mont = MLV_load_image("Personnage_dongeon/Escalier_Montant.png");
	image_esc_desc = MLV_load_image("Personnage_dongeon/Escalier_Descendant.png");
	image_monster = MLV_load_image("Personnage_dongeon/Monstre.png");
	image_treasure = MLV_load_image("Personnage_dongeon/Tresor.png");
	image_sol = MLV_load_image("Personnage_dongeon/Sol.png");



	
	i_bis = 0;

	for(i = hero.coord.x - (13/2) ; i < hero.coord.x + (13/2) ; i++){ 
		
		j_bis = 0;

		
		/* test à supprimer (fin)*/
		for(j = hero.coord.y - (9/2); j < hero.coord.y + (9/2); j++){

			if(!(i >= 0 && i < dim_x && j >= 0 && j < dim_y)){

				/*printf("Cordonnées non affichées (%d - %d)\n", i_bis, j_bis);*/
				j_bis ++;
				continue;
			}
			

			if(chemin.terrain[i][j].type == ROOM){
				couleur = MLV_COLOR_BLACK;
			}

			if(chemin.terrain[i][j].type == STAIR_DOWN){
				couleur = MLV_COLOR_BLACK;
			}

			if(chemin.terrain[i][j].type == STAIR_UP){
				couleur = MLV_COLOR_BLACK;
			}

			if(chemin.terrain[i][j].type == TREASURE){
				couleur = MLV_COLOR_BLACK;
			}

			if(chemin.terrain[i][j].type == MONSTER){
				couleur = MLV_COLOR_BLACK;
			}


			MLV_draw_filled_rectangle(i_bis*(X/13) + 3, j_bis*(Y/9) + 20, (X/13), (Y/9), couleur);


			if(chemin.terrain[i][j].type == STAIR_UP){
				MLV_draw_image(image_esc_mont, i_bis*(X/13) - 20 + 3, j_bis*(Y/9) + 10);
			}

			if(chemin.terrain[i][j].type == STAIR_DOWN){
				MLV_draw_image(image_esc_desc, i_bis*(X/13) - 20 + 3, j_bis*(Y/9) + 10);
			}

			if(chemin.terrain[i][j].type == WALL){

					MLV_draw_partial_image(image_mur, 20, 20, (X/13), (Y/9), i_bis*(X/13) + 3, j_bis*(Y/9) + 20);
			}

			if(chemin.terrain[i][j].type == MONSTER){

					MLV_draw_partial_image(image_monster, 20, 20, (X/13), (Y/9), i_bis*(X/13), j_bis*(Y/9) + 30);
			}

			if(chemin.terrain[i][j].type == TREASURE){

					MLV_draw_partial_image(image_treasure, 20, 20, (X/13), (Y/9), i_bis*(X/13) + 3, j_bis*(Y/9) + 25);
			}


			if(hero.coord.x == i && hero.coord.y == j){

				MLV_Image * image;

				switch(hero.direction){
					case NORD : {
						image = MLV_load_image("Personnage_dongeon/Haut.png");
						MLV_draw_image(image, i_bis*(X/13) - 19, j_bis*(Y/9) + 10);
						MLV_free_image(image);
						break;
					}

					case SUD : {
						image = MLV_load_image("Personnage_dongeon/Bas.png");
						MLV_draw_image(image, i_bis*(X/13) - 20, j_bis*(Y/9) + 20);
						MLV_free_image(image);
						break;
					}

					case EST : {
						image = MLV_load_image("Personnage_dongeon/Droite.png");
						MLV_draw_image(image, i_bis*(X/13) - 20, j_bis*(Y/9) + 10);
						MLV_free_image(image);
						break;
					}

					case OUEST: {
						image = MLV_load_image("Personnage_dongeon/Gauche.png");
						MLV_draw_image(image, i_bis*(X/13) - 20, j_bis*(Y/9) + 10);
						MLV_free_image(image);
						break;
					}

				}
	
	
			}

			j_bis++;
		}
		i_bis ++;
	}


	MLV_free_image(image_mur);
	MLV_free_image(image_esc_mont);
	MLV_free_image(image_esc_desc);
	MLV_free_image(image_monster);
	MLV_free_image(image_treasure);
	MLV_free_image(image_sol);

	MLV_draw_filled_rectangle(10, Y - 105, 35, 30 , MLV_COLOR_CYAN);
	MLV_draw_text(10 + (35 / 2) - 2, (Y - 105) + (30 / 4), "S",MLV_COLOR_BLACK);
	MLV_draw_filled_rectangle(10, Y - 160, 35, 30 , MLV_COLOR_ORANGE);
	MLV_draw_text(10 + (35 / 2) - 2, (Y - 160) + (30 / 4), "I",MLV_COLOR_BLACK);
	show_perso(hero);
	

	MLV_actualise_window();


}


/* attend un événement du joueur*/
/* 1 signifie qu'il ne se passe rien, généralement cela a lieu lors d'un déplacement */
/* elle renvoie 2 si il souhaite sauvegarder*/
/* elle renvoie 3 si il souhaite faire une fouille*/
/* elle renvoei 4 si il lance un combat en rentrant dans un monstre
	5 => Attaque
	6 => Magie
*/
/* sinon elle renvoie 1*/

int wait_event(Perso * perso, Terrain * chemin, int limit_x, int limit_y, Potion tab_potion[MAX_USED_POTION]){
	
	int x_mouse, y_mouse, clic;
	MLV_Keyboard_button touche;
	MLV_Event event_type = MLV_NONE;
	x_mouse = -1;
	y_mouse = -1;

	event_type = MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &x_mouse, &y_mouse);

	clic = clic_window(x_mouse, y_mouse);

	/*printf("Votre clic vaut : %d\n", clic);*/

	if(event_type == MLV_KEY){


		if(touche == MLV_KEYBOARD_DOWN) {

			if(perso->direction != SUD){

				perso->direction = SUD;

				return 1;
			}
			
			/* on autorise le personnage a se déplacer si il entre dans une room, ou qu'il arrive sur une échelle*/
			if( (chemin != NULL && chemin->terrain[perso->coord.x][perso->coord.y + 1].type == ROOM) || (chemin->terrain[perso->coord.x][perso->coord.y + 1].type == STAIR_DOWN )
				|| (chemin->terrain[perso->coord.x][perso->coord.y + 1].type == STAIR_UP)){
				active_tab_potion(perso, tab_potion);
				deplacement_perso(perso, SUD, limit_x, limit_y);
				return 1;
			}
			/* on verifie s'il y a un monstre à côté du héros, ici en haut*/
			else if(chemin != NULL && chemin->terrain[perso->coord.x][perso->coord.y + 1].type == MONSTER){
				active_tab_potion(perso, tab_potion);
				return 4;
			}

			/* on ouvre un coffre au trésor*/

			else if(chemin != NULL && chemin->terrain[perso->coord.x][perso->coord.y + 1].type == TREASURE){
				return 3;

			}
		}

		else if(touche == MLV_KEYBOARD_LEFT ){
			
			if(perso->direction != OUEST){

				perso->direction = OUEST;

				return 1;
			}
			/* on autorise le personnage a se déplacer si il entre dans une room, ou qu'il arrive sur une échelle*/
			if( (chemin != NULL && chemin->terrain[perso->coord.x - 1][perso->coord.y].type == ROOM )|| (chemin->terrain[perso->coord.x - 1][perso->coord.y].type == STAIR_UP)
				|| (chemin->terrain[perso->coord.x - 1][perso->coord.y].type == STAIR_DOWN)){
				active_tab_potion(perso, tab_potion);
				deplacement_perso(perso, OUEST, limit_x, limit_y);
				
			}
			
			/* on verifie s'il y a un monstre à côté du héros, ici  à gauche*/
			else if(chemin != NULL && chemin->terrain[perso->coord.x - 1][perso->coord.y].type == MONSTER){
				active_tab_potion(perso, tab_potion);
				return 4;
			}

			/*on ouvre un coffre au trésor*/
			else if(chemin != NULL && chemin->terrain[perso->coord.x - 1][perso->coord.y].type == TREASURE){
				return 3;
			}
		}

		else if(touche == MLV_KEYBOARD_UP) {
			
			if(perso->direction != NORD){

				perso->direction = NORD;

				return 1;
			}
	
			/* on autorise le personnage a se déplacer si il entre dans une room, ou qu'il arrive sur une échelle*/
			if( (chemin != NULL && chemin->terrain[perso->coord.x][perso->coord.y - 1].type == ROOM) || (chemin->terrain[perso->coord.x][perso->coord.y - 1].type == STAIR_DOWN) ||
			(chemin->terrain[perso->coord.x][perso->coord.y - 1].type == STAIR_UP)){
				active_tab_potion(perso, tab_potion);
				deplacement_perso(perso, NORD, limit_x, limit_y);
				
			}
			
			/* on verifie s'il y a un monstre à côté du héros, ici  en bas*/
			else if(chemin != NULL && chemin->terrain[perso->coord.x][perso->coord.y - 1].type == MONSTER){
				active_tab_potion(perso, tab_potion);
				return 4;
			}
			/* on ouvre un coffre*/
			else if(chemin != NULL && chemin->terrain[perso->coord.x][perso->coord.y - 1].type == TREASURE){
				return 3;
			}
		}

		else if(touche == MLV_KEYBOARD_RIGHT) {
			
			if(perso->direction != EST){

				perso->direction = EST;

				return 1;
			}
			active_tab_potion(perso, tab_potion);
			
			/* on autorise le personnage a se déplacer si il entre dans une room, ou qu'il arrive sur une échelle*/
			if((chemin != NULL && chemin->terrain[perso->coord.x + 1][perso->coord.y].type == ROOM) || (chemin->terrain[perso->coord.x + 1][perso->coord.y].type == STAIR_DOWN)
				|| (chemin->terrain[perso->coord.x + 1][perso->coord.y].type == STAIR_UP)){
				active_tab_potion(perso, tab_potion);
				deplacement_perso(perso, EST, limit_x, limit_y);
			}
			
			/* on verifie qu'il y a un monstre à côté du héros, ici à sa droite*/
			else if(chemin != NULL && chemin->terrain[perso->coord.x + 1][perso->coord.y].type == MONSTER){
				active_tab_potion(perso, tab_potion);
				return 4;
			}
			/* on ouvre un coffre*/
			else if(chemin != NULL && chemin->terrain[perso->coord.x + 1][perso->coord.y].type == TREASURE){
				return 3;
			}
		}

		/* cas où le user souhaite sauvegarder*/
		else if(touche ==  MLV_KEYBOARD_s){
			return 2;
		}
		/* cas où il souhaite faire une fouille*/
		else if(touche ==  MLV_KEYBOARD_d){
			return 3;
		}


		/*show_inventaire(*perso, 0, chemin->nb_monster);*//*À la place du 0 mettre le curseur*/
		/* cas où le user souhaite modifier son inventaire */
		else if(touche ==  MLV_KEYBOARD_i){

			show_inventaire(*perso, 0, chemin->nb_monster);	/*À la place du 0 mettre le curseur*/
			/*show_inventaire_equipement(*perso);
			show_inventaire_potion(*perso);*/
			modifier_inventaire(perso, tab_potion, chemin->nb_monster);
			/* on veut arrêter d'afficher l'inventaire*/
			return 9;
			
		}

		/*attaque MAGIE*/
		else if(touche == MLV_KEYBOARD_z){
			return 5;
		}

		/*ATTAQUE melee*/
		else if(touche == MLV_KEYBOARD_a){
			return 6;
		}

		/*On coupe ou active les musiques*/
		else if(touche == MLV_KEYBOARD_r){
			return 7;
		}

		/*On coupe ou active les sons*/
		else if(touche == MLV_KEYBOARD_t){
			return 8;
		}

	}
	else{

		/*ACTIONS DU JOUEUR AVEC LES CLICS*/
		if(clic  == 1){
			return 3;
		}


		/* cas où le user souhaite modifier son inventaire */
		else if(clic == 5){

			show_inventaire(*perso, 0, chemin->nb_monster);	/*À la place du 0 mettre le curseur*/
			/*show_inventaire_equipement(*perso);
			show_inventaire_potion(*perso);*/
			modifier_inventaire(perso, tab_potion, chemin->nb_monster);
			/* on veut arrêter d'afficher l'inventaire*/
			return 1;
		}

		/* cas où le user souhaite sauvegarder*/
		else if(clic == 4){
			return 2;
		}

		/* gestion des attaques */
		/* attaque mélée*/
		else if(clic == 3){
			return 6;
		}
		/*attaque magique*/
		else if(clic == 2){
			return 5;
		}
		


	}
	/* il ne se passe rien*/
	return 13;

}


/*Affiche un message en haut de la fenêtre ainsi que les stats du joueur
durant la partie*/
void animation_end(const char * message, Perso hero, Donjon dongeon){

	MLV_clear_window(MLV_COLOR_BLACK);


	MLV_draw_text((X / 2) - 25, 50, message, MLV_COLOR_ORANGE);


	MLV_draw_text((X / 2) - 25, Y /2 - 40, "Niveau atteint: %d", MLV_COLOR_ORANGE, hero.lv);
	MLV_draw_text((X / 2) - 25, Y /2 - 20, "HP : %d", MLV_COLOR_ORANGE, hero.hp);
	MLV_draw_text((X / 2) - 25, Y /2, "MP : %d", MLV_COLOR_ORANGE, hero.mp);
	MLV_draw_text((X / 2) - 25, Y /2 + 20, "Monstres tués : %d", MLV_COLOR_ORANGE, hero.stats.monster_killed);
	MLV_draw_text((X / 2) - 25, Y /2 + 40, "Trésors ouverts : %d", MLV_COLOR_ORANGE, hero.stats.treasures_opened);
	MLV_draw_text((X / 2) - 25, Y /2 + 60, "Etage  : %d", MLV_COLOR_ORANGE, dongeon.etage_courant + 1);

	MLV_actualise_window();

	MLV_wait_seconds(10);
}

void close_window(){
	MLV_free_window();
}

/* cette fonction affiche un msg si le joueur n'a pas suffisamment de mp pour attaquer*/
void msg_mp(void){
	MLV_draw_text(X/3, 25, " Vous n'avez pas suffisamment de mp " , MLV_COLOR_RED);
	MLV_actualise_window();
	MLV_wait_seconds(2);
}

/* affiche les différentes barrres liées aux actions possibles pendant un combat*/
/* on affiche aussi un triangle sur le monstre qui est en face du joueur*/
void barre_combat(void){
	/* barre d'attaque normale */
	MLV_draw_filled_rectangle(10, Y - 45, JAUGE_ATTAQUE, 15 , MLV_COLOR_DARK_RED);
	/* affiche la touche pour l'attaque normal*/
	MLV_draw_text(15, Y - 45, "Attaque (A)", MLV_COLOR_WHITE);
	/* barre d'attaque magique */
	MLV_draw_filled_rectangle(10, Y - 65, JAUGE_ATTAQUE, 15 , MLV_COLOR_YELLOW);
	/* affiche la touche pour l'attaque magique*/
	MLV_draw_text(15, Y - 65, "Magie (Z)", MLV_COLOR_BLACK);
	MLV_actualise_window();

}



/*affiche les infos du monstre (barre de vie)*/
/* numero correspond à l'ordre dans lequel apparait le monstre, cela permet de savoir où placer sa jauge*/
void show_monster_hp(Monster monster, int numero){

	/* jauge d'hp */
	MLV_draw_filled_rectangle(X - 180, Y - (20 * numero), ((monster.hp*JAUGE_SIZE)/monster.max_hp), 15 , MLV_COLOR_RED);
	/* affiche le nombre d'hp restant du monstre*/
	MLV_draw_text(X - 145, Y-(20 * numero), "%d / %d hp", MLV_COLOR_WHITE, monster.hp, monster.max_hp);
	MLV_actualise_window();
}

/* affiche les dégats reçu par le monstre après une attaque*/
void show_degats_monstre(int numero, int degats){
	/* affiche le nombre d'hp perdus du monstre*/
	MLV_draw_text(X - 175, Y-(20 * numero), " - %d", MLV_COLOR_BLUE, degats);
	MLV_actualise_window();

}

/* affiche les dégats reçu par le monstre après une attaque*/
void show_degats_perso(int degats){
	/* affiche le nombre d'hp perdu du joueur*/
	MLV_draw_text(115, 8, "- %d ", MLV_COLOR_RED, degats);
	MLV_actualise_window();


}

/* fonction qui teste si le combat continue ou non*/
/* elle renvoie false (0) si le héros fuit, et true (1)sinon*/
int test_resume_fight(Perso hero, Coord monster_coord){
	int diffx;
	int diffy;

	diffx = hero.coord.x - monster_coord.x;
	diffy = hero.coord.y - monster_coord.y;
	/* cas où le perso est tourné vers l'est et l'ennemi est à l'est*/
	if(diffx == -1 && hero.direction == EST)
		return FALSE;
	/* cas où le perso est tourné vers l'ouest et l'ennemi est à l'ouest*/
	if(diffx == +1 && hero.direction == OUEST)
		return FALSE;
	/* cas où le perso est tourné vers le nord etl'ennemi au nord*/
	if(diffy == +1 && hero.direction == NORD)
		return FALSE;
	/* cas où le perso est tourné vers le sud alors que l'ennemi est au sud*/
	if(diffy == -1 && hero.direction == SUD)
		return FALSE;

	return TRUE;

}

/* Elle modifie (corrige) la position du héros selon les coordonnées du monstre suivant auquel il peut faire face dans le même combat */
void new_position_fight(Perso * hero, Coord monster_coord){
	int diffx;
	int diffy;

	diffx = hero->coord.x - monster_coord.x;
	diffy = hero->coord.y - monster_coord.y;
	/* cas où le perso est tourné vers autre chose que l'est alors que l'ennemi est à l'est*/
	if(diffx == -1 && hero->direction != EST){
		hero->direction = EST;
	}
	/* cas où le perso est tourné vers autre chose que l'ouest alors que l'ennemi est à l'ouest*/
	if(diffx == +1 && hero->direction != OUEST)
		hero->direction = OUEST;
	/* cas où le perso est tourné vers autre chose que le nord  alors que l'ennemi est au nord*/
	if(diffy == +1 && hero->direction != NORD)
		hero->direction = NORD;
	/* cas où le perso est tourné vers le nord alors que l'ennemi est au sud*/
	if(diffy == -1 && hero->direction != SUD)
		hero->direction = SUD;

}

/* fait changer la direction du joueur ou confirme sa fuite, selon son choix*/
/* renvoie TRUE (0) s'il veut fuir et FALSE (1) si il a seulement changé de direction*/
int wait_fuite_direction(Perso *perso){
	int x_mouse, y_mouse;
	MLV_Keyboard_button touche;
	int clic;
	/* le perso change de direction*/
	MLV_Event event_type = MLV_NONE;
	x_mouse = -1;
	y_mouse = -1;
	clic = -1;
	
	event_type = MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &x_mouse, &y_mouse);
	/* flèche directionnelle ou touche du clavier*/
	if(event_type == MLV_KEY){


		if(touche == MLV_KEYBOARD_DOWN) {

				perso->direction = SUD;

				return FALSE;
		}

		else if(touche == MLV_KEYBOARD_UP) {

				perso->direction = NORD;

				return FALSE;
		}

		else if(touche == MLV_KEYBOARD_LEFT ){

				perso->direction = OUEST;

				return FALSE;
		}


		else if(touche == MLV_KEYBOARD_RIGHT) {

				perso->direction = EST;

				return FALSE;
		}

		/*fuite du joueur*/
		else if(touche == MLV_KEYBOARD_e){
			return TRUE;
		}


	}
	else{

		/*fuite du joueur*/
		if(clic  == 1){
			return TRUE;
		}

	}
	/* le perso continue le combat*/
	return FALSE;
	
}

/* regarde si le joueur a changé de direction en plein combat, si oui on lui demande avec Wait_event s'il veut fuir , si oui il fuit*/
/* elle renvoie TRUE (0) si il veut fuir et (1) false sinon*/
int fuite_mouv(Perso *perso, Direction old_dir, Terrain * chemin, Coord monster_coords[MAX_MONSTER]){
	/* récupère le fait que oui ou non le joueur voulait fuir*/
	/*int res;*/
	/* vérifie si le héros veut toujours se battre*/
	int resume;
	/* on regarde si un combat est toujours possible*/
	resume = test_fight(*perso, chemin, monster_coords);

	/* on constate que le joueur a changé de direction et qu'il n'est plus orienté vers un monstre*/
	if(perso->direction != old_dir && resume == 0){
		return TRUE;
	}
	/* cas où le joueur n'a pas changé de direction par rapport à avant ou qu'il fait toujours face à un monstre*/
	return FALSE;


}

/* permet de passer de coordonnées de coord à une position sur l'écran*/
/* renvoie la nouvelle coord*/
int reecrire_coordx_monster(int x, Perso hero){
	if(hero.direction == EST)
		return ((x * LONGUEUR/2)/hero.coord.x)+30;
	else if(hero.direction == OUEST)
		return ((x * X/2)/hero.coord.x)-20;
	return ((x * X/2)/hero.coord.x);
}

/* permet de passer de coordonnées de coord à une position sur l'écran*/
/* renvoie la nouvelle coordonnée*/
int reecrire_coordy_monster(int y, Perso hero){
	if(hero.direction == SUD)
		return ((y * Y/2)/hero.coord.y)+30;
	else if(hero.direction == NORD)
		return ((y * Y/2)/hero.coord.y)-30;
	return ((y * Y/2)/hero.coord.y);

}

/* permet de passer de coordonnées de coord à une position sur l'écran*/
/* renvoie la nouvelle coord*/
int reecrire_coordx_perso(int x, Perso hero){
	if(hero.direction == EST)
		return ((x * X/2)/hero.coord.x);
	else if(hero.direction == OUEST)
		return ((x * X/2)/hero.coord.x);
	return ((x * X/2)/hero.coord.x);
}

/* permet de passer de coordonnées de coord à une position sur l'écran*/
/* renvoie la nouvelle coord*/
int reecrire_coordy_perso(int y, Perso hero){
	if(hero.direction == SUD)
		return ((y * Y/2)/hero.coord.y);
	else if(hero.direction == NORD)
		return ((y * Y/2)/hero.coord.y);
	return ((y * Y/2)/hero.coord.y);

}

/* affiche à côté du perso les dégâts subis*/

void affiche_degats(int x, int y, int degats){
	MLV_draw_text(x, y, "%d", MLV_COLOR_RED, degats);
	MLV_actualise_window();
}

/* fait en sorte qu'une liste de monstre attaquent le perso tour à tour*/
void list_monster_atk_perso(Perso * hero, Terrain * chemin, Coord monster_coord[MAX_MONSTER]){
	int i;
	int degats;
	Coord monster;
	for(i = 0 ; i < MAX_MONSTER; i++){
		if(monster_coord[i].x != -1 && monster_coord[i].y != -1){
			monster.x = monster_coord[i].x;
			monster.y = monster_coord[i].y;
			monster_atk_perso(hero, chemin->terrain[monster.x][monster.y].entity.monster,&degats);
			show_degats_perso(degats);
			/* attente pour afficher les dégâts perdus pour le joueur*/
			attente();
		}
	}

}

/* fonction qui génère des nouveaux monstres lorsque le user s'est fait piéger*/
void spawn_monster(Perso hero, Terrain * chemin, Coord monster_coords[MAX_MONSTER]){
	Coord monster;
	vide_tab_monster(monster_coords);

	/* on verifie qu'il y a un monstre à côté du héros, ici en haut*/
	if(chemin->terrain[hero.coord.x][hero.coord.y + 1].type == MONSTER){
			monster.x = hero.coord.x;
			monster.y =  hero.coord.y + 1;
			add_monster(monster_coords, monster);
	}
	/* on verifie qu'il y a un monstre à côté du héros, ici en bas*/
	if(chemin->terrain[hero.coord.x][hero.coord.y - 1].type == MONSTER){
			monster.x = hero.coord.x;
			monster.y = hero.coord.y - 1;
			add_monster(monster_coords, monster);
		
	}
	/* on verifie qu'il y a un monstre à côté du héros, ici à sa gauche*/
	if(chemin->terrain[hero.coord.x - 1][hero.coord.y].type == MONSTER){
			monster.x = hero.coord.x-1;
			monster.y = hero.coord.y;
			add_monster(monster_coords, monster);
	}

	/* on verifie qu'il y a un monstre à côté du héros, ici à sa droite*/
	if(chemin->terrain[hero.coord.x + 1][hero.coord.y].type == MONSTER){
			monster.x = hero.coord.x+1;
			monster.y = hero.coord.y;
			add_monster(monster_coords, monster);
	}

}

/* renvoie 1 si le joueur peut tomber sur un assaut de monstres et 0 sinon*/
/* le joueur a une chance sur 30 de tomber sur un groupe de monstre*/
int random_trap(void){
	int trap;
	trap = rand()%30;
	/* si on tombe sur le nombre 1 on peut tomber sur un piège, on a une chance sur 30 
	pour que ça arrive*/
	if(trap == 1)
		return 1;
	return 0;
}

/* génère plusieurs monstre autour du perso lors d'un piège*/
void piege_monster(Perso hero, Terrain * chemin, Coord monster_found[MAX_MONSTER], int etage){
	/*int i,j;*/
	/* on ajoute deux monstres au plus*/
	int compteur;
	/* récupère l'info de si oui ou non un groupe de monstre peut attaquer le joueur*/
	int trap;
	/* le joueur a une chance sur 3 de voir apparaitre deux monstres en plus, 1/3 de voir 1 monstre apparaitre et 1 chance sur 3 d'en voir 0*/
	/* le joueur a une chance sur 30 de tomber sur un groupe de monstre*/
	trap =  random_trap();
	if(trap == 0)
		return;
	compteur = rand()%2;
	if(chemin->terrain[hero.coord.x][hero.coord.y+1].type == ROOM && compteur > 0){

		(chemin->terrain[hero.coord.x][hero.coord.y+1]).entity.monster = generate_trap_monster(etage);
		(chemin->terrain[hero.coord.x][hero.coord.y+1]).type = MONSTER;
		compteur--;
		chemin->nb_monster++;

	}
	if(chemin->terrain[hero.coord.x+1][hero.coord.y].type == ROOM && compteur > 0){

		(chemin->terrain[hero.coord.x+1][hero.coord.y]).entity.monster= generate_trap_monster(etage);
		(chemin->terrain[hero.coord.x+1][hero.coord.y]).type = MONSTER;
		compteur--;
		chemin->nb_monster++;

	}
	if(chemin->terrain[hero.coord.x][hero.coord.y-1].type == ROOM && compteur > 0){

		(chemin->terrain[hero.coord.x][hero.coord.y-1]).entity.monster = generate_trap_monster(etage);
		(chemin->terrain[hero.coord.x][hero.coord.y-1]).type = MONSTER;
		compteur--;
		chemin->nb_monster++;

	}
	if(chemin->terrain[hero.coord.x-1][hero.coord.y].type == ROOM && compteur > 0){

		(chemin->terrain[hero.coord.x-1][hero.coord.y]).entity.monster = generate_trap_monster(etage);
		(chemin->terrain[hero.coord.x-1][hero.coord.y]).type = MONSTER;
		compteur--;
		chemin->nb_monster++;

	}
	/* on remet à jour les monstres autour du joueur*/
	spawn_monster(hero, chemin, monster_found);


}


/* actualise la position du héro lors d'un mouvement de côté*/
/*void actualise_orientation_perso(Perso hero){

}*/


/*gère un combat*/
/* elle renvoie false si le combat est fini, elle renvoie true si il continue*/
int fight(Perso * hero, Terrain * chemin, Coord monster_coord[MAX_MONSTER], Potion tab_potion[MAX_USED_POTION]){
	
	Monster monster_found; 
	/*coordonnée du monstre que le joueur cible actuellement*/
	Coord monster_target;
	/* variable qui récupère le type de l'attaque choisie par le joueur */
	MLV_Keyboard_button atk;
	/* variable qui vérifie que le coup du user est valide ou non. Elle nécessaire pour les attaques magiques*/
	int valide;
	int degats;
	int fuite;
	int numero;
	/* ancienne direction du héros*/
	Direction old_dir;
	old_dir = hero->direction;

	fuite = FALSE;
	valide = FALSE;
	numero = 1;

	/* on met à jour tous l'affichage du jeu pour éviter que des infos ne se superposent*/
	show_game(LONGUEUR, LARGEUR, *chemin, *hero);
	if(hero->hp <= 0){
		return FALSE;
	}

	/* on récupère les coordonnées du premier monstre ciblé par le joueur*/
	find_one_monster(*hero, chemin, &monster_target);
	monster_found = chemin->terrain[monster_target.x][monster_target.y].entity.monster;

	/* tant que le joueur n'entre pas une touche valide on récupère sa saisie*/
	do{


		/* on met à jour tous l'affichage du jeu pour éviter que des infos ne se superposent*/
		show_game(LONGUEUR, LARGEUR, *chemin, *hero);


		/* on prévient le joueur qu'il peut attaquer*/
		barre_combat();

		show_monster_hp(monster_found,1);

		/*on récupère l'attaque choisie par le joueur dans "atk"*/

		atk = wait_event(hero, chemin, LONGUEUR, LARGEUR, tab_potion);
		/* si le user fait une attaque melee*/
		if(atk == 6){
			/*printf("\n\n\nAttaque effectuée\n\n\n");*/
			/* récupère la valeur de retour de l'attaque pour s'assurer qu'elle est valide*/
			/* pour une attaque melee c'est toujours le cas normalement*/
			valide =  perso_atk_melee_monster(hero, &chemin->terrain[monster_target.x][monster_target.y].entity.monster, &degats);
		}
		/* si le user fait une attaque magique*/
		else if(atk == 5){
			/*printf("\n\n\nMagie effectuée\n\n\n");*/

			/* récupère la valeur de retour de l'attaque pour s'assurer qu'elle est valide*/
			/* pour une attaque magique ça dépend du nombre de mp du joueur*/
			valide = perso_atk_magique_monster(hero, &chemin->terrain[monster_target.x][monster_target.y].entity.monster, &degats);
			if(valide == FALSE){
				/*envoie un message sur l'écran du user si celui-ci n'a pas assez de mp*/
				msg_mp();
			}
		}


		/* si le joueur utilise son inventaire*/
		else if(atk == 9){
			/*printf("\n\n\n Vous avez utilisé votre inventaire le monstre en profite pour vous attaquer !\n\n\n");*/
			/* si le joueur utilise son inventaire*/
			show_game(LONGUEUR, LARGEUR, *chemin, *hero);
			valide = FALSE;
			fuite = FALSE;
		}
		/* si le perso fuit et qu'il n'y a pas de monstre autour alors il peut fuir*/
		else if(atk == 1 && fuite_mouv(hero, old_dir, chemin, monster_coord) == TRUE && test_fight(*hero, chemin, monster_coord) == 0){
			fuite = TRUE;
			valide = TRUE;
		}
		/* le perso change de cible mais ne fuit pas ou fait une action inutile*/
		else {
			/* on met à jour le monstre ciblé par le personnage*/
			find_one_monster(*hero, chemin, &monster_target);
			monster_found = chemin->terrain[monster_target.x][monster_target.y].entity.monster;
		}

	}while((atk != 6 && atk != 5 && fuite == FALSE && atk != 1) || valide == FALSE);

	/* on retire le monstre s'il est mort*/
	if(chemin->terrain[monster_target.x][monster_target.y].entity.monster.hp <= 0){
		/* on affiche les dégâts reçus par le monstre*/
		show_degats_monstre(numero, degats);
		chemin->nb_monster--;
		hero->stats.monster_killed++;
		
		attente();
		retire_monster(monster_coord, monster_target);
		chemin->terrain[monster_target.x][monster_target.y].type = ROOM;
		chemin->terrain[monster_target.x][monster_target.y].entity.monster.atk = 0;

	}
	/* s'il n'y a plus de monstre dans le tableau on arrête le combat*/
	if(is_empty_tab_monster(monster_coord) == 1){
		attente();

		chemin->terrain[monster_target.x][monster_target.y].type = ROOM;
		chemin->terrain[monster_target.x][monster_target.y].entity.monster.atk = 0;

		/* vide entièrement le tableau des monstres dans le tableau où sont enregistrées les coordonnées des monstres attaqués*/
		vide_tab_monster(monster_coord);
		/* le combat est fini*/
		return FALSE;
	}
	/* le joueur a tué un monstre mais il en reste encore, le joueur n'a pas fuit*/
	else if(is_empty_tab_monster(monster_coord) == 0 && fuite == FALSE && valide == TRUE  && chemin->terrain[monster_target.x][monster_target.y].entity.monster.hp <= 0){
		chemin->nb_monster--;
		hero->stats.monster_killed++;
		/* on affiche les dégâts reçus par le monstre*/
		show_degats_monstre(numero, degats);
		attente();
		chemin->terrain[monster_target.x][monster_target.y].type = ROOM;
		chemin->terrain[monster_target.x][monster_target.y].entity.monster.atk = 0;
		retire_monster(monster_coord, monster_target);
		/* le combat continue*/
		/* on ajoute les coordonnées du premier monstre encore en vie dans la target*/
		first_monster(monster_coord, &monster_target);
		new_position_fight(hero, monster_target);
		/* les monstres restants attaquent chacun leur tour le perso*/
		list_monster_atk_perso(hero, chemin, monster_coord);
	}
	/* le combat continue le joueur attaque*/
	/* le joueur attaque mais il n'a tué personne */
	else if(valide == TRUE && fuite == FALSE && atk != 1){
		/* on affiche les dégâts reçus par le monstre*/
		show_degats_monstre(numero, degats);
		/* attente pour afficher les dégâts perdus pour le monstre*/
		attente();
		list_monster_atk_perso(hero, chemin, monster_coord);
	}
	/* le joueur fuit ou utilise son inventaire*/
	else if(fuite == TRUE || atk == 1){
		list_monster_atk_perso(hero, chemin, monster_coord);
	}

	/*le perso fuit*/
	if(!test_resume_fight(*hero, monster_target)){
		printf("Vous avez pris la fuite ! \n ");
		return FALSE;
	}
	/* le combat continue*/
	return TRUE;
}










