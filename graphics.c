#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "gol.h"

void grid_update(SDL_Renderer *renderer, cursor *curs, int x, int y, cell *cells[])
{
    /* Sets x and y position of rectangle at 0 and width and height relative to screen */
    SDL_Rect cell_rect={0,0,(SCREEN_WIDTH/x),(SCREEN_HEIGHT/y)}; 
    /* For each cell on the grid, create a rectangle. Change its colour depending on its state.*/
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            if(i==curs->posy && j==curs->posx){
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);   
                SDL_RenderDrawRect(renderer,&cell_rect);
            }   
            else if(cells[i*x+j]->state==1){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   
                SDL_RenderFillRect(renderer,&cell_rect);

            }
            else{
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);   
                SDL_RenderFillRect(renderer,&cell_rect);                
            }
            cell_rect.x+=(SCREEN_WIDTH/x); //Keep creating rectangles to the right
        }
        cell_rect.y+=(SCREEN_HEIGHT/y); //Go to the next row
        cell_rect.x=0; //Go back to the first column
    }
}






