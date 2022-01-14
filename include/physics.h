#pragma once

#include <SDL.h>

#include "circle.h"

class Physics
{
public:
	static bool is_collision(Circle& a, SDL_Rect& b);

	static bool is_collision(SDL_Rect& a, SDL_Rect& b);

private:
	static double distance_squared(double x_1, double y_1, double x_2, double y_2);
};
