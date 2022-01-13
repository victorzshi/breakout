#include "vector_2d.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Vector2D::add(Vector2D vector)
{
	x += vector.x;
	y += vector.y;
}
