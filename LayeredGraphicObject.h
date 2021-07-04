#pragma once

#include <vector>

#include "WorldObject.h"
#include "GraphicLayer.h"

class LayeredGraphicObject : public WorldObject
{
private:
	std::vector<GraphicLayer*> m_layers;

public:
	explicit LayeredGraphicObject(const std::string& _layerFile, float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);
	~LayeredGraphicObject() override;

	bool Update() override;
	void Draw(SDL_Renderer* _renderer) const override;

	GraphicLayer* GetGraphicLayer(int _layer);
};

