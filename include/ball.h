#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "audio.h"
#include "bricks.h"
#include "circle.h"
#include "paddle.h"
#include "score.h"
#include "vector_2.h"
#include "walls.h"

class Ball
{
public:
	Ball();

	void set_position(Vector2 v);

	Circle& get_collider();

	void update(SDL_Renderer* renderer, Audio& audio, Score& score, Walls& walls, Bricks& bricks, Paddle& paddle);

	void render(SDL_Renderer* renderer, double elapsed_time);

	void free();

private:
	const double RADIUS = 5.0;
	const double START_VELOCITY = 1.0;
	const double INCREASE_VELOCITY = 0.25;
	const double MAX_VELOCITY = 4.0;
	const SDL_Color RESET_FONT_COLOR = { 255, 255, 255 };

	double current_velocity;

	Vector2 start_position;
	Vector2 position;
	Vector2 velocity;

	Circle collider;

	bool is_reset;
	int reset_time;

	TTF_Font* reset_font;
	std::stringstream reset_text;
	Texture reset_texture;

	void reset();
};
