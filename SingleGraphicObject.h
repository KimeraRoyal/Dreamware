#pragma once

#include "WorldObject.h"
#include "ISprite.h"

class SingleGraphicObject : public WorldObject
{
private:
	ISprite* m_sprite = nullptr;
	
public:
	explicit SingleGraphicObject(ISprite* _sprite, float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);
	~SingleGraphicObject() override;
	
	bool Update() override;
	void Draw(SDL_Renderer* _renderer) const override;
};

