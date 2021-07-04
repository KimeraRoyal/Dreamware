#include "WorldObject.h"

#include <cstdio>

WorldObject::WorldObject(const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
{
	SetTileSize(_tileWidth, _tileHeight);
	SetRect(_x, _y, _width, _height);
	
	SetLayer(_layer);

#ifdef _DEBUG
	printf(">> World Object Created\n");
#endif
}

float WorldObject::GetX() const
{
	return m_X;
}

float WorldObject::GetY() const
{
	return m_Y;
}

int WorldObject::GetTileWidth() const
{
	return m_tileWidth;
}

int WorldObject::GetTileHeight() const
{
	return m_tileHeight;
}

float WorldObject::GetWidth() const
{
	return m_width;
}

float WorldObject::GetHeight() const
{
	return m_height;
}

int WorldObject::GetLayer() const
{
	return m_layer;
}

void WorldObject::SetX(const float _x)
{
	m_X = _x;
}

void WorldObject::SetY(const float _y)
{
	m_Y = _y;
}

void WorldObject::SetPosition(const float _x, const float _y)
{
	SetX(_x);
	SetY(_y);
}

void WorldObject::MoveX(const float _amount)
{
	SetX(GetX() + _amount);
}

void WorldObject::MoveY(const float _amount)
{
	SetY(GetY() + _amount);
}

void WorldObject::Move(const float _xAmount, const float _yAmount)
{
	MoveX(_xAmount);
	MoveY(_yAmount);
}

void WorldObject::SetTile(const int _x, int const _y)
{
	SetPosition(static_cast<float>(_x * m_tileWidth), static_cast<float>(_y * m_tileHeight));
}

void WorldObject::SetTileWidth(const int _width)
{
	m_tileWidth = _width;
}

void WorldObject::SetTileHeight(const int _height)
{
	m_tileHeight = _height;
}

void WorldObject::SetTileSize(const int _width, const int _height)
{
	SetTileWidth(_width);
	SetTileHeight(_height);
}

void WorldObject::SetWidth(const float _width)
{
	m_width = _width;
}

void WorldObject::SetHeight(const float _height)
{
	m_height = _height;
}

void WorldObject::SetSize(const float _width, const float _height)
{
	SetWidth(_width);
	SetHeight(_height);
}

void WorldObject::SetRect(const float _x, const float _y, const float _width, const float _height)
{
	SetPosition(_x, _y);
	SetSize(_width, _height);
}

void WorldObject::SetLayer(const int _layer)
{
	m_layer = _layer;
}
