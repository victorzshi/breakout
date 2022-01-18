#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <sstream>

#include "texture.h"
#include "vector_2.h"

class Score
{
public:
	Score();

	void set_position(Vector2 v);

	void break_brick();

	void lose_ball();

	int get_total_score();

	int get_max_score(int total_bricks);

	void set_is_game_over(bool is_game_over);

	bool get_is_game_over();

	void update(SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer);

	void free();
private:
	static const int BREAK_BRICK_POINTS = 100;
	static const int LOSE_BALL_POINTS = -300;
	const SDL_Color SCORE_FONT_COLOR = { 255, 255, 255 };

	Vector2 position;

	int total_score;

	bool is_game_over;

	TTF_Font* score_font;
	std::stringstream score_text;
	Texture score_texture;
};
