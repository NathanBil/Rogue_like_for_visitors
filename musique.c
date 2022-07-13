#include "../inc/musique.h"

/* initialise le tableau des sons*/
void init_tab_sound(MLV_Sound *tab[NB_SOUND]){
	int i;
	for(i =0 ; i< NB_SOUND ; i++){
		tab[i] = NULL;
	}
}
/* initialise le tableau des musiques*/
void init_tab_music(MLV_Music *tab[NB_MUSIC]){
	int i;
	for(i =0 ; i< NB_MUSIC; i++){
		tab[i] = NULL;
	}
}
/*lance le son lié à la découverte d'un coffre*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void treasure_sound(int off , MLV_Sound * tab_sound[NB_SOUND]){
	int i;
	/* enregistre l'emplacmeent associé à l'utilisation de la musique*/
	static int num = 0;
	MLV_Sound *sound;
	/* on arrête la musique*/
	if(off ==0){
			return;
	}
	/* si la musique avait déjà été utilisée on la lance à l'emplacement associé*/
	else if(num != 0){
		printf("musique trouvée ! \n");
		MLV_play_sound(tab_sound[num], 50);
		return;
	}
	sound = MLV_load_sound("Musique/Pieces.ogg");
	/* cas où on lance la musique*/	
	for(i =0; i < NB_SOUND ;i++){
		/* on regarde si la musique était déjà présente*/
		if(tab_sound[i] != NULL && tab_sound[i] == sound){
			printf("musique trouvée ! \n");
			break;
		}
		/* on ajoute la musique si elle n'était pas déjà présente*/
		else if(tab_sound[i] == NULL){
			tab_sound[i] = MLV_load_sound("Musique/Pieces.ogg");
			num = i;
			MLV_free_sound(sound);
			break;
			
			
		}
	}
	/* on joue le son*/
	MLV_play_sound(tab_sound[i], 50);
}

/* lance le bruit de pas lié aux mouvements du héros*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void walk_sound(int off , MLV_Sound * tab_sound[NB_SOUND]){
	int i;
	MLV_Sound *sound;
	/* enregistre l'emplacmeent associé à l'utilisation de la musique*/
	static int num = 0;
	
	/* on arrête la musique*/
	if(off ==0){
			return;
	}
	/* si la musique avait déjà été utilisée on la lance à l'emplacement associé*/
	else if(num != 0){
		printf("musique trouvée ! \n");
		MLV_play_sound(tab_sound[num], 50);
		return;
	}
	sound = MLV_load_sound("Musique/Marche.ogg");
	/* on arrête la musique*/
	if(off ==0){
			return;
	}
	for(i =0; i < NB_SOUND ;i++){
		/* on regarde si la musique était déjà présente*/
		if(tab_sound[i] != NULL && tab_sound[i] == sound)
			break;
		/* on ajoute la musique si elle n'était pas déjà présente*/
		else if(tab_sound[i] == NULL){
			tab_sound[i] = MLV_load_sound("Musique/Marche.ogg");
			MLV_free_sound(sound);
			num = i;
			break;
		}
	}
	/*MLV_free_sound(sound);*/
	/* on joue le son*/
	MLV_play_sound(tab_sound[i], 50);

}

/* lance le son lié à l'apparition d'un monstre*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void monster_sound(int off , MLV_Sound * tab_sound[NB_SOUND]){
	int i;
	MLV_Sound *sound;
	/* enregistre l'emplacmeent associé à l'utilisation de la musique*/
	static int num = 0;
	
	/* on arrête la musique*/
	if(off ==0){
			return;
	}
	/* si la musique avait déjà été utilisée on la lance à l'emplacement associé*/
	else if(num != 0){
		printf("musique trouvée ! \n");
		MLV_play_sound(tab_sound[num], 50);
		return;
	}
	sound = MLV_load_sound("Musique/Monstre.ogg");
	for(i =0; i < NB_SOUND ;i++){
		/* on regarde si la musique était déjà présente*/
		if(tab_sound[i] != NULL && tab_sound[i] == sound)
			break;
		/* on ajoute la musique si elle n'était pas déjà présente*/
		else if(tab_sound[i] == NULL){
			tab_sound[i] = MLV_load_sound("Musique/Monstre.ogg");
			MLV_free_sound(sound);
			num = i;
			break;
		}
	}
	/*MLV_free_sound(sound);*/
	/* on joue le son*/
	MLV_play_sound(tab_sound[i], 50);

}

