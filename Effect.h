#pragma once

#include "Entity.h"

class Effect final : public Entity
{
private:
	int m_totalLifetime = 0;
	int m_currentLifetime = 0;
public:
	explicit Effect(WorldObject* _graphicObject, int _lifetime, float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);

	bool Update() override;
};

