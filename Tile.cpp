#include "Tile.h"

Tile::Tile(SDL_Texture* _texture, const int _x, const int _y, const int _tilesetX, const int _tilesetY, const int _width, const int _height, const int _layer)
{
	m_texture = _texture;
	
	m_sourceRect = { _tilesetX, _tilesetY, _width, _height };
	m_destinationRect = { _x, _y, _width, _height };

	m_layer = _layer;
}

void Tile::Draw(SDL_Renderer* _renderer, const int _offsetX, const int _offsetY) const
{
	auto destinationRect = m_destinationRect;
	destinationRect.x += _offsetX;
	destinationRect.y += _offsetY;
	SDL_RenderCopy(_renderer, m_texture, &m_sourceRect, &destinationRect);
}

int Tile::GetX() const
{
	return m_destinationRect.x;
}

int Tile::GetY() const
{
	return m_destinationRect.y;
}

int Tile::GetTilesetX() const
{
	return m_sourceRect.x;
}

int Tile::GetTilesetY() const
{
	return m_sourceRect.y;
}

int Tile::GetWidth() const
{
	return m_sourceRect.w;
}

int Tile::GetHeight() const
{
	return m_sourceRect.h;
}
