#include "score.h"

Score::Score()
{
	score = 0;
	is_game_over = false;

	font = TTF_OpenFont("assets/fonts/PressStart2P-Regular.ttf", 16);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		throw;
	}
}

void Score::set_position(double x, double y)
{
	position = Vector2(x, y);
}

void Score::break_brick()
{
	score += BREAK_BRICK_POINTS;
}

void Score::lose_ball()
{
	if (score + LOSE_BALL_POINTS > 0)
	{
		score += LOSE_BALL_POINTS;
	}
	else
	{
		score = 0;
	}
}

void Score::set_is_game_over(bool is_game_over)
{
	this->is_game_over = is_game_over;
}

bool Score::get_is_game_over()
{
	return is_game_over;
}

void Score::update(SDL_Renderer* renderer)
{
	score_text.str("");
	score_text << "Total Score: " << score;

	score_texture.load_text(renderer, font, score_text.str().c_str(), FONT_COLOR);
}

void Score::render(SDL_Renderer* renderer)
{
	int offset_x = (int)round(position.x - score_texture.get_width() / 2.0);
	int offset_y = (int)round(position.y - score_texture.get_height() / 2.0);

	score_texture.render(renderer, offset_x, offset_y);
}

void Score::free()
{
	score_texture.free();

	TTF_CloseFont(font);
	font = NULL;
}
