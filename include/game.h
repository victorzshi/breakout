#pragma once

#ifdef _DEBUG
#include <sstream>
#endif

#include <SDL.h>
#include <SDL_ttf.h>

#include "ball.h"
#include "bricks.h"
#include "paddle.h"
#include "score.h"
#include "texture.h"
#include "walls.h"

class Game
{
public:
	Game();

	void start();

	void free();

private:
	static const int SCREEN_WIDTH = 480;
	static const int SCREEN_HEIGHT = 640;
	static const int MS_PER_UPDATE = 5;

	#ifdef _DEBUG
	int start_time;
	int frame_total;
	int update_total;
	TTF_Font* debug_font;
	SDL_Color debug_font_color;
	std::stringstream frame_text;
	std::stringstream update_text;
	Texture frames_per_second_texture;
	Texture updates_per_second_texture;
	#endif

	bool is_running;

	SDL_Window* window;
	SDL_Renderer* renderer;

	Score score;
	Walls walls;
	Bricks bricks;
	Paddle paddle;
	Ball ball;

	TTF_Font* game_over_font;
	SDL_Color game_over_font_color;
	std::stringstream game_over_text;
	Texture game_over_texture;

	void process_input();

	void update();

	void render(double elapsed_time);
};
