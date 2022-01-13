#include <SDL_ttf.h>

#include "texture.h"

Texture::Texture()
{
	texture = NULL;

	width = 0;
	height = 0;
}

void Texture::load_text(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color color)
{
	free();

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		throw;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		throw;
	}

	width = surface->w;
	height = surface->h;

	SDL_FreeSurface(surface);
}

int Texture::get_width()
{
	return width;
}

int Texture::get_height()
{
	return height;
}

void Texture::render(SDL_Renderer* renderer, int x, int y)
{
	SDL_Rect render_target = { x, y, width, height};

	SDL_RenderCopy(renderer, texture, NULL, &render_target);
}

void Texture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}
