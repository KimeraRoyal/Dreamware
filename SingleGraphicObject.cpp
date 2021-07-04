#include "SingleGraphicObject.h"

SingleGraphicObject::SingleGraphicObject(ISprite* _sprite, const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
	: WorldObject(_x, _y, _tileWidth, _tileHeight, _width, _height, _layer)
{
	m_sprite = _sprite;

#ifdef _DEBUG
	printf(">> Single Graphic Object Created\n");
#endif
}

SingleGraphicObject::~SingleGraphicObject()
{
	delete m_sprite;
	m_sprite = nullptr;

#ifdef _DEBUG
	printf(">> Single Graphic Object Unloaded\n");
#endif
}

bool SingleGraphicObject::Update()
{
	m_sprite->Update();

	return true;
}

void SingleGraphicObject::Draw(SDL_Renderer* _renderer) const
{
	m_sprite->Draw(_renderer, static_cast<int>(m_X), static_cast<int>(m_Y));
}
