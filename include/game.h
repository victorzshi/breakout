#pragma once

#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "texture.h"
#include "timer.h"

class Game
{
public:
	Game();

	void start();

	void free();

private:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;

	SDL_Window* window;

	SDL_Renderer* renderer;

	TTF_Font* font;

	bool is_running;

	int frame_total;

	Timer frame_timer;

	std::stringstream frame_text;

	Texture texture;

	void process_input();

	void update();

	void render();
};