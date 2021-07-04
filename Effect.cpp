#include "Effect.h"

Effect::Effect(WorldObject* _graphicObject, const int _lifetime, const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
	: Entity(_graphicObject, 0, 0, 0, 0, CollisionLayer::none, _x, _y, _tileWidth, _tileHeight, _width, _height, _layer)
{
	m_totalLifetime = _lifetime;
	m_currentLifetime = 0;

#ifdef _DEBUG
	printf(">> Effect Loaded\n");
#endif
}

bool Effect::Update()
{
	m_currentLifetime++;

	if(m_currentLifetime >= m_totalLifetime)
	{
		m_entityHandler->RemoveEntity(this);
		return true;
	}
	
	return Entity::Update();
}
