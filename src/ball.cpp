#include "ball.h"

Ball::Ball()
{
    position = Vector2D();
    velocity = Vector2D(SPEED, SPEED);
}

void Ball::set_position(Vector2D vector)
{
    position = vector;
}

void Ball::move(Walls& walls)
{
    position = position.add(velocity);

    // This puts the center of the ball in the wall...
    if (position.x >= 640 || position.x <= 0)
    {
        velocity.x *= -1;
    }

    if (position.y > 480 || position.y < 0)
    {
        velocity.y *= -1;
    }
}

void Ball::render(SDL_Renderer* renderer, double elapsed_time)
{
    Vector2D rendered_position;

    if (elapsed_time > 0)
    {
        rendered_position = position.add(velocity.multiply(elapsed_time));
    }
    else
    {
        rendered_position = position;
    }
   
    int x = rendered_position.x;
    int y = rendered_position.y;
    int offset_x = RADIUS;
    int offset_y = 0;
    int error = 0;

    while (offset_x >= offset_y)
    {
        SDL_RenderDrawPoint(renderer, x + offset_x, y + offset_y);
        SDL_RenderDrawPoint(renderer, x + offset_y, y + offset_x);
        SDL_RenderDrawPoint(renderer, x - offset_y, y + offset_x);
        SDL_RenderDrawPoint(renderer, x - offset_x, y + offset_y);
        SDL_RenderDrawPoint(renderer, x - offset_x, y - offset_y);
        SDL_RenderDrawPoint(renderer, x - offset_y, y - offset_x);
        SDL_RenderDrawPoint(renderer, x + offset_y, y - offset_x);
        SDL_RenderDrawPoint(renderer, x + offset_x, y - offset_y);

        if (error <= 0)
        {
            offset_y += 1;
            error += 2 * offset_y + 1;
        }
        else
        {
            offset_x -= 1;
            error -= 2 * offset_x + 1;
        }
    }
}

void Ball::free()
{
	return;
}
