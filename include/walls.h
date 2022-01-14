#pragma once

#include <SDL.h>

class Walls
{
public:
	Walls();

	void set_dimensions(int x, int y, int w, int h);

	SDL_Rect& get_top();

	SDL_Rect& get_bottom();

	SDL_Rect& get_left();

	SDL_Rect& get_right();

	void render(SDL_Renderer* renderer);

	void free();

private:
	static const int THICKNESS = 10;

	SDL_Rect top, bottom, left, right;
};
