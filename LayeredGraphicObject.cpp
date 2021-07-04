#include "LayeredGraphicObject.h"

#include <rapidjson/document.h>

#include "FileManager.h"

LayeredGraphicObject::LayeredGraphicObject(const std::string& _layerFile, const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
	: WorldObject(_x, _y, _tileWidth, _tileHeight, _width, _height, _layer)
{
	auto* layerJson = FileManager::GetTextFile(_layerFile + ".json");
	
	rapidjson::Document layerDoc;
	layerDoc.Parse(layerJson);

	const auto& layers = layerDoc["layers"];
	assert(layers.IsArray());
	for (rapidjson::SizeType i = 0; i < layers.Size(); i++)
	{
		m_layers.push_back(new GraphicLayer(layers[i]));
	}

#ifdef _DEBUG
	printf(">> Layered Graphic Object Created\n");
#endif
}

LayeredGraphicObject::~LayeredGraphicObject()
{
	for (auto& layer : m_layers)
	{
		delete layer;
	}
	m_layers.clear();
	
#ifdef _DEBUG
	printf(">> Layered Graphic Object Unloaded\n");
#endif
}

bool LayeredGraphicObject::Update()
{
	for (auto& layer : m_layers)
	{
		layer->Update();
	}

	return true;
}

void LayeredGraphicObject::Draw(SDL_Renderer* _renderer) const
{
	for (auto& layer : m_layers)
	{
		layer->Draw(_renderer, static_cast<int>(m_X), static_cast<int>(m_Y));
	}
}

GraphicLayer* LayeredGraphicObject::GetGraphicLayer(const int _layer)
{
	return m_layers[_layer];
}