/* lance le son lors d'une attaque*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void fight_sound(int off, MLV_Sound * tab_sound[NB_SOUND]){
	int i;
	MLV_Sound *sound;
	/* enregistre l'emplacmeent associé à l'utilisation de la musique*/
	static int num = 0;
	
	/* on arrête la musique*/
	if(off ==0){
			return;
	}
	/* si la musique avait déjà été utilisée on la lance à l'emplacement associé*/
	else if(num != 0){
		printf("musique trouvée ! \n");
		MLV_play_sound(tab_sound[num], 50);
		return;
	}
	sound = MLV_load_sound("Musique/Sword_fight.ogg");
	for(i =0; i < NB_SOUND ;i++){
		/* on regarde si la musique était déjà présente*/
		if(tab_sound[i] != NULL && tab_sound[i] == sound)
			break;
		/* on ajoute la musique si elle n'était pas déjà présente*/
		else if(tab_sound[i] == NULL){
			tab_sound[i] = MLV_load_sound("Musique/Sword_fight.ogg");
			MLV_free_sound(sound);
			num = i;
			break;
		}
	}
	/*MLV_free_sound(sound);*/
	/* on joue le son*/
	MLV_play_sound(tab_sound[i], 50);

}

/* lance la musique de combat*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void fight_music(int off, MLV_Music * tab_music[NB_MUSIC], MLV_Sound * tab_sound[NB_SOUND]){
	int i;
	MLV_Sound *sound;
	MLV_Music *music;
	/* enregistre l'emplacmeent associé à l'utilisation de la musique*/
	static int num = 0;
	static int num2 = 0;
	/* on arrête la musique*/
	if(off ==0){
			return;
	}
	/* si la musique avait déjà été utilisée on la lance à l'emplacement associé*/
	else if(num != 0){
		printf("musique trouvée !\n");
		MLV_play_sound(tab_sound[num], 50);
		MLV_play_music(tab_music[num2], 5, -1);
		return;
	}
	sound = MLV_load_sound("Musique/Sword_fight.ogg");
	for(i =0; i < NB_MUSIC ;i++){
		/* on regarde si la musique était déjà présente*/
		if(tab_sound[i] != NULL && tab_sound[i] == sound)
			break;
		/* on ajoute la musique si elle n'était pas déjà présente*/
		else if(tab_sound[i] == NULL){
			tab_sound[i] = MLV_load_sound("Musique/Sword_fight.ogg");
			MLV_free_sound(sound);
			num = i;
			break;
		}
	}
	/* on joue le son*/
	MLV_play_sound(tab_sound[i], 50);
	/*MLV_free_sound(sound);*/
	monster_sound(off, tab_sound);

	music = MLV_load_music("Musique/Heros.mp3");

	for(i =0; i < NB_MUSIC ;i++){
		/* on regarde si la musique était déjà présente*/
		if(tab_music[i] != NULL && tab_music[i] == music)
			break;
		/* on ajoute la musique si elle n'était pas déjà présente*/
		else if(tab_music[i] == NULL){
			tab_music[i] = MLV_load_music("Musique/Heros.mp3");
			MLV_free_music(music);
			num2 = i;
			break;
		}
	}

	/*MLV_free_music(music);*/

	/* on joue la musique */
	MLV_play_music(tab_music[i], 5, -1);
}

/* coupe la musique*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void music_off(){
	MLV_Music *music;
	music = MLV_load_music("Musique/Heros.mp3");
	MLV_free_music(music);
}

/* coupe la musique*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void sound_off(){
	MLV_Sound *sound;


	sound = MLV_load_sound("Musique/Marche.ogg");
	MLV_free_sound(sound);

	sound = MLV_load_sound("Musique/Monstre.ogg");
	MLV_free_sound(sound);


	sound = MLV_load_sound("Musique/Pieces.ogg");
	MLV_free_sound(sound);

	sound = MLV_load_sound("Musique/Sword_fight.ogg");
	MLV_free_sound(sound);
}
/* charge tous les sons*/
void load_sound(MLV_Sound * tab_sound[NB_SOUND]){

}
/* charge toutes les musiques*/
void load_music(MLV_Music * tab_music[NB_MUSIC]){

}

/* lance toutes les musiques*/
void launch_musics() {
	/*fight_music(1);*/

}
/* lance tous les sons*/
void launch_sounds(){
	/*treasure_sound(1);
	walk_sound(1);
	monster_sound(1);*/

}
/* arrête les musiques*/
void stop_music(){
	MLV_stop_music();
}

/* arrête les sons*/
void stop_sound(){
	MLV_stop_all_sounds();
}

/* libère le tableau des musiques*/
void free_all_music(MLV_Music *tab[NB_MUSIC]){
	int i;
	for(i =0 ; i< NB_MUSIC ; i++){
		if(tab[i] != NULL){
			MLV_free_music(tab[i]);
		}
		tab[i] = NULL;
	}

}

/* libère le tableau des sons*/
void free_all_sound(MLV_Sound *tab[NB_SOUND]){
	int i;
	for(i =0 ; i< NB_SOUND ; i++){
		if(tab[i] != NULL){
			MLV_free_sound(tab[i]);
		}
		tab[i] = NULL;
	}
	
}
