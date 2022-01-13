#include "walls.h"

Walls::Walls()
{
	top = { 0, 0, 0, 0 };
	bottom = { 0, 0, 0, 0 };
	left = { 0, 0, 0, 0 };
	right = { 0, 0, 0, 0 };
}

void Walls::set_dimensions(int x, int y, int w, int h)
{
	top.x = x;
	top.y = y;
	top.w = w;
	top.h = THICKNESS;

	bottom.x = x;
	bottom.y = y + h - THICKNESS;
	bottom.w = w;
	bottom.h = THICKNESS;

	left.x = x;
	left.y = y;
	left.w = THICKNESS;
	left.h = h;

	right.x = x + w - THICKNESS;
	right.y = y;
	right.w = THICKNESS;
	right.h = h;
}

void Walls::render(SDL_Renderer* renderer)
{
	SDL_RenderFillRect(renderer, &top);
	SDL_RenderFillRect(renderer, &bottom);
	SDL_RenderFillRect(renderer, &left);
	SDL_RenderFillRect(renderer, &right);
}

void Walls::free()
{
	return;
}
