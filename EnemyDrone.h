#pragma once

#include "Enemy.h"

#include "LayeredGraphicObject.h"

class EnemyDrone final : public Enemy
{
private:
	static constexpr int c_gunLayer = 0;

	static constexpr float c_movementSpeed = 16.0f;

	static constexpr int c_fireFrames = 90;
	static constexpr int c_stationaryFireFrames = 50;

	static constexpr float c_bulletOffsetX = 12;
	static constexpr float c_bulletOffsetY = 16;
	static constexpr float c_bulletSpeed = 80;
	static constexpr float c_bulletFalloff = 0.1f;
	
	LayeredGraphicObject* m_enemyGraphic = nullptr;

	DiagonalDirection m_gunDirection = DiagonalDirection::down;
	DiagonalDirection m_lastGunDirection = DiagonalDirection::down;

	int m_fireDelay = 0;
	int m_rotationTimer = 0;

	float m_targetX = 0;
	float m_targetY = 0;

	void Move();
public:
	explicit EnemyDrone(SDL_Rect& _hitbox, FMOD::Studio::EventDescription* _fireSound, FMOD::Studio::EventDescription* _hurtSound, FMOD::Studio::EventDescription* _deathSound, FMOD::Studio::EventDescription* _bulletExplosionSound, int _health, int _damage, float _targetX, float _targetY, float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);

	bool Update() override;
	void Draw(SDL_Renderer* _renderer) const override;
};

