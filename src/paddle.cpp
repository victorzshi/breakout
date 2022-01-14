#include "paddle.h"
#include "physics.h"

Paddle::Paddle()
{
	position = Vector2();
    velocity = Vector2();
    acceleration = Vector2();

    collider = {0, 0, WIDTH, HEIGHT};
}

void Paddle::set_position(double x, double y)
{
    position = Vector2(x, y);

    update_collider();
}

void Paddle::process_input(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            acceleration = Vector2(-SPEED, 0.0);
            break;
        case SDLK_RIGHT:
            acceleration = Vector2(SPEED, 0.0);
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
    velocity = Vector2::limit(velocity, MAX_SPEED);
    position = Vector2::add(position, velocity);

    update_collider();

    if (Physics::is_collision(collider, walls.get_left()) ||
        Physics::is_collision(collider, walls.get_right()))
    {
        position = Vector2::subtract(position, velocity);

        update_collider();
    }
}

void Paddle::render(SDL_Renderer* renderer, double elapsed_time)
{
    SDL_Rect box;

    if (elapsed_time > 0)
    {
        Vector2 estimated_velocity = Vector2::multiply(velocity, elapsed_time);
        Vector2 rendered_position = Vector2::add(position, estimated_velocity);

        int x = (int)round(rendered_position.x - WIDTH / 2.0);
        int y = (int)round(rendered_position.y - HEIGHT / 2.0);

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

void Paddle::update_collider()
{
    collider.x = (int)round(position.x - WIDTH / 2.0);
    collider.y = (int)round(position.y - HEIGHT / 2.0);
}
