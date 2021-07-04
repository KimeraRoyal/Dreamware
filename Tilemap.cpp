#include "Tilemap.h"

#include <tileson.h>

#include "FileManager.h"

Tilemap::Tilemap(const std::string& _fileName)
{
	Load(_fileName.c_str());
}

void Tilemap::Load(const char* _fileName)
{
	//TODO: Implement LZMA compression on Tiled files
	
	size_t tilemapSize;
	char* tilemapData = FileManager::ReadTextFile(_fileName, &tilemapSize);
	
	tson::Tileson t;
	auto map = t.parse(tilemapData, tilemapSize);

	if(map->getStatus() == tson::ParseStatus::OK)
	{
		m_width = map->getSize().x;
		m_height = map->getSize().y;
		m_tileWidth = map->getTileSize().x;
		m_tileHeight = map->getTileSize().y;

		for(auto& tileset : map->getTilesets())
		{
			auto* tilesetTexture = FileManager::GetTexture(FileManager::GetInstance()->GetRelativePath("Assets/Maps/" + tileset.getImagePath().generic_string()));
			m_tilesets.insert(std::pair<int, SDL_Texture*>(tileset.getFirstgid(), tilesetTexture));

#ifdef _DEBUG
			printf(">>> Found Tileset\n");
#endif
		}

		for(auto& layer : map->getLayers())
		{
			switch(layer.getType())
			{
				case tson::LayerType::TileLayer:
				{
					for (int y = 0; y < m_height; y++)
					{
						for (int x = 0; x < m_width; x++)
						{
							auto* tile = layer.getTileData(x, y);

							const auto tileGid = tile->getGid() - 1;
							if (tileGid == 0)
							{
								continue;
							}

							auto* tileTileset = tile->getTileset();
							if (tileTileset == nullptr)
							{
								continue;
							}

							const auto textureX = (tileGid % (tileTileset->getImageSize().x / m_tileWidth)) * m_tileWidth;
							const auto textureY = (tileGid / (tileTileset->getImageSize().x / m_tileWidth)) * m_tileWidth;

							const auto worldX = x * m_tileWidth;
							const auto worldY = y * m_tileHeight;

							Tile tileObject(m_tilesets[tileTileset->getFirstgid()], worldX, worldY, textureX, textureY, m_tileWidth, m_tileHeight, 0);
							m_tiles.push_back(tileObject);
						}
					}
					break;
				}
				case tson::LayerType::ObjectGroup:
				case tson::LayerType::ImageLayer:
				case tson::LayerType::Group:
				case tson::LayerType::Undefined:
				{
					printf("Unsupported Layer Type.\n");
					break;
				}
			}
		}
	}
	else
	{
		std::cout << map->getStatusMessage();
		
		free(tilemapData);
		exit(-1);
	}

	free(tilemapData);

#ifdef _DEBUG
	printf(">> Tilemap Loaded\n");
#endif
}

void Tilemap::Load(const std::string& _fileName)
{
	Load(_fileName.c_str());
}

void Tilemap::Draw(SDL_Renderer* _renderer, const int _offsetX, const int _offsetY)
{
	for(auto& tile : m_tiles)
	{
		tile.Draw(_renderer, _offsetX, _offsetY);
	}
}

void Tilemap::Update()
{
	// Static tilemaps have no update functionality
}

int Tilemap::GetWidth() const
{
	return m_width;
}

int Tilemap::GetHeight() const
{
	return m_height;
}

int Tilemap::GetTileWidth() const
{
	return m_tileWidth;
}

int Tilemap::GetTileHeight() const
{
	return m_tileHeight;
}
