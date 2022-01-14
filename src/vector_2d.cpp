#include <cmath>

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

Vector2D Vector2D::add(Vector2D v)
{
	return Vector2D(x + v.x, y + v.y);
}

Vector2D Vector2D::subtract(Vector2D v)
{
	return Vector2D(x - v.x, y - v.y);
}

Vector2D Vector2D::multiply(double n)
{
	return Vector2D(round(x * n), round(y * n));
}

Vector2D Vector2D::divide(double n)
{
	return Vector2D(round(x / n), round(y / n));
}

double Vector2D::magnitude()
{
	return sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize()
{
	double magnitude = this->magnitude();
	if (magnitude > 0)
	{
		return this->divide(magnitude);
	}
	else
	{
		throw;
	}
}
