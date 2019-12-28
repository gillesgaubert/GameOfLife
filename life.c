/* game of life */

#include <stdio.h>
#include <stdbool.h>
#include "unistd.h"
#include "life.h"



// un organisme avec aucune cellules vivantes...
void createOrganism(CELL organism [SIZEX][SIZEY]) {
	int i;
	int j;
	for (i=0;i<SIZEX;i++) {
		for (j=0;j<SIZEY;j++) {
			organism[i][j].evolving=false;
			organism[i][j].alive=false;
		}
	}
}

// permets de mettre une position de depart
void seedLife(CELL organism [SIZEX][SIZEY]) {
	int cellNumber;
	int column;
	int line;
	int i;
	puts("Et te voici le Créateur");
	printf("Donne le nombre de cellules à créer : ");
	scanf("%d",&cellNumber);
	// on assigne donc les cellules vivantes
	for (i=0;i<cellNumber;i++) {
		printf("Donne un colonne de 0 à %d : ",SIZEX);
		scanf("%d",&column);
		printf("Donne une ligne de 0 à %d : ",SIZEY);
		scanf("%d",&line);
		organism[column][line].evolving=false;
		organism[column][line].alive=true;
	}
}

// est qu'on est dans les limites ?
bool outside(int i,int j) {
    if ((i<0) || (i>(SIZEX-1))) return true;
    if ((j<0) || (j>(SIZEY-1))) return true;
    return false;
}

// on compte le nbre de cellules vivantes autour
// d'une position donnee
int aliveCellsAround(CELL organism[SIZEX][SIZEY],int c,int l) {
	int i;
	int j;
	int aliveCellsNumber=0;
	for (i=-1;i<2;i++) {
		for (j=-1;j<2;j++) {
			if ((i!=0) || (j!=0)) {
				if ((!outside(c+i,l+j)) && (organism[c+i][l+j].alive)) {
					aliveCellsNumber++;
				}
			}
		}
	}
	return aliveCellsNumber;
}

// fait evoluer les cellules si besoin
void evolving(CELL* ptrCell) {
    if ((*ptrCell).evolving) {
        (*ptrCell).alive=!(*ptrCell).alive;
        (*ptrCell).evolving=false;
    }
}

// change le statut de la cellule qui va evoluer
void changeStatus(CELL* ptrCell) {
    (*ptrCell).evolving=true;
}

// analyse le changement en suivant les regles
// de la vie
void analyseChange(CELL organism[SIZEX][SIZEY],int c,int l) {
	CELL cell;
	cell=organism[c][l];
	int neighbours;
	neighbours=aliveCellsAround(organism,c,l);
	if ((cell.alive) && ((neighbours>3) || (neighbours<2))) {
		changeStatus(&cell);
	}
	if ((!cell.alive) && (neighbours==3)) {
		changeStatus(&cell);
	}
	organism[c][l]=cell;
}

// analyse ou modifie selon l'etat du flag modify
void analyseOrMutate(CELL organism[SIZEX][SIZEY],bool modify) {
	int i;
	int j;
	for (i=0;i<SIZEX;i++) {
		for (j=0;j<SIZEY;j++) {
			// donc pour chaque cellule on fait...
			if (modify) {
				evolving(&organism[i][j]);
			} else {
				analyseChange(organism,i,j);
			}
		}
	}
}

// retourne le caractere O pour afficher une cellule
// vivante, un espace sinon
char printState(CELL cell) {
	if (cell.alive) {
		return ALIVE;
	} else {
		return DEAD;
	}
}

// affiche l'organisme
void showOrganism(CELL organism[SIZEX][SIZEY]) {
	printf("\n");
	int i;
	int j;
	char state;
	// premiere ligne
	printf(" /");
	for (i=0;i<(2*SIZEX-1);i++) {
		printf("-");
	}
	printf("\\\n");
	// les autres
	for (i=0;i<SIZEY;i++) {
		printf(" |");
		for (j=0;j<SIZEX;j++) {
			printf("%c|",printState(organism[j][i]));
		}
		printf("\n");
	}
	// la derniere ligne
	printf(" \\");
	for (i=0;i<(2*SIZEX-1);i++) {
		printf("-");
	}
	printf("/\n");
}


/* Reste à faire : 
implementation de certains organismes qui sont connus pour
provoquer des periodes ou des extinctions.
implementer une interface plus conviviale en particulier grace à la bibliotheque ncurse. */


// main
void main(){
	// declaration de l'organisme
	CELL organism [SIZEX][SIZEY];
	
	// nombre de cycles de vie
	int cyclesNumber=0;

	// organisme est vide
	createOrganism(organism);
	// on lui ajoute un peu de vie
	seedLife(organism);
	// on affiche l'organisme
	puts("Et au départ, Dieu (Vous) créa :");
	showOrganism(organism);

	// cycles de vie
	printf("Combien voulez vous de cycles de vie : ");
	scanf("%d",&cyclesNumber);
	int i;
	for (i=1;i<=cyclesNumber;i++) {
		printf("C'est le cycle %d...\n",i);

		// on regarde si des cellules doivent muter
		analyseOrMutate(organism,false);

		// ensuite on les mute
		analyseOrMutate(organism,true);
		
		// on affiche l'organisme
		showOrganism(organism);

		// on attend 2 secondes
		sleep(2);
	}
}
