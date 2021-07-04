#pragma once

#include "WorldObject.h"

#include "EntityHandler.h"

enum class CardinalDirection
{
	up = 0x00,
	left = 0x01,
	down = 0x02,
	right = 0x03
};

enum class DiagonalDirection
{
	up = 0x00,
	top_left = 0x01,
	left = 0x02,
	bottom_left = 0x03,
	down = 0x04,
	bottom_right = 0x05,
	right = 0x06,
	top_right = 0x07
};

enum class CollisionLayer : unsigned short
{
	none = 0x0,
	player = 0x1,
	enemy = 0x2,
	level = 0x4,
	bullet = 0x8,
	all = 0xF
};

class Entity : public WorldObject
{
protected:
	EntityHandler* m_entityHandler = nullptr;

	static constexpr bool c_drawHitboxes = false;
	static constexpr SDL_Color c_hitboxOutlineColor = { 0, 255, 0, 255 };
	
	WorldObject* m_graphicObject;

	int m_hitboxX = 0;
	int m_hitboxY = 0;
	int m_hitboxWidth = 0;
	int m_hitboxHeight = 0;

	CollisionLayer m_collisionLayer = CollisionLayer::none;

	static void GetDirectionVector(CardinalDirection _direction, float& _outX, float& _outY);
	static void GetDirectionVector(DiagonalDirection _direction, float& _outX, float& _outY);
public:
	explicit Entity(WorldObject* _graphicObject, int _hitboxX, int _hitboxY, int _hitboxWidth, int _hitboxHeight, CollisionLayer _collisionLayer, float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);
	explicit Entity(WorldObject* _graphicObject, SDL_Rect& _hitbox, CollisionLayer _collisionLayer, float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);
	~Entity() override;
	
	bool Update() override;
	void Draw(SDL_Renderer* _renderer) const override;

	virtual void Kill(Entity* _source = nullptr);

	[[nodiscard]] int GetHitboxX() const;
	[[nodiscard]] int GetHitboxY() const;
	
	[[nodiscard]] int GetHitboxWidth() const;
	[[nodiscard]] int GetHitboxHeight() const;

	[[nodiscard]] CollisionLayer GetCollisionLayer() const;

	void SetEntityHandler(EntityHandler* _entityHandler);

	void SetHitboxX(int _x);
	void SetHitboxY(int _y);
	void SetHitboxPosition(int _x, int _y);

	void SetHitboxWidth(int _width);
	void SetHitboxHeight(int _height);
	void SetHitboxSize(int _width, int _height);

	void SetHitboxRect(int _x, int _y, int _width, int _height);

	void SetCollisionLayer(CollisionLayer _collisionLayer);

	bool CheckCollision(Entity* _other);

	static bool CheckCollision(Entity* _a, Entity* _b);
};