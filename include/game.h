#pragma once

#include <SDL.h>

class Game
{
public:
	Game();

	void start();

	void free();

private:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

	bool is_running;

	SDL_Window* window;

	SDL_Renderer* renderer;

	void process_input();

	void update();

	void render();
};