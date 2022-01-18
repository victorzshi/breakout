#include "ball.h"
#include "physics.h"

Ball::Ball()
{
    start_position = Vector2();
    position = Vector2();

    current_velocity = START_VELOCITY;
    velocity = Vector2(0.0, current_velocity);

    collider = { position.x, position.y, RADIUS };

    is_reset = false;
    reset_time = 0;

    reset_font = TTF_OpenFont("assets/fonts/PressStart2P-Regular.ttf", 32);
    if (reset_font == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        throw;
    }
}

void Ball::set_position(Vector2 v)
{
    if (start_position.x == 0.0 && start_position.y == 0.0)
    {
        start_position = v;
    }

    position = v;
    collider.x = position.x;
    collider.y = position.y;
}

Circle& Ball::get_collider()
{
    return collider;
}

void Ball::update(SDL_Renderer* renderer, Score& score, Walls& walls, Bricks& bricks, Paddle& paddle)
{
    if (is_reset)
    {
        int elapsed = SDL_GetTicks64() - reset_time;

        if (elapsed < 3000)
        {
            int countdown = ((3000 - elapsed) / 1000) + 1;

            reset_text.str("");
            reset_text << countdown;

            if (countdown == 3)
            {
                reset_text << "...";
            }
            else if (countdown == 2)
            {
                reset_text << "..";
            }
            else if (countdown == 1)
            {
                reset_text << ".";
            }

            reset_texture.load_text(renderer, reset_font, reset_text.str().c_str(), RESET_FONT_COLOR);
        }
        else
        {
            is_reset = false;
        }

        return;
    }

    velocity = Vector2::limit(velocity, MAX_VELOCITY);

    Vector2 new_position = Vector2::add(position, velocity);
    set_position(new_position);

    if (Physics::is_collision(collider, walls.get_left()) ||
        Physics::is_collision(collider, walls.get_right()))
    {
        new_position = Vector2::subtract(position, velocity);
        set_position(new_position);

        velocity.x *= -1;
    }

    if (Physics::is_collision(collider, walls.get_top()))
    {
        new_position = Vector2::subtract(position, velocity);
        set_position(new_position);

        velocity.y *= -1;
    }

    if (Physics::is_collision(collider, walls.get_bottom()))
    {
        reset();
        score.lose_ball();
    }

    if (Physics::is_collision(collider, bricks.get_collider()))
    {
        std::vector<std::vector<SDL_Rect>>& array_2d = bricks.get_bricks();

        for (int i = 0; i < array_2d.size(); i++)
        {
            for (int j = 0; j < array_2d[i].size(); j++)
            {
                if (bricks.is_brick(i, j) && Physics::is_collision(collider, array_2d[i][j])) {
                    new_position = Vector2::subtract(position, velocity);
                    set_position(new_position);

                    SDL_Rect brick = array_2d[i][j];

                    if (position.y <= brick.y || position.y >= brick.y + brick.h) {
                        velocity.y *= -1;
                    }
                    else
                    {
                        velocity.x *= -1;
                    }

                    bricks.remove_brick(i, j);
                    score.break_brick();
                }
            }
        }
    }

    SDL_Rect p_collider = paddle.get_collider();
    if (Physics::is_collision(collider, p_collider))
    {
        new_position = Vector2::subtract(position, velocity);
        set_position(new_position);

        // Change direction of ball
        if (position.y < p_collider.y) {
            double paddle_x = p_collider.x + p_collider.w * 0.5;
            double paddle_y = p_collider.y + p_collider.h * 2.0;

            Vector2 paddle_position = Vector2(paddle_x, paddle_y);
            Vector2 new_direction = Vector2::subtract(position, paddle_position);

            current_velocity += INCREASE_VELOCITY;

            velocity = Vector2::normalize(new_direction);
            velocity = Vector2::multiply(velocity, current_velocity);
        }
        else
        {
            // Do not let ball get stuck inside paddle
            if (position.x < p_collider.x)
            {
                new_position = Vector2(p_collider.x - RADIUS, new_position.y);
                set_position(new_position);

                // Do not let ball get stuck inside wall
                if (Physics::is_collision(collider, walls.get_left()))
                {
                    new_position = Vector2(p_collider.x + RADIUS, p_collider.y + p_collider.h + RADIUS);
                    set_position(new_position);
                }
            }
            else
            {
                new_position = Vector2(p_collider.x + p_collider.w + RADIUS, new_position.y);
                set_position(new_position);

                if (Physics::is_collision(collider, walls.get_right()))
                {
                    new_position = Vector2(p_collider.x + p_collider.w - RADIUS, p_collider.y + p_collider.h + RADIUS);
                    set_position(new_position);
                }
            }

            double paddle_x = p_collider.x + p_collider.w * 0.5;
            double paddle_y = p_collider.y + p_collider.h * -2.0;

            Vector2 paddle_position = Vector2(paddle_x, paddle_y);
            Vector2 new_direction = Vector2::subtract(position, paddle_position);

            velocity = Vector2::normalize(new_direction);

            double paddle_magnitude = Vector2::magnitude(paddle.get_velocity());
            double ball_magnitude = Vector2::magnitude(velocity);

            if (paddle_magnitude > ball_magnitude)
            {
                velocity = Vector2::multiply(velocity, paddle_magnitude * 1.5);
            }
            else
            {
                velocity = Vector2::multiply(velocity, ball_magnitude);
            }

        }
    }
}

void Ball::render(SDL_Renderer* renderer, double elapsed_time)
{
    if (is_reset)
    {
        int offset_x = (int)round(position.x - reset_texture.get_width() / 2.0);
        int offset_y = (int)round(position.y - reset_texture.get_height() / 2.0);

        reset_texture.render(renderer, offset_x, offset_y);
        return;
    }

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
    reset_texture.free();

    TTF_CloseFont(reset_font);
    reset_font = NULL;
}

void Ball::reset()
{
    is_reset = true;
    reset_time = SDL_GetTicks64();

    set_position(start_position);
    current_velocity = START_VELOCITY;
    velocity = Vector2(0.0, current_velocity);
}
