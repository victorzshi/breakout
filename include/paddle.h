#pragma once

#include <SDL.h>

#include "vector_2.h"
#include "walls.h"

class Paddle
{
public:
	Paddle();

	void set_position(double x, double y);

	Vector2 get_position();

	Vector2 get_velocity();

	SDL_Rect& get_collider();

	void process_input(SDL_Event& event);

	void update(Walls& walls);

	void render(SDL_Renderer* renderer, double elapsed_time);

	void free();

private:
	static const int WIDTH = 60;
	static const int HEIGHT = 10;

	const double ACCELERATION = 0.1;
	const double MAX_VELOCITY = 3.0;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;

	SDL_Rect collider;

	void update_collider();

	Vector2 calculate_top_left_corner(double x, double y);
};