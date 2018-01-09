#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "gol.h"

void cell_init(int x, int y,int states[],cell *cells[]){
	assert((UNDER <= OVER));
	int newx,newy;
	cell *zero_cell = malloc(sizeof(cell));

	int n[8][2] = {{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};//Neighbour position relative to cell
	/* For each cell on the grid from left->right, then top->bottom: */
	for(int i=0;i<x*y;i++){ 
		cells[i]->posx = i%x; //change x 
		cells[i]->posy = i/x; //change y
		cells[i]->state = states[i]; //make the "state" equal to any predefined "state" from input
		cells[i]->newstate = states[i];
		/* For each neighbour of a cell, change the neighbour's x and y position relative to the grid*/
		for(int k=0;k<8;k++){
			newx = cells[i]->posx + n[k][0];
			newy = cells[i]->posy + n[k][1];
			/* Ensures that the neighbours are actually on the grid. If not, point them somewhere to null.*/
			if(newx>=0 && newx<x && newy>=0 && newy<y){
				cells[i]->neighbours[k] = cells[newy*x+newx];
			} else{
				cells[i]->neighbours[k] = zero_cell;
			}
		}
	}
	return;
}

void cell_prime(cell *c){
	int sum = 0;
	for(int i=0;i<8;i++){
		sum += c->neighbours[i]->state;
	}
	if(c->state){
		if((sum < UNDER) || (sum > OVER)){
			c->newstate=0;
		}
	}else{
		if(sum == SPAWN){
			c->newstate=1;
		}
	}
	return;
}

void cell_transfer(cell *cells[],int size){
	for(int i=0;i<size;i++){
		cells[i]->state=cells[i]->newstate;
	}
	return;
}

void cell_change(cell *cells[],int posx,int posy,int x){
	cells[x*posy + posx]->state = !cells[x*posy + posx]->state;
	cells[x*posy + posx]->newstate = !cells[x*posy + posx]->newstate;	
	return;
}

void cursor_move(char action,cursor *curs,int x,int y,char *start){

	switch(action){
		case 'L':{
			curs->posx--;
			curs->posx += curs->posx>=0?0:x;
			break;
		}
		case 'R':{
			curs->posx++;
			curs->posx -= curs->posx>=x?x:0;
			break;
		}
		case 'U':{
			curs->posy--;
			curs->posy += curs->posy>=0?0:y;
			break;
		}
		case 'D':{
			curs->posy++;
			curs->posy -= curs->posy>=y?y:0; 
			break;
		}
		case 'P': curs->isClick = 1; break;
		case 'S': *start=!(*start); break;
		default: return;
	}
}

void cell_update(cell *cells[], int size){
	for(int i=0;i<size;i++){
		cell_prime(cells[i]);
	}
	cell_transfer(cells,size);
	return;
}

void create_glider(int *glider, int size){
	/*A glider can only exist on a 4x4 grid. A certain algorithm creates a predefined state*/
	assert(size>4);
	for(int i=0;i<size*size;i++){
		glider[i]= 0;
	}
	int diff=size-4;
	glider[6+diff]=1;glider[11+diff*2]=1;glider[13+diff*3]=1;glider[14+diff*3]=1;glider[15+diff*3]=1;
	return;
}

void create_mp(int *map, int x,int y){
	for(int j=0;j<y;j++){
		for(int i=0;i<x;i++){
			if(((j%4)<2) && ((i%4)<2)){
				if((i<2||x-i<3)||(j<2||y-j<3)) map[j*x+i] = 1;
				else map[j*x+i] = 0;
			}else map[j*x+i] = 0;
		}
	}
}






