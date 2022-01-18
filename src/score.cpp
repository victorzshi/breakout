#include "score.h"

Score::Score()
{
	total_score = 0;
	is_game_over = false;

	score_font = TTF_OpenFont("assets/fonts/PressStart2P-Regular.ttf", 16);
	if (score_font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		throw;
	}
}

void Score::set_position(Vector2 v)
{
	position = v;
}

void Score::break_brick()
{
	total_score += BREAK_BRICK_POINTS;
}

void Score::lose_ball()
{
	if (total_score + LOSE_BALL_POINTS > 0)
	{
		total_score += LOSE_BALL_POINTS;
	}
	else
	{
		total_score = 0;
	}
}

int Score::get_total_score()
{
	return total_score;
}

int Score::get_max_score(int total_bricks)
{
	return BREAK_BRICK_POINTS * total_bricks;
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
	score_text << "Total Score: " << total_score;

	score_texture.load_text(renderer, score_font, score_text.str().c_str(), SCORE_FONT_COLOR);
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

	TTF_CloseFont(score_font);
	score_font = NULL;
}
