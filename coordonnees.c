#include "../inc/coordonnees.h"

/* modifie les coordonnées en affectant les valeurs de x1 et y1*/
void enregistrer_coord(Coord * coord, int x1, int y1){
	(*coord).x = x1;
	(*coord).y = y1;
}