#ifndef __PERSO__
#define __PERSO__
	#include "tresor.h"
	#include "equipement.h"
	#include "potion.h"
	#include "coordonnees.h"
	#include "monstre.h"
	#include "boolean.h"
	#include "string.h"
	#include <ctype.h>	/* points accordés au user lorsqu'il monte en niveau */
	#define POINT_LEVEL_UP 3
	#define SIZE_INVENTAIRE 6
	#define NB_INVENTAIRE 3
	#define MAX_USED_POTION 5
	#define NB_VETEMENTS 3
	


	typedef enum direction{
		NORD,
		OUEST,
		EST, 
		SUD
	}Direction;

	
	typedef struct stats{
		int monster_killed; 
		int treasures_opened;
	}Stats;

	typedef struct perso {
		int hp;
		int mp;
		int atk;
		int inte;
		int def;
		int exp;
		int lv;
		/* variable qui gère le pourcentage de chance du héros de faire une attaque critique*/
		/* cela peut-être modfié par une potion de precision*/
		int boost;
		int boost_exp;
		int bonus_mp;
		int bonus_hp;
		Equipement armure;
		Equipement baguette;
		Equipement arme;
		Coord coord;
		Direction direction;
		Stats stats;
		/* correspond à l'inventaire du personnage*/
		/* l'inventaire est composé de deux parties : une pour les potions, l'autre pour les équipements*/
		union Item invent[NB_INVENTAIRE][SIZE_INVENTAIRE];
	
	} Perso ;

	/* initalise le personnage lors de la première partie avec son niveau, ses pv etc...*/
	Perso initialise_pt_perso(void);
	/* met à jour les pts du personnage en fonction de son niveau*/
	void update_perso(Perso *p1);

	/* fonction qui donne le nombre de hp maximum du personnage en fonction de ses stats de défense*/
	int max_hp(Perso p1);
	/* fonction qui donne le nombre de Mp maximum du personnage en fonction de ses stats de défense*/
	int max_mp(Perso p1);
	/*  vérifie si le personnage doit augmenter en niveau  */
	int level_up(Perso *p1);

	int is_character_dead(Perso character);

	/* initialise l'inventaire du héros en le rendant vide et lui donne aussi ses premiers équipements*/
	/* l'argument est le personnage qui reçoit les équipements et l'inventaire vide*/
	void initialise_inventaire_equipement(Perso * p1);

	/* initialise l'inventaire du héros en le rendant vide et lui donne aussi ses premiers équipements*/
	/* l'argument est le personnage qui reçoit les équipements et l'inventaire vide*/
	void initialise_inventaire_potion(Perso * p1);

	/* vérifie si le tab_potion est vide*/
	/* renvoie true si oui (0) et false sinon (1)*/
	int empty_tab(Potion tab_potion[MAX_USED_POTION]);

	/* met à jour les objets portés par le joueur*/
	void mise_a_jour_stuff(Perso *p1, Potion tab_potion[MAX_USED_POTION]);

	/* initialise les équipements que porte le héros*/
	/* l'argument est le personnage qui met ses équipements*/
	void initalise_objet_portee(Perso * p1);

	/* initialise les équipements que porte le héros*/
	/* l'argument est le personnage qui met ses équipements*/
	void initalise_objet_porte(Perso * p1);

	void initialise_perso(Perso * perso, int x, int y);

	/* cette fonction dit si oui ou non un emplacement vide a été trouvé dans l'inventaire des armures*/
	/* elle remplit les variables x et y avec les coordonnées de cet emplacement*/
	/* elle renvoie true si un emplacement a été trouvé*/
	/* elle renvoie false si non*/
	int find_empty_place_1(Perso p1, int *x, int *y);

	/* cette fonction dit si oui ou non un emplacement vide a été trouvé dans l'inventaire des potions*/
	/* elle remplit les variables x et y avec les coordonnées de cet emplacement*/
	/* elle renvoie true si un emplacement a été trouvé*/
	/* elle renvoie false si non*/
	int find_empty_place_2(Perso p1, int *x, int *y);

	void deplacement_perso(Perso * perso, Direction direction, int limit_x, int limit_y);

	int monster_atk_perso(Perso * perso, Monster monster, int *degats);

	/* indique si le monstre a fait un coup critique ou non*/
	/* si elle renvoie true cela signifie que le coup est critique*/
	/* boost correpsond à un pourcentage de chance de faire une attaque critique de 15%
	il est lié à un boost permis par une potion*/
	int critique_hero(Perso hero);
	
	/* fonction qui calcule la puissance de l'attaque normale du joueur*/
	/* elle renvoie la valeur de l'attaque du joueur*/
	int perso_atk_melee(Perso hero);
	/* fonction qui gère la perte de vie du monstre en fonction de la puissance d'attaque du joueur*/
	/* elle renvoie true or false selon si l'attaque est autorisée, pour ce type d'attaque c'est toujours autorisé*/
	int perso_atk_melee_monster(Perso * hero, Monster * monster, int * degats);

	/* fonction qui calcule la puissance de l'attaque magique du joueur*/
	/* elle renvoie la valeur de l'attaque magique du joueur*/
	int perso_atk_magique(Perso hero);
	/* fonction qui gère la perte de vie du monstre en fonction de la puissance d'attaque magique du joueur*/
	/* elle renvoie true or false selon si l'attaque est autorisée, c'est à dire si le joueur a assez suffisamment d'mp ou non*/
	int perso_atk_magique_monster(Perso *hero, Monster * monster, int * degats);

	/* renvoie le pourcentage d'exp du joueur par rapport au pourcentage d'exp nécessaire pour augmenter un niveau*/
	int pourcentage_xp(Perso p1);

	/* fonction qui gère l'ajout d'un équipement dans l'inventaire*/
	void add_equipement_invent(Perso * hero, Equipement eq1,int x, int y);
	/* fonction qui gère l'ajout d'une potion dans l'inventaire*/
	void add_potion_invent(Perso * hero, Potion pot1,int x, int y);

	/* retire l'objet associé aux cases x et y de l'inventaire des équipements*/
	void retire_equipement_invent(Perso *hero, int y);

	/* retire l'objet associé aux cases x et y de l'inventaire des potions*/
	void retire_potion_invent(Perso *hero, int y);

	/* cette fonction affiche l'ensemble des éléments de l'inventaire des équipements*/
	void show_inventaire_equipement(Perso p1);

	/* cette fonction affiche l'ensemble des éléments de l'inventaire des potions*/
	void show_inventaire_potion(Perso p1);
	

	/* fonction qui gère l'échange entre un équipement que le héros portait et le nouvel équipement qu'il veut maintenant porter*/
	void changer_equipement(Perso *hero, int i, int j);


	/* fonction qui gère l'activation d'une potion*/
	/* elle renvoie la potion avec son nouvel état*/
	void active_potion(Perso * hero,Potion *pot);

	/* fonction qui gère l'activation des potions du tableau des potions*/
	void active_tab_potion(Perso * hero, Potion tab_potion[MAX_USED_POTION]);

	/* fonction qui gère l'activation de la dernière potion bu par le héros sans attendre un tour*/
	void active_last_potion(Perso * hero, Potion tab_potion[MAX_USED_POTION]);

	/* vérifie si un type de potion est déjà utilisé par le joueur*/
	/* true (1)si la potion est déjà utilisée, false sinon*/
	int already_used(Potion pot, Potion tab_potion[MAX_USED_POTION]);

	/* fonction qui gère le fait que le héros choisit une potion qu'il veut boire et l'ajoute dans la liste des potions à boire*/
	int bois_potion(Perso * hero, int i, int j, Potion tab_potion[MAX_USED_POTION]);

	/* fonction qui gère le fait que le héros s'équipe d'un objet*/
	void equipe_equipement(Perso *hero, int i, int j, Potion tab_potion[MAX_USED_POTION]);

	
	/* Trouve le premier emplacement vide du tableau de potion*/
	int empty_place(Potion tab_potion[MAX_USED_POTION]);

	/* tableau qui initialise les potions que le joueur peut boire en même temps*/
	void initialise_tab_potion(Potion tab_potion[MAX_USED_POTION]);

	/* jette la potion choisie par le user*/
	void jeter_potion(Perso * perso, int i, int j);

	/* jette la potion choisie par le user*/
	void jeter_equipement(Perso * perso, int i, int j);

	/* fonction qui gère l'action de ranger une arme dans l'inventaire*/
	void ranger_equipement(Perso * perso, int i, int j);

	/* renvoie le total des hps du joueur en prenant en compte les équipements*/
	int total_hp(Perso hero);

	/* compare les armes du joueur selon leurs attaques et lui fait porter la meilleure*/
	/* elle renvoie 0 si il faut changer et 1 sinon*/
	/* les coordonnées de la nouvelle meilleure armes sont dans i et j*/
	int compare_arme(int *i, int *j, Perso hero);

	/* compare les armes du joueur selon leurs intelligence et lui fait porter la meilleure*/
	/* elle renvoie 0 si il faut changer et 1 sinon*/
	/* les coordonnées de la nouvelle meilleure armes sont dans i et j*/
	int compare_baguette(int *i, int *j, Perso hero);

	/* compare les armes du joueur selon leurs défenses et lui fait porter la meilleure*/
	/* elle renvoie 0 si il faut changer et 1 sinon*/
	/* les coordonnées de la nouvelle meilleure armes sont dans i et j*/
	int compare_armure(int *i, int *j, Perso hero);
	/* donne au joueur les meilleurs équipements qu'il peut avoir*/
	void meilleur_equipement(Perso *hero);
	

#endif