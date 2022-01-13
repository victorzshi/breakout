#pragma once

class Vector2D
{
public:
	int x, y;

	Vector2D();

	Vector2D(int x, int y);

	void add(Vector2D vector);
};
