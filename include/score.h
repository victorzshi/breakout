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

	void set_position(double x, double y);

	void set_score(int score);

	void set_game_over();

	bool get_game_over();

	void update(SDL_Renderer* renderer);

	void render(SDL_Renderer* renderer);

	void free();
private:
	const SDL_Color FONT_COLOR = { 255, 255, 255 };

	Vector2 position;

	int score;

	bool game_over;

	TTF_Font* font;

	std::stringstream score_text;

	Texture score_texture;
};
