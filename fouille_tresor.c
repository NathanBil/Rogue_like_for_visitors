#include "../inc/fouille_tresor.h"


/* affiche la barre indiquant au user qu'il peut fouiller un coffre*/
void barre_fouille(void){
	/* barre pour la fouille */
	MLV_draw_filled_rectangle(10, Y - 20, 90 , 15 , MLV_COLOR_SANDY_BROWN);
	/* affiche texte pour fouiller */
	MLV_draw_text(15, Y - 20, "Fouiller (D)", MLV_COLOR_WHITE);

	MLV_actualise_window();

}

/* fonction qui dit si oui ou non un coffre est vide*/
/* elle renvoie 1 si oui et 0 si non*/
int empty_coffre(Treasure tresor[NB_TRESOR]){
	int i;
	for(i = 0 ; i < NB_TRESOR;i++){
		if(tresor[i].type_tresor != VIDE)
			return 1;
	}
	return 0;

}

/* fonction qui gère l'ajout du trésor à l'inventaire*/
int add_tresor(Perso * hero, Terrain * chemin, int i, Coord tresor_found){
	int empty_place;
	/* variable qui récupèrent les coordonnées de l'emplacement vide pour le trésor de l'inventaire*/
	int x,y;
	Equipement eq1;
	Potion pot1;
	int valide_ajout = 1;

	/* on parcorut le coffre et on regarde si l'emplacement correspond à un équipement ou une potion*/
	if(chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].type_tresor == EQUIPEMENT){
			/* on vérifie s'il y a un emplacement vide*/
			empty_place = find_empty_place_1(*hero, &x, &y);
			/* s'il y a un emplacement vide alors on ajoute l'équipement*/
			if(empty_place == TRUE){
				/* l'ajout est un succès*/
				valide_ajout = 0;
				show_equipement(chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].item.eq);
				eq1 = chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].item.eq;
				add_equipement_invent(hero, eq1,x,y);
				/* on remplace l'emplacement par du vide*/
				chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].type_tresor = VIDE;

			}


		else
			printf("Votre inventaire des équipements est plein, veuillez le vider pour ajouter un objet\n");
	}
	/* si l'objet du coffre est un équipement alors...*/
	else if(chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].type_tresor == POTION){
			/* on vérifie s'il y a un emplacement vide*/
			empty_place = find_empty_place_2(*hero, &x, &y);
			/* s'il y a un emplacement vide alors on ajoute la potion*/
			if(empty_place == TRUE){
				/* l'ajout est un succès*/
				valide_ajout = 0;
				show_potion(chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].item.pot);
				pot1 = chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].item.pot;
				add_potion_invent(hero, pot1,x,y);
				/* on remplace l'emplacement par du vide*/
				chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].type_tresor = VIDE;
			}
			else
				printf("Votre inventaire des potions est plein, veuillez le vider pour ajouter un objet\n");
	}
	/* le joueur a réussit à faire un ajout ou plus*/
	if(valide_ajout == 0)
		return TRUE;
	/* pas d'emplacement vide*/
	return FALSE;
}

