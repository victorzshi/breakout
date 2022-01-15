#pragma once

#include <SDL.h>

#include "circle.h"
#include "paddle.h"
#include "vector_2.h"
#include "walls.h"

class Ball
{
public:
	Ball();

	void set_position(double x, double y);

	Circle& get_collider();

	void update(Walls& walls, Paddle& paddle);

	void render(SDL_Renderer* renderer, double elapsed_time);

	void free();

private:
	const double RADIUS = 5.0;
	const double MAX_VELOCITY = 5.0;

	double speed = 1.0;

	Vector2 position;
	Vector2 velocity;

	Circle collider;

	void update_collider();
};
