#include "GraphicLayer.h"

#include "Sprite.h"
#include "Spritesheet.h"

GraphicLayer::GraphicLayer(const rapidjson::Value& _layer)
{
	const std::string textureName = _layer["texture"].GetString();
	const std::string spriteType = _layer["type"].GetString();

	if (spriteType == "sprite")
	{
		m_sprite = new Sprite(textureName);
	}
	else if (spriteType == "spritesheet")
	{
		m_sprite = new Spritesheet(textureName);
	}

	m_offsetX = _layer["x"].GetInt();
	m_offsetY = _layer["y"].GetInt();
}

GraphicLayer::GraphicLayer(ISprite* _sprite, const int _offsetX, const int _offsetY)
{
	m_sprite = _sprite;

	m_offsetX = _offsetX;
	m_offsetY = _offsetY;
}

GraphicLayer::~GraphicLayer()
{
	delete m_sprite;
	m_sprite = nullptr;
}

void GraphicLayer::Update() const
{
	m_sprite->Update();
}

void GraphicLayer::Draw(SDL_Renderer* _renderer, const int _x, const int _y) const
{
	m_sprite->Draw(_renderer, _x + m_offsetX, _y + m_offsetY);
}

ISprite* GraphicLayer::GetSprite() const
{
	return m_sprite;
}