/* affiche visuellement le contenu du coffre*/
void show_coffre(Treasure coffre[NB_TRESOR], int curseur){
	int i, j, taille_carre;

	MLV_Image * image;
	MLV_Color color;

	color = MLV_COLOR_DEEPPINK4;

	show_tresor(coffre[curseur]);
	printf(" nous sommes en position : %d \n", curseur);
	taille_carre = ((X / 2) -  10) / SIZE_INVENTAIRE;


	MLV_draw_filled_rectangle( (X / 4), (Y / 4), (taille_carre + 4) * SIZE_INVENTAIRE + 4, taille_carre * (NB_INVENTAIRE  + 2), MLV_COLOR_MAROON);

	

	for(i = 0; i < NB_TRESOR; i++){

			if(i == curseur)
				MLV_draw_filled_rectangle( 90 * i + 200 - 2 , 200 - 2, taille_carre + 4, taille_carre + 4, MLV_COLOR_CYAN);

			MLV_draw_filled_rectangle(90 * i + 200 , 200 , taille_carre, taille_carre, color);

			if(coffre[i].type_tresor == POTION){

				if(coffre[i].item.pot.type == SOIN){
					image = MLV_load_image("Personnage_dongeon/Potion_Green.png");
				}

				if(coffre[i].item.pot.type == MAGIE){
					image = MLV_load_image("Personnage_dongeon/Potion_Blue.png");
				}

				if(coffre[i].item.pot.type== REGENERATION){
					image = MLV_load_image("Personnage_dongeon/Potion_Purple.png");
				}

				if(coffre[i].item.pot.type == PRECISION_POT){
					image = MLV_load_image("Personnage_dongeon/Potion_Yellow.png");
				}

				if(coffre[i].item.pot.type == APPRENTISSAGE){
					image = MLV_load_image("Personnage_dongeon/Potion_Orange.png");
				}

			}

			else if(coffre[i].type_tresor == EQUIPEMENT){

				if(coffre[i].item.eq.type== ARME){
					image = MLV_load_image("Personnage_dongeon/Epee.png");
				}

				if(coffre[i].item.eq.type== ARMURE){
					image = MLV_load_image("Personnage_dongeon/Armure.png");
				}

				if(coffre[i].item.eq.type == BAGUETTE){
					image = MLV_load_image("Personnage_dongeon/Baguette_Magique.png");
				}
			}

			if(coffre[i].type_tresor != VIDE){
				MLV_draw_image(image, 90 * i + 172, 172);
				MLV_free_image(image);
			}
	}

	MLV_draw_rectangle((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) - 90, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30, 100, 15, MLV_COLOR_DEEPPINK4);

	MLV_draw_rectangle((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) +  70, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30, 100, 15, MLV_COLOR_DEEPPINK4);


	MLV_draw_text((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10), taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 ,"TREASURE", MLV_COLOR_DEEPPINK4);

	MLV_draw_text((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) - 75, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30,"Fermer (D)", MLV_COLOR_DEEPPINK4);

	MLV_draw_text((((taille_carre + 4) * SIZE_INVENTAIRE + 4) / 2) + (X / 4) - (4 * 10) - 38 + 120, taille_carre * (NB_INVENTAIRE  + 2) + (Y / 4) - 20 - 30,"Prendre (Q)", MLV_COLOR_DEEPPINK4);


	MLV_actualise_window();
}

