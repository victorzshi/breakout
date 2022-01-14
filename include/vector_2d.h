#pragma once

class Vector2D
{
public:
	int x, y;

	Vector2D();

	Vector2D(int x, int y);

	Vector2D add(Vector2D v);

	Vector2D subtract(Vector2D v);

	Vector2D multiply(double n);

	Vector2D divide(double n);

	double magnitude();

	Vector2D normalize();
};
