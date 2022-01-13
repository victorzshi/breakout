#include <stdio.h>

#include "game.h"

Game::Game()
{
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
	else
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}
	
	font = TTF_OpenFont("assets/fonts/PressStart2P-Regular.ttf", 16);
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		throw;
	}

	is_running = true;
	start_time = 0;
	frame_total = 0;
}

void Game::start()
{
	start_time = SDL_GetTicks64();

	int previous = SDL_GetTicks64();
	int lag = 0;

	while (is_running)
	{
		int current = SDL_GetTicks64();
		int elapsed = current - previous;
		previous = current;
		lag += elapsed;

		process_input();

		while (lag >= MS_PER_UPDATE)
		{
			update();
			lag -= MS_PER_UPDATE;
		}

		render(lag / MS_PER_UPDATE);

		++frame_total;
	}
}

void Game::free()
{
	texture.free();

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
	}
}

void Game::update()
{
	double total_time = (SDL_GetTicks64() - start_time) / 1000.0;
	double average_fps = frame_total / total_time;

	frame_text.str("");
	frame_text << "Average Frames Per Second " << average_fps;

	SDL_Color color = { 255, 255, 255 };

	texture.load_text(renderer, font, frame_text.str().c_str(), color);
}

void Game::render(int elapsed_time)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	texture.render(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	SDL_RenderPresent(renderer);
}
