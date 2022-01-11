#include <stdio.h>

#include "game.h"

Game::Game()
{
	window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL error: %s\n", SDL_GetError());
		throw;
	}

	surface = SDL_GetWindowSurface(window);
}

void Game::render()
{
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

	SDL_UpdateWindowSurface(window);
}

void Game::free()
{
	SDL_DestroyWindow(window);
	SDL_FreeSurface(surface);
	window = NULL;
	surface = NULL;
}
