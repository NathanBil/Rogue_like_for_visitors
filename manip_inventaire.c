#include "../inc/manip_inventaire.h"


void erase_perso(){
	MLV_draw_filled_rectangle(10, 10, JAUGE_SIZE+1, 15 , MLV_COLOR_BLACK);
	MLV_draw_filled_rectangle(10, 25, JAUGE_SIZE+1 , 15 , MLV_COLOR_BLACK);
	MLV_draw_filled_rectangle(10, 40, JAUGE_SIZE+1 , 15 , MLV_COLOR_BLACK);

}


void monstre_restant(int restant){

	MLV_Image *image_monster;

	image_monster = MLV_load_image("Personnage_dongeon/Monstre.png");
	if(image_monster == NULL)
		return;
	MLV_draw_image(image_monster, 120, Y/2+15);
	MLV_draw_text(150, Y/2+15, " X %d"  , MLV_COLOR_RED, restant);
	MLV_free_image(image_monster);
}

/* fonction qui affiche graphiquement l'inventaire*/
void show_inventaire(Perso perso, int curseur, int nb_monster){
	int i, j, taille_carre;

	MLV_Image * image;
	MLV_Color color;

	color = MLV_COLOR_DEEPPINK4;


	taille_carre = ((X / 2) -  10) / SIZE_INVENTAIRE;


	MLV_draw_filled_rectangle( (X / 4), (Y / 4), (taille_carre + 4) * SIZE_INVENTAIRE + 4, taille_carre * (NB_INVENTAIRE  + 2), MLV_COLOR_MAROON);

	

	for(i = 0; i < NB_INVENTAIRE ; i++ ){


		for(j = 0; j < SIZE_INVENTAIRE; j++){


			if(i == NB_INVENTAIRE - 1){
				color = MLV_COLOR_GRAY;
			}

			if((curseur == j && curseur < SIZE_INVENTAIRE && i == 0) || (curseur == j + SIZE_INVENTAIRE && curseur >= SIZE_INVENTAIRE && i == 1) 
				|| (curseur == j + SIZE_INVENTAIRE*2 && curseur >= SIZE_INVENTAIRE*2 && i == 2))
				MLV_draw_filled_rectangle((taille_carre + 4) * (j) + (X / 4) + 3 , (taille_carre + 4) * (i) + (Y/ 4) + 3, taille_carre + 4, taille_carre + 4, MLV_COLOR_CYAN);

			MLV_draw_filled_rectangle((taille_carre + 4) * (j) + (X / 4) + 5 , (taille_carre + 4) * (i) + (Y/ 4) + 5, taille_carre, taille_carre, color);
			/*printf("i=%d",i);*/
		}
	}




	for(i = 0; i < NB_INVENTAIRE ; i++ ){
		for(j = 0; j < SIZE_INVENTAIRE; j++){

			/* */
			if(i == 0 || (i == 2 && j <= 2)){ /*Equipement*/
			/* soit dans la partie inventaire soit dans la partie qui montre ce que le joueur porte*/

				if(perso.invent[i][j].eq.exists == TRUE){

					if(perso.invent[i][j].eq.type == ARME){
						image = MLV_load_image("Personnage_dongeon/Epee.png");
					}

					if(perso.invent[i][j].eq.type == ARMURE){
						image = MLV_load_image("Personnage_dongeon/Armure.png");
					}

					if(perso.invent[i][j].eq.type == BAGUETTE){
						image = MLV_load_image("Personnage_dongeon/Baguette_Magique.png");
					}

					/*fprintf(stderr, "Aie Equipement\n");*/
					MLV_draw_image(image, (taille_carre + 4) * (j) + (X / 4) - 20, (taille_carre + 4) * (i) + (Y/ 4) - 20);
					MLV_free_image(image);
					/*fprintf(stderr, "Aie Equipement\n");*/
				}
				
			}
			/**/
			if(i == 1 || (i == 2 && j < SIZE_INVENTAIRE && j >= 3)){	/*Potion*/
			/* soit dans la partie inventaire soit dans la partie qui montre ce que le joueur porte*/
				if(perso.invent[i][j].pot.exists == TRUE){

					if(perso.invent[i][j].pot.type == SOIN){
						image = MLV_load_image("Personnage_dongeon/Potion_Green.png");
					}

					if(perso.invent[i][j].pot.type == MAGIE){
						image = MLV_load_image("Personnage_dongeon/Potion_Blue.png");
					}

					if(perso.invent[i][j].pot.type == REGENERATION){
						image = MLV_load_image("Personnage_dongeon/Potion_Purple.png");
					}

					if(perso.invent[i][j].pot.type == PRECISION_POT){
						image = MLV_load_image("Personnage_dongeon/Potion_Yellow.png");
					}

					if(perso.invent[i][j].pot.type == APPRENTISSAGE){
						image = MLV_load_image("Personnage_dongeon/Potion_Orange.png");
					}

					/*fprintf(stderr, "Aie Potion\n");*/


					MLV_draw_image(image, (taille_carre + 4) * (j) + (X / 4) - 20, (taille_carre + 4) * (i) + (Y/ 4) - 20);
					MLV_free_image(image);
					
					/*fprintf(stderr, "Aie Potion2\n");*/
				}
			}

		}	
	
	}


	MLV_draw_rectangle((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) - 40, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30, 50, 15, MLV_COLOR_DEEPPINK4);


	MLV_draw_rectangle((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) + 20, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30, 50, 15, MLV_COLOR_DEEPPINK4);


	MLV_draw_rectangle((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) +  80, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30, 50, 15, MLV_COLOR_DEEPPINK4);

	/*retirer, equiper, jeter*/

	MLV_draw_text((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10), taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 ,"INVENTAIRE", MLV_COLOR_DEEPPINK4);





	MLV_draw_text((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) - 35, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30,"Jeter", MLV_COLOR_DEEPPINK4);

	MLV_draw_text((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) - 38 + 60, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30,"Equip.", MLV_COLOR_DEEPPINK4);

	MLV_draw_text((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) - 38 + 120, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30,"Retir.", MLV_COLOR_DEEPPINK4);



	monstre_restant(nb_monster);
	/*efface très rapidement les stats du perso afin que ne se superposent pas visuellement les anciens et les nouveaux*/
	erase_perso();
	show_perso2(perso);

	MLV_actualise_window();

}

