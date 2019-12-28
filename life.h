/* life.h */


#ifndef INCL_VIE_H
#define INCL_VIE_H



#include <stdio.h>
#include <stdbool.h>


const int SIZEX=15;
const int SIZEY=15;
const char ALIVE='O';
const char DEAD=' ';


typedef struct {
	bool evolving;
	bool alive;
} CELL;



void createOrganism(CELL organism [SIZEX][SIZEY]);

void seedLife(CELL organism [SIZEX][SIZEY]);

bool outside(int i,int j);

int aliveCellsAround(CELL organism[SIZEX][SIZEY],int c,int l);

void evolving(CELL* ptrCell);

void changeStatus(CELL* ptrCell);

void analyseChange(CELL organism[SIZEX][SIZEY],int c,int l);

void analyseOrMutate(CELL organism[SIZEX][SIZEY],bool modify);

char printState(CELL cell);

void showOrganism(CELL organism[SIZEX][SIZEY]);





#endif
