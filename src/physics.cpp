#include "physics.h"

bool Physics::is_collision(Circle& a, SDL_Rect& b)
{
    double closest_x, closest_y;

    if (a.x < b.x)
    {
        closest_x = b.x;
    }
    else if (a.x > b.x + b.w)
    {
        closest_x = b.x + b.w;
    }
    else
    {
        closest_x = a.x;
    }

    if (a.y < b.y)
    {
        closest_y = b.y;
    }
    else if (a.y > b.y + b.h)
    {
        closest_y = b.y + b.h;
    }
    else
    {
        closest_y = a.y;
    }

    if (distance_squared(a.x, a.y, closest_x, closest_y) < a.r * a.r)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Physics::is_collision(SDL_Rect& a, SDL_Rect& b)
{
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;

    left_a = a.x;
    right_a = a.x + a.w;
    top_a = a.y;
    bottom_a = a.y + a.h;

    left_b = b.x;
    right_b = b.x + b.w;
    top_b = b.y;
    bottom_b = b.y + b.h;

    if (bottom_a <= top_b || top_a >= bottom_b || right_a <= left_b || left_a >= right_b)
    {
        return false;
    }
    else
    {
        return true;
    }
}

double Physics::distance_squared(double x_1, double y_1, double x_2, double y_2)
{
    double delta_x = x_2 - x_1;
    double delta_y = y_2 - y_1;

    return delta_x * delta_x + delta_y * delta_y;
}
