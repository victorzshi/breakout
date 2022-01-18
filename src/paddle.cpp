#include "paddle.h"
#include "physics.h"

Paddle::Paddle()
{
	position = Vector2();
    velocity = Vector2();
    acceleration = Vector2();

    collider.x = 0;
    collider.y = 0;
    collider.w = WIDTH;
    collider.h = HEIGHT;
}

void Paddle::set_position(Vector2 v)
{
    position = v;

    Vector2 offset = calculate_top_left_corner(position.x, position.y);

    int x = (int)round(offset.x);
    int y = (int)round(offset.y);

    collider.x = x;
    collider.y = y;
}

Vector2 Paddle::get_position()
{
    return position;
}

Vector2 Paddle::get_velocity()
{
    return velocity;
}

SDL_Rect& Paddle::get_collider()
{
    return collider;
}

void Paddle::process_input(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            acceleration = Vector2(-ACCELERATION, 0.0);
            break;
        case SDLK_RIGHT:
            acceleration = Vector2(ACCELERATION, 0.0);
            break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        acceleration = Vector2(0.0, 0.0);
        velocity = Vector2();
    }
}

void Paddle::update(Walls& walls)
{
    velocity = Vector2::add(velocity, acceleration);
    velocity = Vector2::limit(velocity, MAX_VELOCITY);

    Vector2 new_position = Vector2::add(position, velocity);
    set_position(new_position);

    if (Physics::is_collision(collider, walls.get_left()) ||
        Physics::is_collision(collider, walls.get_right()))
    {
        new_position = Vector2::subtract(position, velocity);
        set_position(new_position);
    }
}

void Paddle::render(SDL_Renderer* renderer, double elapsed_time)
{ 
    SDL_Rect box;

    if (elapsed_time > 0)
    {
        Vector2 estimated_velocity = Vector2::multiply(velocity, elapsed_time);
        Vector2 rendered_position = Vector2::add(position, estimated_velocity);
        Vector2 offset = calculate_top_left_corner(rendered_position.x, rendered_position.y);

        int x = (int)round(offset.x);
        int y = (int)round(offset.y);

        box = { x, y, WIDTH, HEIGHT };
    }
    else
    {
        box = collider;
    }

    SDL_RenderFillRect(renderer, &box);
}

void Paddle::free()
{
	return;
}

Vector2 Paddle::calculate_top_left_corner(double x, double y)
{
    double offset_x = x - WIDTH * 0.5;
    double offset_y = y - HEIGHT * 0.5;

    return Vector2(offset_x, offset_y);
}
