#pragma once

#include <SDL_mixer.h>

class Audio
{
public:
	Audio();

	void play_beeep();

	void play_peeeeeep();

	void play_plop();

	void play_death();

	void play_flawless_victory();

	void play_winner();

	void play_you_win();

	void play_game_over();

	void free();

private:
	bool is_game_over;

	Mix_Chunk* beeep;
	Mix_Chunk* peeeeeep;
	Mix_Chunk* plop;
	Mix_Chunk* death;
	Mix_Chunk* flawless_victory;
	Mix_Chunk* winner;
	Mix_Chunk* you_win;
	Mix_Chunk* game_over;
};
