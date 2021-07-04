#pragma once

#include <SDL.h>

class Tile
{
private:
	SDL_Texture* m_texture = nullptr;
	
	SDL_Rect m_sourceRect{};
	SDL_Rect m_destinationRect{};

	int m_layer = 0;
public:
	Tile(SDL_Texture* _texture, int _x, int _y, int _tilesetX, int _tilesetY, int _width, int _height, int _layer);

	void Draw(SDL_Renderer* _renderer, int _offsetX = 0, int _offsetY = 0) const;

	[[nodiscard]] int GetX() const;
	[[nodiscard]] int GetY() const;

	[[nodiscard]] int GetTilesetX() const;
	[[nodiscard]] int GetTilesetY() const;

	[[nodiscard]] int GetWidth() const;
	[[nodiscard]] int GetHeight() const;
};

