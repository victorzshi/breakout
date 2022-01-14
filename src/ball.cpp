#include "ball.h"
#include "physics.h"

Ball::Ball()
{
    position = Vector2();
    velocity = Vector2(SPEED, SPEED);
    acceleration = Vector2(-0.01, 0.01);

    collider = { position.x, position.y, RADIUS };
}

void Ball::set_position(double x, double y)
{
    position = Vector2(x, y);

    update_collider();
}

Circle& Ball::get_collider()
{
    return collider;
}

void Ball::update(Walls& walls)
{
    velocity = Vector2::add(velocity, acceleration);
    velocity = Vector2::limit(velocity, 10.0);
    position = Vector2::add(position, velocity);

    update_collider();

    if (Physics::is_collision(collider, walls.get_left()) ||
        Physics::is_collision(collider, walls.get_right()))
    {
        position = Vector2::subtract(position, velocity);
        velocity.x *= -1;

        update_collider();
    }

    if (Physics::is_collision(collider, walls.get_top()) ||
        Physics::is_collision(collider, walls.get_bottom()))
    {
        position = Vector2::subtract(position, velocity);
        velocity.y *= -1;

        update_collider();
    }
}

void Ball::render(SDL_Renderer* renderer, double elapsed_time)
{
    Vector2 rendered_position;

    if (elapsed_time > 0)
    {
        Vector2 estimated_velocity = Vector2::multiply(velocity, elapsed_time);
        rendered_position = Vector2::add(position, estimated_velocity);
    }
    else
    {
        rendered_position = position;
    }
   
    int x = (int)round(rendered_position.x);
    int y = (int)round(rendered_position.y);
    int offset_x = (int)round(RADIUS);
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

void Ball::update_collider()
{
    collider.x = position.x;
    collider.y = position.y;
}