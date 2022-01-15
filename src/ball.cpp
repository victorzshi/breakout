#include "ball.h"
#include "physics.h"

Ball::Ball()
{
    position = Vector2();
    velocity = Vector2(1.0, 1.0);

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

void Ball::update(Walls& walls, Paddle& paddle)
{
    velocity = Vector2::limit(velocity, MAX_VELOCITY);

    Vector2 new_position = Vector2::add(position, velocity);
    set_position(new_position.x, new_position.y);

    if (Physics::is_collision(collider, walls.get_left()) ||
        Physics::is_collision(collider, walls.get_right()))
    {
        new_position = Vector2::subtract(position, velocity);
        set_position(new_position.x, new_position.y);

        velocity.x *= -1;
    }

    if (Physics::is_collision(collider, walls.get_top()) ||
        Physics::is_collision(collider, walls.get_bottom()))
    {
        new_position = Vector2::subtract(position, velocity);
        set_position(new_position.x, new_position.y);

        velocity.y *= -1;
    }

    if (Physics::is_collision(collider, paddle.get_collider()))
    {
        new_position = Vector2::subtract(position, velocity);
        set_position(new_position.x, new_position.y);

        if (position.y <= paddle.get_collider().y) {
            velocity.y *= -1;
            velocity = Vector2::multiply(velocity, VELOCITY_MULTIPLIER);
        }
        else
        {
            velocity.x *= -1;
        }
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