/* fonction qui gère la modification d'un coffre au trésor fouillé par le user*/
int modif_tresor(Perso * hero, Terrain * chemin, Coord tresor_found){
	int x_mouse, y_mouse, clic;
	MLV_Keyboard_button touche;
	MLV_Event event_type = MLV_NONE;
	int i;
	int ajout_valide;
	/* variable permettant de savoir où se situe le joueur au niveau des listes*/
	/* i = 0 signifie que le joueur est à l'emplacement 0 de la liste.
	la liste s'étend NB_TRESOR*/
	int pos;

	pos = 0;

	i = 0;
	/* dit si oui ou non le user a réussi à faire un ajout*/
	ajout_valide = FALSE;
	/* on initialise les variables au cas où le user ne cliquerait pas */
	x_mouse = -1;
	y_mouse = -1;
	touche = MLV_KEYBOARD_NONE;
	clic = -1;
	show_coffre(chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure, i);
	MLV_actualise_window();
	event_type = MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &x_mouse, &y_mouse);
	/* on s'assure que le user a cliqué*/
	if(event_type == MLV_MOUSE_BUTTON){
		clic = clic_invent(x_mouse, y_mouse, 't');
	}

		while(touche != MLV_KEYBOARD_d && clic != 9){

			printf(" nous sommes en position : %d \n", i);
			/* gestion des déplacement du user dans le menu des équipements*/

			/*déplacements à gauche*/
			if(touche == MLV_KEYBOARD_LEFT ){
				/* on s'assure que le user n'est pas en bout de ligne sur la gauche*/
				if(pos > 0){
					pos--;
					i--;
					/* on décrémente ici*/
					/*j--;*/
				}
				/*if(chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].type_tresor == VIDE){*/
					/* cas où le user se pose sur une case qui a été vidée, on décale son curseur*/
					/*while(chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].type_tresor == VIDE && i > 0){
						i--;
						pos--;
					}
					
				}*/

			}

			/*déplacements à droite*/
			else if(touche == MLV_KEYBOARD_RIGHT){
				
					/* on arrive au bout de la première ligne par la droite, on revient à gauche */
					if(pos >= NB_TRESOR -1){
					
						/* on retounre à gauche*/
						pos = 0;
						i = 0;
						/* on incrémente de 1 ici*/
						/*j++;*/
					}
					else{
						pos++;
						i++;
					}

					/* cas où le user se pose sur une case qui a été vidée, on décale son curseur vers la droite*/
					/*while(chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure[i].type_tresor == VIDE && i < NB_TRESOR-1){
						i++;
						pos++;
					}*/

			}

		


			/*pour les équipements (fin)*/

			/* cas où le joueur veut prendre un objet*/
			else if(touche == MLV_KEYBOARD_q || clic == 10){
				printf(" après la touche nous sommes en posiiton : %d \n", i);
				if(ajout_valide == FALSE)
					ajout_valide = add_tresor(hero, chemin, i, tresor_found);
				else
					add_tresor(hero, chemin, i, tresor_found);
					
			}

			show_coffre(chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure, i);
			
			
			touche = MLV_KEYBOARD_NONE;
			event_type = MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &x_mouse, &y_mouse);
			/* on s'assure que le joueur a cliqué à la souris*/
			if(event_type == MLV_MOUSE_BUTTON){
				clic = clic_invent(x_mouse, y_mouse, 't');
			}

			/*show_game(LONGUEUR, LARGEUR, chemin, *perso);*/
		}
		return ajout_valide;
}



/* fonction qui réalise la récupération du trésor une fois que le joueur a choisi de fouiller le coffre*/
void fouille(Perso * hero, Terrain * chemin, Coord tresor_found){
	/* cette variable vérifie si l'ajout s'est bien passé*/
	int result_add;
	/* on ajoute le trésor à l'inventaire ssi le user le peut.*/
	result_add = modif_tresor(hero, chemin, tresor_found);
	/* si le personnage a réussit à faire des ajouts, on modifie l'apparence de l'emplacement si le coffre est vide
	et on donne au joueur le meilleur équipement*/
	if(result_add == TRUE){
		meilleur_equipement(hero);

		/* on transforme l'emplacement associé à un coffre en un emplacement ou on peut se déplacer*/
		if(empty_coffre(chemin->terrain[tresor_found.x][tresor_found.y].entity.treasure) == 0){
			hero->stats.treasures_opened++;
			chemin->terrain[tresor_found.x][tresor_found.y].type = ROOM;
			show_game(LONGUEUR, LARGEUR, *chemin, *hero);
		}
	}

}

/* Donne la possibilité au joueur de fouiller un coffre au trésor*/
/* renvoie l'action du joueur*/
int decouverte(Perso * hero, Terrain * chemin, Coord tresor_found, Potion tab_potion[MAX_USED_POTION], int sound_off, MLV_Sound * tab_sound[NB_SOUND]){
	/* variable qui vérifie que le user tente d'ouvrir ou non un trésor*/
	MLV_Keyboard_button open;
	/* affiche au user qu'il peut fouiller un coffre*/
	barre_fouille();

	/*récupère l'action du joueur*/
	open = wait_event(hero, chemin, LONGUEUR, LARGEUR, tab_potion);
	/* on met à jour tout l'affichage du jeu en fonction de l'action du joueur*/
	show_game(LONGUEUR, LARGEUR, *chemin, *hero);
	/* si il n'a pas fait une fouille on sort de la fonction de découverte*/
	if(open != 3){
		return open;
	}
	/* lance la fonction de fouille du coffre */
	treasure_sound(sound_off, tab_sound);
	fouille(hero, chemin, tresor_found);
	return open;
}



