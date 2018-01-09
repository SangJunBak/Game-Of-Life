#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "gol.h"

int main(int argc, char* args[]){
	/* Grid Initialization */
	int GRID_SIZE=GRID_X*GRID_Y;
	int glider[GRID_SIZE];
	int states[GRID_SIZE];
	cell raw_cells[GRID_SIZE];
	cell **cells=malloc((GRID_SIZE)*sizeof(cell));
	for(int i=0; i<GRID_SIZE;i++){
		cells[i] = &raw_cells[i];
		states[i] = 0;
	}
	int map[GRID_SIZE];
	create_mp(map, GRID_X,GRID_Y);
	cell_init(GRID_X,GRID_Y,map,cells);

	// create_glider(glider,GRID_X);


	/* SDL Initialization */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;
    Uint32 start=0;
    bool running = true; 
    char pause = 0;
	cursor *curs = (cursor*)malloc(sizeof(cursor));
	curs->posy=0;

    while(running)
    {
		start=SDL_GetTicks(); /* Track start time of program */

		while(SDL_PollEvent(&event)) /* Listen to events */
		{
			/* Keep the program running while it's open : */
		    if(event.type == SDL_QUIT)
		    {
		        running = false;
		    }
		    else if(event.type == SDL_KEYDOWN)
		    {
		    	switch(event.key.keysym.sym){

		    		case SDLK_LEFT:{
			    		cursor_move('L', curs, GRID_X,GRID_Y,&pause);
						grid_update(renderer,curs,GRID_X,GRID_Y,cells);
			    		SDL_RenderPresent(renderer); 
		    			break;
		    		}
		    		case SDLK_RIGHT:{
			    		cursor_move('R', curs, GRID_X,GRID_Y,&pause);
						grid_update(renderer,curs,GRID_X,GRID_Y,cells);
			    		SDL_RenderPresent(renderer); 
		    			break;
		    		}
		    		case SDLK_UP:{
			    		cursor_move('U', curs, GRID_X,GRID_Y,&pause);
						grid_update(renderer,curs,GRID_X,GRID_Y,cells);
			    		SDL_RenderPresent(renderer); 
		    			break;
		    		}
		    		case SDLK_DOWN:{
			    		cursor_move('D', curs, GRID_X,GRID_Y,&pause);
						grid_update(renderer,curs,GRID_X,GRID_Y,cells);
			    		SDL_RenderPresent(renderer); 
		    			break;
		    		}
		    		case SDLK_SPACE:{
			    		cursor_move('P', curs, GRID_X,GRID_Y,&pause);
						cell_change(cells,curs->posx,curs->posy,GRID_X);
						curs->isClick = 0;
						grid_update(renderer,curs,GRID_X,GRID_Y,cells);
			    		SDL_RenderPresent(renderer); 
		    			break;
		    		}
		    		case SDLK_RETURN:{
			    		cursor_move('S', curs, GRID_X,GRID_Y,&pause);
						cell_update(cells, GRID_SIZE);
						grid_update(renderer,curs,GRID_X,GRID_Y,cells);
			    		SDL_RenderPresent(renderer); 
		    			break;
		    		}
		    	}

		    	
		    }
		}

		if(pause){
			grid_update(renderer,curs,GRID_X,GRID_Y,cells); /* Update a render of the grid per frame */
			cell_update(cells, GRID_SIZE);

			SDL_RenderPresent(renderer); /* Draw the render per frame */

			/* Make sure the program runs at this specific frame rate */
			if(1000/FPS>SDL_GetTicks()-start){
				SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
			}	
		}
    }    
    /* Clear any memory in the heap */    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    free(cells);
    free(curs);
	curs = NULL;

	return 0;
}
