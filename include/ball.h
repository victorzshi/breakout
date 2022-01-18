#pragma once

#include <SDL.h>

#include "bricks.h"
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

	void update(Walls& walls, Bricks& bricks, Paddle& paddle);

	void render(SDL_Renderer* renderer, double elapsed_time);

	void free();

private:
	const double RADIUS = 5.0;
	const double START_VELOCITY = 1.0;
	const double INCREASE_VELOCITY = 0.25;
	const double MAX_VELOCITY = 5.0;

	double current_velocity;

	Vector2 start_position;
	Vector2 position;
	Vector2 velocity;

	Circle collider;

	void reset();
};
