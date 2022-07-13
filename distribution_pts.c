#include "../inc/distribution_pts.h"

char show_lvl_up(){

	int valide;
	MLV_Input_box * box; 

	char * chaine;


	valide = 0;

	while(valide == 0){

		MLV_wait_input_box((LONGUEUR / 2) + 50, (LARGEUR / 2) + 200, (LONGUEUR / 2) + 300, (LARGEUR / 2) + 50, MLV_COLOR_MAROON, MLV_COLOR_DEEPPINK4, MLV_COLOR_MAROON, "Nouvelle Compétence : ", &chaine);


		if(strcmp(chaine, "Intelligence") == 0){

			MLV_desactivate_input_box();
			return 'i';
		}

		else if(strcmp(chaine, "Defense") == 0){
			MLV_desactivate_input_box();
			return 'd';
		}

		else if(strcmp(chaine, "Attaque") == 0){
			MLV_desactivate_input_box();
			return 'a';
		}

		else if(strcmp(chaine, "recommencer") == 0){
			MLV_desactivate_input_box();
			return 'r';
		}
	}

	return 'x';
}
