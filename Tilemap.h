#pragma once

#include <map>
#include <vector>
#include <string>

#include "IGraphic.h"
#include "Tile.h"

class Tilemap final : public IGraphic
{
private:
	std::map<int, SDL_Texture*> m_tilesets;
	
	std::vector<Tile> m_tiles;

	int m_width = 0;
	int m_height = 0;
	int m_tileWidth = 0;
	int m_tileHeight = 0;
public:
	Tilemap() = default;
	explicit Tilemap(const std::string& _fileName);
	
	void Load(const char* _fileName);
	void Load(const std::string& _fileName);
	void Draw(SDL_Renderer* _renderer, int _offsetX = 0, int _offsetY = 0) override;
	void Update() override;

	[[nodiscard]] int GetWidth() const;
	[[nodiscard]] int GetHeight() const;

	[[nodiscard]] int GetTileWidth() const;
	[[nodiscard]] int GetTileHeight() const;
};

