#pragma once

#include <SDL.h>

#include "vector_2d.h"

class Ball
{
public:
	Ball();

	void set_position(Vector2D vector);

	void render(SDL_Renderer* renderer);

	void free();

private:
	static const int RADIUS = 5;

	Vector2D position;
};
