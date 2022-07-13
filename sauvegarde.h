#ifndef __SAUVEGARDE__
#define __SAUVEGARDE__


	#include "terrain.h"
	#include "tresor.h"
	#include "perso.h"
	#include "monstre.h"
	
	/* enregistre les données chemin accessible au joueur et les caractéristiques des éléments présents le long de ce chemin*/
	int save_chemin(Terrain chemin, FILE * file);
	/* enregistre les données chemin du dernier monstre trouvé*/
	int save_monster_found(Coord monster_found[MAX_MONSTER], FILE * file);
	/* enregistre les données du donjon*/
	int save_dongeon(Donjon dongeon, FILE * file);
	/* enregistre les données du personnage dans le fichier que le user aura ouvert au préalable*/
	int save_perso(Perso hero , FILE * file);

	/* enregistre les données de l'étage dans lequel se situe le perso*/
	int save_etage(int etage, FILE * file);

	/* permet d'enregistrer une entité de type */
	int save_entity(Entity ent, Celltype type , FILE * file);
	/* permet d'enregistrer une entité de type potion*/

	/* enregistre les données des potion,qui sont en train d'être consommée*/
	int save_consommee(Potion tab_potion[MAX_USED_POTION], FILE* file);


	/* fonction qui gère la sauvegarde de l'état du jeu*/
	int save(Terrain chemin, Donjon dongeon, Coord monster_found[MAX_MONSTER], Perso hero, Potion tab_potion[MAX_USED_POTION]);

	/* fonction qui permet de donner au personnage les infos qui ont été sauvegardées sur lui*/
	int load_perso(Perso *hero, FILE *file);
	int load_monstre(Coord monster_found[MAX_MONSTER], FILE *file);
	/* fonction qui permet de charger les infos sur le donjon*/
	int load_dongeon(Donjon * dongeon, FILE *file);

	/* fonction qui permet de charger les infos sur le chemin parcourut par le joueur */
	int load_chemin(Terrain * chemin, FILE *file);

	int load_etage(int *etage, FILE *file);


	/* charge les données des potions,qui ont été consommée*/
	int load_consommee(Potion tab_potion[MAX_USED_POTION], FILE* file);

	/* charge les données qui indiquent le nombre d'étage du jeu*/
	int load_etage_nb(int nb_etage, FILE* file);
	/* fonction qui gère l'ajout des données de données de sauvegarde dans les différentes variables du jeu*/
	int load(Terrain * chemin, Donjon * dongeon, Coord * monster_found, Perso * hero, Potion tab_potion[MAX_USED_POTION]);

	



#endif