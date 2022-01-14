#pragma once

#include <SDL.h>

#include "vector_2.h"
#include "walls.h"

class Paddle
{
public:
	Paddle();

	void set_position(double x, double y);

	void process_input(SDL_Event& event);

	void update(Walls& walls);

	void render(SDL_Renderer* renderer, double elapsed_time);

	void free();

private:
	static const int WIDTH = 50;
	static const int HEIGHT = 5;

	const double SPEED = 0.025;
	const double MAX_SPEED = 2.0;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	SDL_Rect collider;

	void update_collider();
};