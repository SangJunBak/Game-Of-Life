#ifndef GOL_H
#define GOL_H

/* John Conway's Game of Life Adaptation By Brayden Riggs, Sang Jun Bak, and Emily Huang */

#include <SDL2/SDL.h>
/* Rules/Constants */
#define UNDER 2 //Rule 1: An 'alive' cell 'dies' if it has strictly less than this number of 'alive neighbours'
#define OVER 3  //Rule 2: An 'alive' cell 'dies' if has strictly more than this number of 'alive neighbours'
#define SPAWN 3 //Rule 3: A 'dead' cell comes 'alive' if it has exactly this number of 'alive neighbours'    
#define FPS 10  
static const int SCREEN_WIDTH = 600; 
static const int SCREEN_HEIGHT = 600;
static const int GRID_X = 20; //Grid x
static const int GRID_Y = 20; //Grid y

/* A cell describes the properties of an object on a grid. Each cell has: */
typedef struct cell{
	/*Eight neighbours*/
	struct cell* neighbours[8]; 
	/* An x-position and y-position relative to the top left corner of the grid*/
	int posx; 
	int posy; 
	/* An initial and final state. 0 means dead while 1 means alive. */
	int state; 
	int newstate; 
}cell;

typedef struct cursor{
	int posx;
	int posy;
	int isClick;
}cursor;

void cell_change(cell *cells[],int posx,int posy,int x);
void cursor_move(char action,cursor *curs,int x,int y,char *start);
void create_mp(int *map, int x,int y);

/* Sums the "state" values of each neighbour of a cell "c". 
	Updates c's new state according to the rules */
void cell_prime(cell *c);
/* Helper Function: Changes a cell's state to its newstate */
void cell_transfer(cell *cells[], int size);
/* Used to update each cell by calling cell_prime, then cell_transfer */
void cell_update(cell *cells[], int size);
/* Used to initialize every cell on the grid and their properties */
void cell_init(int x,int y,int states[], cell *cells[]); 
/* Updates the grid at a constant frame rate. Uses a renderer to draw the grid.*/
void grid_update(SDL_Renderer *renderer, cursor *curs, int x, int y, cell **cells);
/* A function to create a "glider" for its respective grid size*/
void create_glider(int *glider, int size);
#endif