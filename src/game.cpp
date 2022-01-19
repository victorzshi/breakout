#include <stdio.h>

#include "game.h"

Game::Game()
{
	#ifdef _DEBUG
		start_time = 0;
		frame_total = 0;
		update_total = 0;

		debug_font = TTF_OpenFont("assets/fonts/PressStart2P-Regular.ttf", 8);
		if (debug_font == NULL)
		{
			printf("Failed to load debug font! SDL_ttf Error: %s\n", TTF_GetError());
			throw;
		}

		debug_font_color = {0, 255, 0};
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

	game_over_font = TTF_OpenFont("assets/fonts/PressStart2P-Regular.ttf", 16);
	if (game_over_font == NULL)
	{
		printf("Failed to load game over font! SDL_ttf Error: %s\n", TTF_GetError());
		throw;
	}

	game_over_font_color = { 0, 255, 0 };
}

void Game::start()
{
	#ifdef _DEBUG
		start_time = (int)SDL_GetTicks64();
	#endif

	is_running = true;

	score.set_position(Vector2(SCREEN_WIDTH * 0.5, 25.0));
	walls.set_dimensions(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100);
	bricks.set_dimensions(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.2, 300, 30);
	paddle.set_position(Vector2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.8));
	ball.set_position(Vector2(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5));

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
		
		TTF_CloseFont(debug_font);
		debug_font = NULL;
	#endif

	game_over_texture.free();
	TTF_CloseFont(game_over_font);
	game_over_font = NULL;

	ball.free();
	paddle.free();
	bricks.free();
	walls.free();
	score.free();
	audio.free();

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

		if (!score.get_is_game_over())
		{
			paddle.process_input(event);
		}
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

		frames_per_second_texture.load_text(renderer, debug_font, frame_text.str().c_str(), debug_font_color);
		updates_per_second_texture.load_text(renderer, debug_font, update_text.str().c_str(), debug_font_color);

		++update_total;
	#endif

	if (!score.get_is_game_over())
	{
		score.update(renderer);
		bricks.update(score);
		paddle.update(walls);
		ball.update(renderer, audio, score, walls, bricks, paddle);
	}
	else
	{
		int total_score = score.get_total_score();
		int max_score = score.get_max_score(bricks.get_total_bricks());
		int score_difference = max_score - total_score;

		game_over_text.str("");
		SDL_Color color;
		if (score_difference == 0)
		{
			game_over_text << "Not bad... you had a perfect game! Thanks for playing - Victor";
			color = { 255, 255, 0 };
			audio.play_flawless_victory();
		}
		else if (score_difference <= max_score * 0.3)
		{
			game_over_text << "Nice! " << score_difference << " points away from a perfect score...";
			color = { 0, 255, 0 };
			audio.play_winner();
		}
		else if (score_difference <= max_score * 0.6)
		{
			game_over_text << "Not bad. " << score_difference << " points away from a perfect score...";
			color = { 0, 0, 255 };
			audio.play_you_win();
		}
		else
		{
			game_over_text << "You can do better?";
			color = { 255, 255, 255 };
			audio.play_game_over();
		}

		game_over_texture.load_text(renderer, game_over_font, game_over_text.str().c_str(), color);
	}
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

	if (!score.get_is_game_over())
	{
		score.render(renderer);
		walls.render(renderer);
		bricks.render(renderer);
		paddle.render(renderer, elapsed_time);
		ball.render(renderer, elapsed_time);
	}
	else
	{
		score.render(renderer);
		walls.render(renderer);

		int offset_x = (int)round(SCREEN_WIDTH / 2.0 - game_over_texture.get_width() / 2.0);
		int offset_y = (int)round(SCREEN_HEIGHT / 2.0 - game_over_texture.get_height() / 2.0);

		game_over_texture.render(renderer, offset_x, offset_y);
	}

	SDL_RenderPresent(renderer);
}
