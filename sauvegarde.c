#include "../inc/sauvegarde.h"

/* enregistre les données du personnage dans le fichier que le user aura ouvert au préalable (valide)*/
int save_perso(Perso hero, FILE * file){
	if(file == NULL)
		return 0;
	fwrite(&hero, sizeof(Perso),1, file);
	return 1;
}

/* enregistre les données de l'étage dans lequel se situe le perso*/
int save_etage(int etage, FILE * file){
	if(file == NULL)
		return 0;
	fwrite(&etage, sizeof(int),1, file);
	return 1;

}
/*
Cell terrain[LONGUEUR][LARGEUR];
	int nb_monster;
	int x_esc_mont;
int y_esc_mont;*/
/* enregistre les données chemin accessible au joueur et les caractéristiques des éléments présents le long de ce chemin*/
int save_chemin(Terrain chemin, FILE * file){
	/*int i,j;*/
	/*int nb_monster;
	int x_esc_mont;
	int y_esc_mont;*/
	if(file == NULL)
		return 0;
	/*nb_monster = chemin.nb_monster;
	x_esc_mont = chemin.x_esc_mont ;
	y_esc_mont = chemin.y_esc_mont ;*/

	/*fwrite(&nb_monster, sizeof(int),1, file);
	fwrite(&x_esc_mont, sizeof(int),1, file);
	fwrite(&y_esc_mont, sizeof(int),1, file);
	for(i =0 ; i < LONGUEUR ;i++){
		for(j=0 ; j < LARGEUR ;j++){
			fwrite(&chemin.terrain[i][j], sizeof(Cell),1, file);
		}
	}*/
	fwrite(&chemin, sizeof(Cell),1, file);
	return 1;
}

/* enregistre les données chemin du dernier monstre trouvé (valide)*/
int save_monster_found(Coord monster_found[MAX_MONSTER], FILE * file){
	if(file == NULL)
		return 0;

	fwrite(monster_found, sizeof(Coord),MAX_MONSTER, file);
	return 1;
}

/* enregistre les données du donjon*/
int save_dongeon(Donjon dongeon, FILE* file){
	int size;
	int etage_courant;
	if(file == NULL){
		printf("Echec chargement sauvegarde \n");
		return 0;
	}
	size = dongeon.size;
	etage_courant = dongeon.etage_courant;
	fwrite(&size, sizeof(int),1, file);
	fwrite(&etage_courant, sizeof(int),1, file);
	fwrite(dongeon.etages, sizeof(Terrain), size, file);
	return 1;
	
}

/* enregistre les données des potion,qui sont en train d'être consommée*/
int save_consommee(Potion tab_potion[MAX_USED_POTION], FILE* file){
	if(file == NULL)
		return 0;
	fwrite(tab_potion, sizeof(Potion),MAX_USED_POTION, file);
	return 1;
	
}


/* fonction qui gère la sauvegarde de l'état du jeu*/
int save(Terrain chemin, Donjon dongeon, Coord monster_found[MAX_MONSTER], Perso hero, Potion tab_potion[MAX_USED_POTION]){
	FILE* save = NULL;
	save = fopen("sauvegarde.txt", "wb");
	/* échec lors de l'ouverture du fichier*/
	if(save == NULL)
	{
		printf("Erreur lors de la création du fichier de sauvegarde ! \n");
		return 0;
	} 
	save_consommee(tab_potion, save);
	save_chemin(chemin, save);
	save_dongeon(dongeon, save);
	save_monster_found(monster_found, save);
	save_perso(hero, save);

	fclose(save);

	printf("Sauvegarde réussie ! \n");

	return 1;
	
}

int load_etage(int *etage, FILE *file){
	if(file == NULL){
		printf("Echec chargement sauvegarde \n");
		return 0;
	}
	fread(etage, sizeof(int),1 ,file);
	return 1;
}

/* fonction qui permet de donner au personnage les infos qui ont été sauvegardées sur lui*/
int load_perso(Perso *hero, FILE *file){
	if(file == NULL){
		printf("Echec chargement sauvegarde \n");
		return 0;
	}
	fread(hero, sizeof(Perso),1 ,file);
	return 1;
}

/* fonction qui permet de donner au dernier monstre trouvé les infos sur lui*/
int load_monstre(Coord monster_found[MAX_MONSTER], FILE *file){
	if(file == NULL){
		printf("Echec chargement sauvegarde \n");
		return 0;
	}
	fread(monster_found, sizeof(Coord), MAX_MONSTER ,file);
	return 1;
}

/* fonction qui permet de charger les infos sur le donjon*/

int load_dongeon(Donjon * dongeon, FILE *file){
	/*int nb_etages;
	int etage_courant;*/

	if(file == NULL){
		printf("Echec chargement sauvegarde \n");
		return 0;
	}
	/* on récupère le nombre d'étage présent dans la partie*/
	fread(&(dongeon->size), sizeof(int),1, file);
	/* on récupère l'étage courant dans la partie*/
	fread(&(dongeon->etage_courant), sizeof(int),1, file);
	dongeon->etages = (Terrain*) malloc(sizeof(Terrain) * dongeon->size);
	/* on récupère les infos sur les étages*/
	fread(dongeon->etages, sizeof(Terrain), dongeon->size, file);
	return 1;
}

/* fonction qui permet de charger les infos sur le chemin parcourut par le joueur */
int load_chemin(Terrain * chemin, FILE *file){
	if(file == NULL){
		printf("Echec chargement sauvegarde \n");
		return 0;
	}
	fread(chemin, sizeof(Terrain),1 ,file);
	return 1;
}

/* charge les données des potions,qui ont été consommée*/
int load_consommee(Potion tab_potion[MAX_USED_POTION], FILE* file){
	if(file == NULL)
		return 0;
	fread(tab_potion, sizeof(Potion),MAX_USED_POTION, file);
	return 1;
	
}

/* fonction qui gère l'ajout des données de données de sauvegarde dans les différentes variables du jeu*/
int load(Terrain * chemin, Donjon * dongeon, Coord * monster_found, Perso * hero, Potion tab_potion[MAX_USED_POTION]){ 
	FILE* save = NULL;
	save = fopen("sauvegarde.txt", "rb");
	if(save == NULL){
		printf("Echec du chargement des données ! \n");
		return 0;
	}
	load_consommee(tab_potion, save);
	load_chemin(chemin, save);
	load_dongeon(dongeon, save);
	load_monstre(monster_found, save);
	load_perso(hero, save);

	fclose(save);
	printf("Chargement des données réussie ! \n");
	return 1;
}