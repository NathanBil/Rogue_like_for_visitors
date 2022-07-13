#include "../inc/clic.h"



/*Renvoie vrai si le clic se trouve dans le carré*/
int is_in_square(int clic_x, int clic_y, int x_0, int x_n, int y_0, int y_n){

	if(clic_x > x_0 && clic_x < x_n && clic_y > y_0 && clic_y < y_n){
		return TRUE;
	}

	return FALSE;
}