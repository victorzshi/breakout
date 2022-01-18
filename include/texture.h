#pragma once

#include <string>

#include <SDL.h>

class Texture
{
public:
	Texture();

	void load_text(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color color);

	int get_width();

	int get_height();

	void render(SDL_Renderer* renderer, int x, int y);

	void free();

private:
	static const int WRAP_LENGTH = 300;

	SDL_Texture* texture;

	int width;

	int height;
};