/* fonction qui gère les actions du perso quand il veut voir son inventaire*/
void modifier_inventaire(Perso *perso, Potion tab_potion[MAX_USED_POTION], int monstre_leftover){
	int x_mouse, y_mouse, clic;
	MLV_Keyboard_button touche;
	MLV_Event event_type = MLV_NONE;
	/* variable permettant de savoir où se situe le joueur au niveau des listes*/
	/* i = 0 signifie equipements, i = 1 signifie potions, i = 2 Signifie vêtements portés*/
	/* j désigne la colonne où se situe le user : ça va de 0 à 4*/
	int i,j;
	int bois;
	/* position où est le curseur dans l'inventaire entre 0 et 10 */
	/* 0 est l'emplacement 0 sur la ligne 0*/
	/* 10 est l'emplacement  numero 5, sur la ligne 1*/
	/* 11 est l'emplacement numero 1, sur la ligne 2 */
	int pos;

	pos = 0;

	i = 0;
	j = 0;
	/* on initialise les variables au cas où le user ne cliquerait pas */
	x_mouse = -1;
	y_mouse = -1;
	clic = -1;
	touche = MLV_KEYBOARD_NONE;
	/* on affiche les monsres restants*/
	monstre_restant(monstre_leftover);
	MLV_actualise_window();
	event_type = MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &x_mouse, &y_mouse);
	/* on s'assure que le user a cliqué*/
	if(event_type == MLV_MOUSE_BUTTON){
		clic = clic_invent(x_mouse, y_mouse, 'i');
	}

		while(touche != MLV_KEYBOARD_i){


			/* gestion des déplacement du user dans le menu des équipements*/

			/*déplacements à gauche*/
			if(touche == MLV_KEYBOARD_LEFT){
				/* on s'assure que le user n'est pas en haut à gauche dans le tableau*/
				if(pos > 0){
					/* on arrive au bout de la deuxième ligne par la gauche, on remonte*/
					if(pos == SIZE_INVENTAIRE){
						i = 0;
						/* on ira à la case 4 mais on augmente de 1 ici car on décrémentera juste après*/
						j = SIZE_INVENTAIRE;
					}

					/* on arrive au bout de la troième ligne par la gauche, on remonte*/
					if(pos == SIZE_INVENTAIRE*2){
						i = 1;
						/* on ira à la case 4 mais on augmente de 1 ici car on décrémentera juste après*/
						j = SIZE_INVENTAIRE;
					}
					pos--;
					/* on décrémente ici*/
					j--;
				}

			}

			/*déplacements à droite*/
			else if(touche == MLV_KEYBOARD_RIGHT){
				
					/* on arrive au bout de la première ligne par la droite, on descend*/
					if(pos == SIZE_INVENTAIRE-1){
						i = 1;
						/* on ira à la case 0 mais on décrémente de 1 ici car on incrémentera de 1 juste après*/
						j = -1;
					}

					/* on arrive au bout de la deuxième ligne par la droite, on remonte*/
					else if(pos == (SIZE_INVENTAIRE*2) -1){
						/* on retourne à la case 0 mais l'incrémentation pour arriver à 0 se fera juste après donc on fait -1*/
						i = 2;
						j = -1;
					}
					/* on arrive au bout de la troisième ligne par la droite, on remonte*/
					else if(pos >= (SIZE_INVENTAIRE*3) -1){
						/* on retourne à la case 0 mais l'incrémentation pour arriver à 0 se fera juste après donc on fait -1*/
						pos = -1;
						i = 0;
					}
					/* on avance de 1*/
					pos++;
					/* on incrémente de 1 ici*/
					j++;

			}

			/* pour les potions (début)*/
			/* on monte*/
			else if(touche == MLV_KEYBOARD_UP && i == 1){
				i = 0;
				pos-=SIZE_INVENTAIRE;

			}

			/* on descend*/
			else if(touche == MLV_KEYBOARD_DOWN && i == 1){
				i = 2;
				pos+=SIZE_INVENTAIRE;

			}
			/* pour les potions (fin)*/

			/*pour les équipements portés (début) */
			else if(touche == MLV_KEYBOARD_UP && i == 2){
				i = 1;
				pos-=SIZE_INVENTAIRE;

			}

			/*pour les équipements portés (fin) */

			/*pour les équipements (début)*/
			/* on monte*/
			else if(touche == MLV_KEYBOARD_DOWN && i == 0){
				i = 1;
				pos +=SIZE_INVENTAIRE;
			}


			/*pour les équipements (fin)*/

			/* cas où le joueur veut utiliser un objet*/
			else if(touche == MLV_KEYBOARD_q || clic == 7){
				/* cas equipement*/
				if(i == 0)
					equipe_equipement(perso, i, j , tab_potion);
				/* cas potion*/
				if(i == 1){
					bois = bois_potion(perso,i,j, tab_potion);
					if(bois == TRUE)
						show_perso2(*perso);
				}
					
			}

			/* cas où le joueur veut jeter un objet*/
			else if(touche == MLV_KEYBOARD_a || clic == 6){
				/* cas equipement*/
				if(i == 0)
					jeter_equipement(perso, i, j);
				/* cas potion*/
				if(i == 1){
					jeter_potion(perso,i,j);
				}
					
			}

			/* cas où le joueur veut retirer un équipement pour le mettre dans l'inventaire*/
			else if(touche == MLV_KEYBOARD_d || clic == 8){
				/* cas equipement*/
				if(i == 2 && j < 3){
					ranger_equipement(perso, i, j);
					mise_a_jour_stuff(perso, tab_potion);
				}
				
					
			}
			monstre_restant(monstre_leftover);
			show_inventaire(*perso, pos, monstre_leftover);
			
			
			touche = MLV_KEYBOARD_NONE;
			event_type = MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &x_mouse, &y_mouse);
			/* on s'assure que le joueur a cliqué à la souris*/
			if(event_type == MLV_MOUSE_BUTTON){
				clic = clic_invent(x_mouse, y_mouse, 'i');
			}

			/*show_game(LONGUEUR, LARGEUR, chemin, *perso);*/
		}
}

