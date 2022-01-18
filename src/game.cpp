#include <stdio.h>

#include "game.h"

Game::Game()
{
	#ifdef _DEBUG
		start_time = 0;
		frame_total = 0;
		update_total = 0;
	#endif

	is_running = false;

	window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL error: %s\n", SDL_GetError());
		throw;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		throw;
	}
	
	font = TTF_OpenFont("assets/fonts/PressStart2P-Regular.ttf", 8);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		throw;
	}
}

void Game::start()
{
	#ifdef _DEBUG
		start_time = (int)SDL_GetTicks64();
	#endif

	is_running = true;

	walls.set_dimensions(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100);
	bricks.set_dimensions(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.2, 300, 30);
	paddle.set_position(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.8);
	ball.set_position(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5);

	double previous = (double)SDL_GetTicks64();
	double lag = 0.0;

	while (is_running)
	{
		double current = (double)SDL_GetTicks64();
		double elapsed = current - previous;
		previous = current;
		lag += elapsed;

		process_input();

		while (lag >= MS_PER_UPDATE)
		{
			update();
			lag -= MS_PER_UPDATE;
		}

		render(lag / MS_PER_UPDATE);
	}
}

void Game::free()
{
	#ifdef _DEBUG
		frames_per_second_texture.free();
		updates_per_second_texture.free();
	#endif

	ball.free();
	paddle.free();
	bricks.free();
	walls.free();

	TTF_CloseFont(font);
	font = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
}

void Game::process_input()
{
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			is_running = false;
		}

		paddle.process_input(event);
	}
}

void Game::update()
{
	#ifdef _DEBUG
		double total_time = (SDL_GetTicks64() - start_time) / 1000.0;

		double average_frames_per_second = frame_total / total_time;
		frame_text.str("");
		frame_text << "Average Frames Per Second " << average_frames_per_second;

		double average_updates_per_second = update_total / total_time;
		update_text.str("");
		update_text << "Average Updates Per Second " << average_updates_per_second;

		SDL_Color green = { 0, 255, 0 };

		frames_per_second_texture.load_text(renderer, font, frame_text.str().c_str(), green);
		updates_per_second_texture.load_text(renderer, font, update_text.str().c_str(), green);

		++update_total;
	#endif

	paddle.update(walls);
	ball.update(walls, bricks, paddle);
}

void Game::render(double elapsed_time)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	#ifdef _DEBUG
		frames_per_second_texture.render(renderer, 0, 0);
		updates_per_second_texture.render(renderer, 0, frames_per_second_texture.get_height());

		++frame_total;
	#endif

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	walls.render(renderer);
	bricks.render(renderer);
	paddle.render(renderer, elapsed_time);
	ball.render(renderer, elapsed_time);

	SDL_RenderPresent(renderer);
}
