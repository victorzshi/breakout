#pragma once

#include <SDL.h>

class Game
{
public:
	Game();

	void render();

	void free();

private:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

	SDL_Window* window = NULL;

	SDL_Surface* surface = NULL;
};