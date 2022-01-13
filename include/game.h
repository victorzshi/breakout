#pragma once

#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "texture.h"

class Game
{
public:
	Game();

	void start();

	void free();

private:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	static const int MS_PER_UPDATE = 16;

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	bool is_running;
	int start_time;
	int frame_total;
	std::stringstream frame_text;
	Texture texture;

	void process_input();

	void update();

	void render(int elapsed_time);
};