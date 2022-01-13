#pragma once

#include <SDL.h>

class Ball
{
public:
	Ball();

	void set_position(int x, int y);

	void render(SDL_Renderer* renderer);

	void free();

private:
	static const int RADIUS = 5;

	int x, y;
};
