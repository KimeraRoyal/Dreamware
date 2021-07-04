#include "Entity.h"

Entity::Entity(WorldObject* _graphicObject, const int _hitboxX, const int _hitboxY, const int _hitboxWidth, const int _hitboxHeight, const CollisionLayer _collisionLayer, const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
	: WorldObject(_x, _y, _tileWidth, _tileHeight, _width, _height, _layer)
{
	m_graphicObject = _graphicObject;

	SetHitboxRect(_hitboxX, _hitboxY, _hitboxWidth, _hitboxHeight);
	m_collisionLayer = _collisionLayer;
}

Entity::Entity(WorldObject* _graphicObject, SDL_Rect& _hitbox, const CollisionLayer _collisionLayer, const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
	: Entity(_graphicObject, _hitbox.x, _hitbox.y, _hitbox.w, _hitbox.h, _collisionLayer, _x, _y, _tileWidth, _tileHeight, _width, _height, _layer)
{ }

Entity::~Entity()
{
	delete m_graphicObject;
}

bool Entity::Update()
{
	m_graphicObject->SetPosition(GetX(), GetY());
	return m_graphicObject->Update();
}

void Entity::Draw(SDL_Renderer* _renderer) const
{
	m_graphicObject->Draw(_renderer);

	if(c_drawHitboxes)
	{
		SDL_SetRenderDrawColor(_renderer, c_hitboxOutlineColor.r, c_hitboxOutlineColor.g, c_hitboxOutlineColor.b, c_hitboxOutlineColor.a);
		SDL_Rect hitboxRect = { static_cast<int>(m_X) + m_hitboxX , static_cast<int>(m_Y) + m_hitboxY, m_hitboxWidth, m_hitboxHeight };
		SDL_RenderDrawRect(_renderer, &hitboxRect);
	}
}

void Entity::Kill(Entity* _source)
{
	m_entityHandler->RemoveEntity(this);
}


int Entity::GetHitboxX() const
{
	return m_hitboxX;
}

int Entity::GetHitboxY() const
{
	return m_hitboxY;
}

int Entity::GetHitboxWidth() const
{
	return m_hitboxWidth;
}

int Entity::GetHitboxHeight() const
{
	return m_hitboxHeight;
}

CollisionLayer Entity::GetCollisionLayer() const
{
	return m_collisionLayer;
}

void Entity::SetEntityHandler(EntityHandler* _entityHandler)
{
	m_entityHandler = _entityHandler;
}

void Entity::SetHitboxX(const int _x)
{
	m_hitboxX = _x;
}

void Entity::SetHitboxY(const int _y)
{
	m_hitboxY = _y;
}

void Entity::SetHitboxPosition(const int _x, const int _y)
{
	SetHitboxX(_x);
	SetHitboxY(_y);
}

void Entity::SetHitboxWidth(const int _width)
{
	m_hitboxWidth = _width;
}

void Entity::SetHitboxHeight(const int _height)
{
	m_hitboxHeight = _height;
}

void Entity::SetHitboxSize(const int _width, const int _height)
{
	SetHitboxWidth(_width);
	SetHitboxHeight(_height);
}

void Entity::SetHitboxRect(const int _x, const int _y, const int _width, const int _height)
{
	SetHitboxPosition(_x, _y);
	SetHitboxSize(_width, _height);
}

void Entity::SetCollisionLayer(const CollisionLayer _collisionLayer)
{
	m_collisionLayer = _collisionLayer;
}

bool Entity::CheckCollision(Entity* _other)
{
	return CheckCollision(this, _other);
}

bool Entity::CheckCollision(Entity* _a, Entity* _b)
{
	const auto aX = _a->GetX() + static_cast<float>(_a->GetHitboxX());
	const auto aY = _a->GetY() + static_cast<float>(_a->GetHitboxY());
	const auto bX = _b->GetX() + static_cast<float>(_b->GetHitboxX());
	const auto bY = _b->GetY() + static_cast<float>(_b->GetHitboxY());
	
	return
		aX + static_cast<float>(_a->GetHitboxWidth()) > bX &&
		aX < bX + static_cast<float>(_b->GetHitboxWidth()) &&
		aY + static_cast<float>(_a->GetHitboxHeight()) > bY &&
		aY < bY + static_cast<float>(_b->GetHitboxHeight());
}

void Entity::GetDirectionVector(const CardinalDirection _direction, float& _outX, float& _outY)
{
	switch(_direction)
	{
		case CardinalDirection::up:
		{
			_outX = 0;
			_outY = -1;
			break;
		}
		case CardinalDirection::left:
		{
			_outX = -1;
			_outY = 0;
			break;
		}
		case CardinalDirection::down:
		{
			_outX = 0;
			_outY = 1;
			break;
		}
		case CardinalDirection::right:
		{
			_outX = 1;
			_outY = 0;
			break;
		}
	}
}

void Entity::GetDirectionVector(const DiagonalDirection _direction, float& _outX, float& _outY)
{
	switch(_direction)
	{
	case DiagonalDirection::up:
	{
		_outX = 0;
		_outY = -1;
		break;
	}
	case DiagonalDirection::top_left:
	{
		_outX = -1;
		_outY = -1;
		break;
	}
	case DiagonalDirection::left:
	{
		_outX = -1;
		_outY = 0;
		break;
	}
	case DiagonalDirection::bottom_left:
	{
		_outX = -1;
		_outY = 1;
		break;
	}
	case DiagonalDirection::down:
	{
		_outX = 0;
		_outY = 1;
		break;
	}
	case DiagonalDirection::bottom_right:
	{
		_outX = 1;
		_outY = 1;
		break;
	}
	case DiagonalDirection::right:
	{
		_outX = 1;
		_outY = 0;
		break;
	}
	case DiagonalDirection::top_right:
	{
		_outX = 1;
		_outY = -1;
		break;
	}
	}
}
