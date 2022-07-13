#ifndef __MUSIQUE__
#define __MUSIQUE__

#include <MLV/MLV_all.h>

#define NB_MUSIC 5
#define NB_SOUND 5

/* initialise le tableau des sons à null*/
void init_tab_sound(MLV_Sound *tab[NB_SOUND]);
/* initialise le tableau des musiques à null*/
void init_tab_music(MLV_Music *tab[NB_MUSIC]);
/*lance le son lié à la découverte d'un coffre*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void treasure_sound(int off,  MLV_Sound * tab_sound[NB_SOUND]);

/* lance le bruit de pas lié aux mouvements du héros*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void walk_sound(int off,  MLV_Sound * tab_sound[NB_SOUND]);
/* lance le son lié à l'apparition d'un monstre*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void monster_sound(int off,  MLV_Sound * tab_sound[NB_SOUND]);

/* lance le son lors d'une attaque*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void fight_sound(int off,  MLV_Sound * tab_sound[NB_SOUND]);

/* lance la musique de combat*/
/* si la variable vaut true (0) on coupe le son sinon on laisse*/
void fight_music(int off, MLV_Music * tab_music[NB_MUSIC], MLV_Sound * tab_sound[NB_SOUND]);

/* coupe la musique*/
void music_off();
/* coupe la musique*/
void sound_off();


/* lance toutes les musiques*/
void launch_musics();
/* lance tous les sons*/
void launch_sounds();

/* charge tous les sons*/
void load_sound(MLV_Sound * tab_sound[NB_SOUND]);
/* charge toutes les musiques*/
void load_music(MLV_Music * tab_music[NB_MUSIC]);

/* libère le tableau des musiques*/
void free_all_music(MLV_Music *tab[NB_MUSIC]);

/* libère le tableau des sons*/
void free_all_sound(MLV_Sound *tab[NB_SOUND]);



/* arrête les musiques*/
void stop_music();

/* arrête les sons*/
void stop_sound();

#endif