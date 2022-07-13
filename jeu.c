#include "../inc/jeu.h"




/*Fonction représentant le déroulement d'une partie de dongeon*/
void play_dongeon_game(void){

	/*int i;*/
	Terrain chemin;
	Donjon dongeon;
	Coord monster_found[MAX_MONSTER];
	Coord tresor_found;
	Perso hero;
	int end_game, floor_state;
	int floor_state_one;
	int floor_state_two;
	/* indique si on doit arrêter le son 0 = oui, 1 = non*/
	int sound_played_off;
	int music_played_off;
	/* indique si les sons sont déjà activées 0 = oui, 1 = non*/
	int sound_al_off;
	int music_al_off;
	
	/*int i,j;*/
	/* tableau qui contient les potions qui seront utilisées à chaque tour*/
	Potion tab_potion[MAX_USED_POTION];
	
	/* variable qui vérifie si un combat doit continuer ou non*/
	int combat;
	/* si data vaut 1 cela signifie que l'on va charger des données du joueur*/
	/* si data vaut 0 cela signifie qu'on lance une nouvelle partie*/
	int data;
	/* resultat de l'input du joueur*/
	int res;
	int al_test;
	MLV_Music * music;
	/* tableau qui contiennent les musiques à jouer*/
	MLV_Music * tab_music[NB_MUSIC];
	MLV_Sound * tab_sound[NB_SOUND];
	
	data = 0;
	/* indique si les musiques doivent être activées*/
	sound_al_off = 1;
	music_al_off = 1;
	floor_state_two = 0;

	/* indique si on doit activer ou non les musiques dans le main*/
	/* 0 = on coupe le son, 1 signifie on joue le son*/
	sound_played_off = 1;
	music_played_off = 1;
	/*on charge le jeu si le joueur a utilisé des données de sauvegarde*/
	

	/*Initialisation du jeu*/

	memset(tab_potion, 0,(size_t)MAX_USED_POTION* sizeof (POTION));



	end_game = 0;

	srand(time(NULL));
	
	if(MLV_init_audio() == -1){
		printf("AIIE\n");
	}else{
		music = MLV_load_music("Musique/Open.mp3");

	}


	initialise_window();


	/*Affichage avant la première action du joueur*/
	if(menu() == 1){
		vide_tab_monster(monster_found);
		initialise_tab_potion(tab_potion);
		initialise_dongeon(&dongeon, LONGUEUR, LARGEUR, TAILLE_DONGEON_MAX, &chemin);
		initialise_perso(&hero, LONGUEUR / 2, LARGEUR / 2);
		
	}else{
		data = load(&chemin, &dongeon, monster_found, &hero, tab_potion);
		printf("on a chargé les données ! \n");
	}
	/* on charge les sons et les musiques*/
	init_tab_sound(tab_sound);
	init_tab_music(tab_music);

	show_game(LONGUEUR, LARGEUR, chemin, hero);
	

	/* fonction qui permet de trouver les escaliers montant car elle donne leur coordonnées*/
	down_exists(chemin);
	/*Tant que le personnage n'est pas mort*/
	while(is_character_dead(hero) == 1 && !end_game){
		al_test = 0;


		/* on mémorise le nouvel état de l'étage*/
		
		copie_terrain(&(dongeon.etages[dongeon.etage_courant]), &chemin);

		/* si les musiques du jeu sont activées et qu'elles ne l'étaient pas déjà on les lances*/
		if(music_played_off == 1 && music_al_off != 0)	
			MLV_play_music(music, 5, -1);


		/*Verifie si un trésor peut-être récupéré */
		if(test_treasure(hero, &chemin, &tresor_found)){

			res = decouverte(&hero, &chemin, tresor_found, tab_potion, sound_played_off, tab_sound);
			/* vérifie si le joueur a fait une action ce tour-ci via découverte  pour éviter de le demander de faire deux actions*/
			/* 1 signifie oui, 0 non*/
			al_test = 1;
		}

		/*Action du joueur*/
		/* on vérifie que le joueur n'a pas déjà fait une action en cherchant à ouvrir un coffre*/
		if(al_test != 1)
			res = wait_event(&hero, &chemin, LONGUEUR, LARGEUR, tab_potion);
		
		/*Affichage après chaque action du joueur*/
		/*affiche_terrain(LONGUEUR, LARGEUR, chemin, hero);*/

		show_game(LONGUEUR, LARGEUR, chemin, hero);

		/*Vérifie si un combat peut être lancé*/
		if(res == 4){
			/* récupère les coordonées des monstres qui est en face du joueur*/
			test_fight(hero, &chemin, monster_found);
			/* piège le jouer avec une chance sur trois pour qu'il n'ait qu'à affronter qu'un seul monstre*/
			piege_monster(hero, &chemin, monster_found, dongeon.etage_courant);
			/* si le joueur a mis la musique alors on la joue*/
			/* on lance la musique de combat si le joueur a mis les musiques*/
			if(music_played_off != 0)
				fight_music(music_played_off, tab_music, tab_sound);

			/*le combat continue tant que la variable combat est vraie*/
			do{
				combat = fight(&hero, &chemin, monster_found, tab_potion);

			}while(combat == TRUE);
			res = 1;
			show_game(LONGUEUR, LARGEUR, chemin, hero);
			/* dans le cas où le joueur n'aurait pas coupé la musique, on rejoue la musique de la map*/
			if(music_played_off != 0)
				MLV_play_music(music, 5, -1);
		}



		
		floor_state_one = floor_down(&dongeon, &chemin, &hero, LONGUEUR, LARGEUR);
		if(floor_state_one != 1){
			floor_state_two = floor_up(&dongeon, &chemin, &hero, LONGUEUR, LARGEUR);
		}


		

		if(floor_state_two == 2){
   			 end_game = 1;
		}

		if(floor_state_one == 1 || floor_state_two == 1){
			/* on enregistre l'étage où on est */

            /*Affichage_nouveau lvl*/
            MLV_clear_window(MLV_COLOR_BLACK);
            MLV_actualise_window();
            MLV_wait_seconds(2);
            show_game(LONGUEUR, LARGEUR, chemin, hero);
            wait_event(&hero, &chemin, LONGUEUR, LARGEUR, tab_potion);
		}
		/* cas où le joueur a tenté une sauvegarde*/
		if(res == 2){
			save(chemin, dongeon , monster_found, hero, tab_potion);
		}

		/* couper les musiques*/
		if(res == 7 && music_played_off == 1){
			printf("on coupe les musiques \n");
			/* on désactive les musiques*/
			music_played_off = 0;
			music_al_off = 0;
			stop_music();
			music_off();
		}
		/* couper les sons*/
		
		else if(res == 8 && sound_played_off == 1){
			printf("on coupe les sons \n");
			sound_played_off = 0;
			sound_al_off = 0;
			/* on désactive les sons*/
			stop_sound();
			sound_off();
		}

		/* lancer les musiques*/
		else if(res == 7 && music_played_off == 0){
			printf(" on relance les musiques \n");
			music_played_off = 1;
			music_al_off = 1;
			launch_musics();
		}
		/* lancer les sons*/
		
		else if(res == 8 && sound_played_off == 0){
			printf(" on relance les sons \n");
			sound_played_off = 1;
			sound_al_off = 1;
			launch_sounds();
		}

		/* dire que les sons sont déjà activées*/
		if(res != 8 && sound_played_off == 1){
			sound_al_off = 0;
		}
		/* dire que les musiques sont déjà activées*/
		if(res != 7 && music_played_off == 1){
			music_al_off = 0;
		}
		
	}

	


	if(end_game == 1){
		animation_end("YOU WON", hero, dongeon);
	}else{
		animation_end("GAME OVER", hero, dongeon);
	}

	free_dongeon(&dongeon);
	MLV_free_audio();

	free_all_music(tab_music);
	free_all_sound(tab_sound);

	
	

	close_window();


}