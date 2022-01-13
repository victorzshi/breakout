#pragma once

#ifdef _DEBUG
#include <sstream>
#endif

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
	static const int MS_PER_UPDATE = 5;

	#ifdef _DEBUG
	int start_time;
	int frame_total;
	int update_total;
	std::stringstream frame_text;
	std::stringstream update_text;
	Texture frames_per_second_texture;
	Texture updates_per_second_texture;
	#endif

	bool is_running;

	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	void process_input();

	void update();

	void render(int elapsed);
};