#pragma once

#include <vector>

#include <SDL.h>

class Bricks
{
public:
	Bricks();

	void set_dimensions(double x, double y, int w, int h);

	SDL_Rect& get_collider();

	std::vector<std::vector<SDL_Rect>>& get_bricks();

	bool is_brick(int i, int j);

	void remove_brick(int i, int j);

	void render(SDL_Renderer* renderer);

	void free();

private:
	static const int BRICK_WIDTH = 30;
	static const int BRICK_HEIGHT = 10;

	SDL_Rect collider;

	std::vector<std::vector<SDL_Rect>> bricks;
};
