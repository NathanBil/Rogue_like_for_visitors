#ifndef __COORDONNEES__
#define __COORDONNEES__


typedef struct Coordonnees {
		int x;
		int y;
} Coord;


/* modifie les coordonnées en affectant les valeurs de x1 et y1*/
void enregistrer_coord(Coord * coord, int x1, int y1);
#endif