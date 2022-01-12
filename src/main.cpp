#include <stdio.h>

#include <SDL.h>

#include "game.h"

bool initialize()
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

	return true;
}

int main(int argc, char* args[])
{
	if (initialize())
	{
		Game game = Game();

		game.start();
	
		game.free();
	}
	else
	{
		SDL_Quit();
	}
	
	return 0;
}
