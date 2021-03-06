#include "bricks.h"

Bricks::Bricks()
{
	total_bricks = 0;
	removed_bricks = 0;
	collider = { 0, 0, 0, 0 };
}

void Bricks::set_dimensions(double x, double y, int w, int h)
{
	collider.x = (int)round(x - w / 2.0);
	collider.y = (int)round(y - h / 2.0);
	collider.w = w;
	collider.h = h;

	int total_bricks_width = w / BRICK_WIDTH;
	int total_bricks_height = h / BRICK_HEIGHT;
	total_bricks = total_bricks_width * total_bricks_height;

	bricks.resize(total_bricks_height);
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i].resize(total_bricks_width);
		for (int j = 0; j < bricks[i].size(); j++)
		{
			bricks[i][j].x = collider.x + (BRICK_WIDTH * j);
			bricks[i][j].y = collider.y + (BRICK_HEIGHT * i);
			bricks[i][j].w = BRICK_WIDTH;
			bricks[i][j].h = BRICK_HEIGHT;
		}
	}
}

SDL_Rect& Bricks::get_collider()
{
	return collider;
}

std::vector<std::vector<SDL_Rect>>& Bricks::get_bricks()
{
	return bricks;
}

int Bricks::get_total_bricks()
{
	return total_bricks;
}

bool Bricks::is_brick(int i, int j)
{
	SDL_Rect brick = bricks[i][j];
	if (brick.x == NULL && brick.y == NULL && brick.w == NULL && brick.h == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Bricks::remove_brick(int i, int j)
{
	if (is_brick(i, j))
	{
		bricks[i][j].x = NULL;
		bricks[i][j].y = NULL;
		bricks[i][j].h = NULL;
		bricks[i][j].w = NULL;

		++removed_bricks;
	}
	else
	{
		throw;
	}
}

void Bricks::update(Score& score)
{
	if (removed_bricks >= total_bricks)
	{
		score.set_is_game_over(true);
	}
}

void Bricks::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < bricks.size(); i++)
	{
		for (int j = 0; j < bricks[i].size(); j++)
		{
			int index = i % 3;
			switch (index)
			{
			case 2:
				SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
				break;
			case 1:
				SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
				break;
			case 0:
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
				break;
			}

			SDL_Rect brick;
			brick.x = bricks[i][j].x + 1;
			brick.y = bricks[i][j].y + 1;
			brick.w = bricks[i][j].w - 2;
			brick.h = bricks[i][j].h - 2;

			SDL_RenderFillRect(renderer, &brick);
		}
	}

	// Reset render color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Bricks::free()
{
	return;
}
