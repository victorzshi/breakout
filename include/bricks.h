#pragma once

#include <vector>

#include <SDL.h>

#include "score.h"

class Bricks
{
public:
	Bricks();

	void set_dimensions(double x, double y, int w, int h);

	SDL_Rect& get_collider();

	std::vector<std::vector<SDL_Rect>>& get_bricks();

	bool is_brick(int i, int j);

	void remove_brick(int i, int j);

	void update(Score& score);

	void render(SDL_Renderer* renderer);

	void free();

private:
	static const int BRICK_WIDTH = 30;
	static const int BRICK_HEIGHT = 10;

	int total_bricks, removed_bricks;

	SDL_Rect collider;

	std::vector<std::vector<SDL_Rect>> bricks;
};