/* gère les cliques dans l'inventaire*/
int clic_invent(int x, int y, char mode){


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



	if(mode == 'i'){

		if(is_in_square_inv(x, y, 10, 10 + 35 , Y - 105, (Y - 105) + 30) == TRUE){
			printf("\n\nINVENTAIRE\n");
			return 4;
		}

		if(is_in_square_inv(x, y, 10, 10 + 35 , Y - 160, (Y - 160) + 30) == TRUE){
			printf("\n\nINVENTAIRE\n");
			return 5;
		}

		if(is_in_square_inv(x, y, x_bouton_inventaire, x_bouton_inventaire + 50 , y_bouton_inventaire, y_bouton_inventaire + 15) == TRUE){
			printf("\n\nJETER\n\n");
			return 6;
		}

		if(is_in_square_inv(x, y, x_bouton_inventaire + 60, x_bouton_inventaire + 60 + 50 , y_bouton_inventaire, y_bouton_inventaire + 15) == TRUE){
			printf("\n\nEQUIPER\n\n");
			return 7;
		}


		if(is_in_square_inv(x, y, x_bouton_inventaire + 120, x_bouton_inventaire + 120 + 50 , y_bouton_inventaire, y_bouton_inventaire + 15) == TRUE){
			printf("\n\nRETIRER\n\n");
			return 8;
		}
	}

	if(mode == 't'){

		if(is_in_square_inv(x, y, x_bouton_inventaire - 50, x_bouton_inventaire - 50 + 60 +  40, y_bouton_inventaire, y_bouton_inventaire + 15) == TRUE){
			printf("\n\nEQUIPER\n\n");
			return 9;
		}


		if(is_in_square_inv(x, y, x_bouton_inventaire + 110, x_bouton_inventaire - 50 + 60 +  200, y_bouton_inventaire, y_bouton_inventaire + 15) == TRUE){
			printf("\n\nRETIRER\n\n");
			return 10;
		}
	}

	




	



	/*printf("\n\nUNDEFINED\n\n");*/

	return -1;
}

/*affiche les infos du personnage dans l'inventaire (barre de vie, de mp)*/
void show_perso2(Perso hero){
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

	MLV_actualise_window();
}

/*Renvoie vrai si le clic se trouve dans le carré de l'inventaire*/
int is_in_square_inv(int clic_x, int clic_y, int x_0, int x_n, int y_0, int y_n){

	if(clic_x > x_0 && clic_x < x_n && clic_y > y_0 && clic_y < y_n){
		return TRUE;
	}

	return FALSE;
}