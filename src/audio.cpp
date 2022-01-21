#include <stdio.h>

#include "audio.h"

Audio::Audio()
{
    is_game_over = false;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		throw;
	}

    beeep = Mix_LoadWAV("data/sounds/sounds_ping_pong_8bit/ping_pong_8bit_beeep.ogg");
    if (beeep == NULL)
    {
        printf("Failed to load beeep sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    peeeeeep = Mix_LoadWAV("data/sounds/sounds_ping_pong_8bit/ping_pong_8bit_peeeeeep.ogg");
    if (peeeeeep == NULL)
    {
        printf("Failed to load peeeeeep sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    plop = Mix_LoadWAV("data/sounds/sounds_ping_pong_8bit/ping_pong_8bit_plop.ogg");
    if (plop == NULL)
    {
        printf("Failed to load plop sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    death = Mix_LoadWAV("data/sounds/8bit Death Whirl/vgdeathsound.ogg");
    if (death == NULL)
    {
        printf("Failed to load death sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    flawless_victory = Mix_LoadWAV("data/sounds/Voiceover Pack Fighter/flawless_victory.ogg");
    if (flawless_victory == NULL)
    {
        printf("Failed to load flawless_victory sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    winner = Mix_LoadWAV("data/sounds/Voiceover Pack Fighter/winner.ogg");
    if (winner == NULL)
    {
        printf("Failed to load winner sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    you_win = Mix_LoadWAV("data/sounds/Voiceover Pack Fighter/you_win.ogg");
    if (you_win == NULL)
    {
        printf("Failed to load you_win sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }

    game_over = Mix_LoadWAV("data/sounds/Voiceover Pack Fighter/game_over.ogg");
    if (game_over == NULL)
    {
        printf("Failed to load game_over sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void Audio::play_beeep()
{
    Mix_PlayChannel(-1, beeep, 0);
}

void Audio::play_peeeeeep()
{
    Mix_PlayChannel(-1, peeeeeep, 0);
}

void Audio::play_plop()
{
    Mix_PlayChannel(-1, plop, 0);
}

void Audio::play_death()
{
    Mix_PlayChannel(-1, death, 0);
}

void Audio::play_flawless_victory()
{
    if (!is_game_over)
    {
        Mix_PlayChannel(-1, flawless_victory, 0);
        is_game_over = true;
    }
}

void Audio::play_winner()
{
    if (!is_game_over)
    {
        Mix_PlayChannel(-1, winner, 0);
        is_game_over = true;
    }
}

void Audio::play_you_win()
{
    if (!is_game_over)
    {
        Mix_PlayChannel(-1, you_win, 0);
        is_game_over = true;
    }
}

void Audio::play_game_over()
{
    if (!is_game_over)
    {
        Mix_PlayChannel(-1, game_over, 0);
        is_game_over = true;
    }
}

void Audio::free()
{
    Mix_FreeChunk(beeep);
    beeep = NULL;

    Mix_FreeChunk(peeeeeep);
    peeeeeep = NULL;

    Mix_FreeChunk(plop);
    plop = NULL;

    Mix_FreeChunk(death);
    death = NULL;

    Mix_FreeChunk(flawless_victory);
    flawless_victory = NULL;

    Mix_FreeChunk(winner);
    winner = NULL;

    Mix_FreeChunk(you_win);
    you_win = NULL;

    Mix_FreeChunk(game_over);
    game_over = NULL;
}
