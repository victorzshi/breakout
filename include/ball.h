#pragma once

#include <SDL.h>

#include "vector_2d.h"
#include "walls.h"

class Ball
{
public:
	Ball();

	void set_position(Vector2D vector);

	void move(Walls& walls);

	void render(SDL_Renderer* renderer, double elapsed_time);

	void free();

private:
	static const int RADIUS = 5;
	static const int SPEED = 3;

	Vector2D position;

	Vector2D velocity;
};
