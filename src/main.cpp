#include <stdio.h>

#include <SDL.h>

#include "game.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		throw;
	}

	Game* game = new Game();

	game->render();

	SDL_Delay(2000);
	
	game->free();
	SDL_Quit();

	return 0;
}