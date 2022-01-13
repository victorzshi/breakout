#include <stdio.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "game.h"

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		throw;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		throw;
	}

	return true;
}

void quit()
{
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	if (init())
	{
		Game game = Game();

		game.start();
	
		game.free();
	}
	else
	{
		quit();
	}
	
	return 0;
}
