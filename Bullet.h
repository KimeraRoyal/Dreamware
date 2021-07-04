#pragma once

#include "Entity.h"

#include <fmod_studio.hpp>

class EntityHandler;

class Bullet final : public Entity
{
private:
	static constexpr SDL_Rect c_bulletBounds = { -16, -16, 496, 368 };

	static constexpr float c_minimumFalloff = 0.4f;

	static constexpr int c_explosionLifetime = 80;
	static constexpr float c_explosionOffsetX = -4;
	static constexpr float c_explosionOffsetY = -4;

	FMOD::Studio::EventDescription* m_explosionSound = nullptr;
	
	float m_xSpeed = 0.0f;
	float m_ySpeed = 0.0f;
	
	float m_originalXSpeed = 0.0f;
	float m_originalYSpeed = 0.0f;

	float m_falloffRate = 0.0f;
	float m_currentFalloff = 0.0f;

	CollisionLayer m_targetLayer = CollisionLayer::none;
	int m_damage = 1;

	void SpawnExplosion() const;
public:
	explicit Bullet(WorldObject* _graphicObject, FMOD::Studio::EventDescription* _explosionSound, float _xSpeed, float _ySpeed, float _falloff, CollisionLayer _targetLayer, int _damage, SDL_Rect& _hitbox, CollisionLayer _collisionLayer, float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);
	
	bool Update() override;
};

