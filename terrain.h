#ifndef __TERRAIN__
#define __TERRAIN__

	#include "tresor.h"
	#include "perso.h"
	#include "monstre.h"
	#include "string.h"

	#define LONGUEUR 63
	#define LARGEUR 43

	#define RANDOM_TREASURE_MAX 5
	#define TAILLE_DONGEON_MAX 10
	#define FACTEUR_EXP 200
	

	


	typedef struct Tuple Tuple;
	
	struct Tuple{
    	int i;
    	int j;
    	Tuple * suivant;
	};

	
	typedef struct TuplesList TuplesList;

	struct TuplesList{    
    	int size;
    	Tuple *premier;
	};

	


	/*Représente le type d'une case*/
	typedef enum celltype {WALL,
		TREASURE, 
		MONSTER, 
	 	ROOM, 
	 	STAIR_UP , 
	 	STAIR_DOWN

	} Celltype;


	/*Représente une entité*/
	/* Deux entités de taille inégales*/
	typedef union entity{
		Monster monster;
		Treasure treasure[NB_TRESOR];
	}Entity;


	/*Représente une case du terrain*/
	typedef struct{
		Celltype type;
		Entity entity;

	}Cell;


	/*Liste de cases*/
	typedef struct list{
		Cell val;
		struct list *suivant;
	} Cell_in_list, *CellList;


	/*Structure représentant le terrain*/
	typedef struct field{

		Cell terrain[LONGUEUR][LARGEUR];
		int nb_monster;
		int x_esc_mont;
		int y_esc_mont;

	} Terrain;


	typedef struct dongeon {
		int size;
		Terrain * etages;
		int etage_courant;		
	}Donjon;


	void initialise_dongeon(Donjon * dongeon, int dim_x, int dim_y, int dongeon_size, Terrain * chemin);
	void generate_terrain_al(Terrain * chemin, int dim_x, int dim_y, int etage);
	
	/* fonction qui gère la montée du joueur d'un étage */
	int floor_up(Donjon * dongeon, Terrain * chemin, Perso  * hero, int lim_x, int lim_y);
	/* fonction qui gère la descente du joueur d'un étage */
	int floor_down(Donjon * dongeon, Terrain * chemin, Perso  * hero, int lim_x, int lim_y);
	
	int test_fight(Perso hero, Terrain * chemin, Coord monster_coords[4]);

	/* vérifie si un tresor a été trouvé être lancé*/
	/* renvoie 1 si un trésor peut être récupéré*/
	/* renvoie 0 si aucun trésor ne peut être récupéré*/
	/* enregistre les coordonnées du trésor dans tresor_coords*/
	int test_treasure(Perso hero, Terrain * chemin, Coord * tresor_coords);
	/* fonction qui associe à chaque monstre l'expérience qu'il donne après sa mort*/
	/* les monstres d'un étage rapporte tous le même nombre d'exp*/
	/* la somme de leur exp fait augmenter deux niveaux au joueur selon l'étage */
	/* tuer tous les monstres de l'étage 1 une fois permet d'atteindre le niveau 3, pour l'étage 2 le niveau 5, etc...*/
	void experience_monstre(Terrain * chemin, int dim_x, int dim_y, int etage);


	/* copie le contenue de send dans dest*/
	void copie_Cell(Cell * dest, Cell * send);
	/* copie le contenue de send dans dest*/
	void copie_terrain(Terrain * dest, Terrain * send);

	/* vérifie si un combat doit être lancé*/
	/* renvoie 1 si un combat doit être lancé*/
	/* renvoie 0 si aucun combat ne doit être lancé*/
	/* trouve le monstre ciblé par le joueur et enregistre ses coordonnées dans i et j*/
	int find_one_monster(Perso hero, Terrain * chemin, Coord * monster_coords);

	/* fonction de test, vérifie qu'il existe bien un escalier montant*/
	void down_exists(Terrain chemin);

	/* fonction qui permet de libérer chaque étages du dongeon ayant été utilisé donc le dongeon lui-même*/
	void free_dongeon(Donjon * dongeon);
	
	/* fonction qui libère une tupleliste*/
	void free_tupleList(TuplesList * list);
	
	
	

#endif
