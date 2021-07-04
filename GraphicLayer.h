#pragma once

#include <rapidjson/document.h>

#include "ISprite.h"

struct GraphicLayer
{
private:
	ISprite* m_sprite = nullptr;

	int m_offsetX = 0;
	int m_offsetY = 0;

public:
	GraphicLayer(const rapidjson::Value& _layer);
	GraphicLayer(ISprite* _sprite, int _offsetX = 0, int _offsetY = 0);
	~GraphicLayer();

	void Update() const;
	void Draw(SDL_Renderer* _renderer, int _x = 0, int _y = 0) const;

	ISprite* GetSprite() const;
};

