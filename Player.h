#pragma once

#include "LivingEntity.h"

#include <fmod_studio.hpp>

#include "LayeredGraphicObject.h"

class Player final : public LivingEntity
{
private:
	static constexpr int c_scorePerHit = 100;
	
	static constexpr int c_playerBodyLayer = 0;
	static constexpr int c_playerHeadLayer = 1;

	static constexpr SDL_Rect c_movementBounds = { 32, 32, 448, 320 };
	static constexpr float c_walkSpeed = 72;

	static constexpr float c_bulletDelay = 0.4f;
	static constexpr float c_bulletSpeed = 180;
	static constexpr float c_bulletOffsetX = 12;
	static constexpr float c_bulletOffsetY = 16;

	static constexpr float c_playerMovementInfluence = 0.2f;

	FMOD::Studio::EventDescription* m_fireSound = nullptr;
	FMOD::Studio::EventDescription* m_hurtSound = nullptr;
	FMOD::Studio::EventDescription* m_deathSound = nullptr;
	FMOD::Studio::EventDescription* m_bulletExplosionSound = nullptr;

	LayeredGraphicObject* m_playerGraphic = nullptr;
	int m_damage = 1;

	CardinalDirection m_movementDirection = CardinalDirection::down;
	CardinalDirection m_facingDirection = CardinalDirection::down;

	CardinalDirection m_lastMovementDirection = CardinalDirection::up;
	CardinalDirection m_lastFacingDirection = CardinalDirection::up;

	bool m_isMoving = false;
	bool m_wasMoving = false;

	float m_movementX = 0.0f;
	float m_movementY = 0.0f;

	float m_facingX = 0.0f;
	float m_facingY = 0.0f;

	float m_bulletTimer = 0.0f;

	void HandleMovement();
	void HandleFiring();
	void SpawnBullet() const;
public:
	explicit Player(SDL_Rect& _hitbox, int _health, int _damage, float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);
	~Player() override;
	
	bool Update() override;
	void Draw(SDL_Renderer* _renderer) const override;

	void Damage(int _amount, Entity* _source) override;
	void Kill(Entity* _source) override;
};
