#include "walls.h"

Walls::Walls()
{
	top = { 0, 0, 0, 0 };
	bottom = { 0, 0, 0, 0 };
	left = { 0, 0, 0, 0 };
	right = { 0, 0, 0, 0 };
}

void Walls::set_dimensions(double x, double y, int w, int h)
{
	int offset_x = (int)round(x - w / 2.0);
	int offset_y = (int)round(y - h / 2.0);

	top.x = offset_x;
	top.y = offset_y;
	top.w = w;
	top.h = THICKNESS;

	bottom.x = offset_x;
	bottom.y = offset_y + h - THICKNESS;
	bottom.w = w;
	bottom.h = THICKNESS;

	left.x = offset_x;
	left.y = offset_y;
	left.w = THICKNESS;
	left.h = h;

	right.x = offset_x + w - THICKNESS;
	right.y = offset_y;
	right.w = THICKNESS;
	right.h = h;
}

SDL_Rect& Walls::get_top()
{
	return top;
}

SDL_Rect& Walls::get_bottom()
{
	return bottom;
}

SDL_Rect& Walls::get_left()
{
	return left;
}

SDL_Rect& Walls::get_right()
{
	return right;
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
