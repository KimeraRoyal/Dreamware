#pragma once

#include "LivingEntity.h"

#include <fmod_studio.hpp>

class Enemy : public LivingEntity
{
private:
	FMOD::Studio::EventDescription* m_fireSound = nullptr;
	FMOD::Studio::EventDescription* m_hurtSound = nullptr;
	FMOD::Studio::EventDescription* m_deathSound = nullptr;
	FMOD::Studio::EventDescription* m_bulletExplosionSound = nullptr;
	
	static constexpr int c_scorePerHit = 50;
	static constexpr int c_scoreValue = 200;
protected:
	int m_damage = 1;

	void SpawnBullet(float _xDirection, float _yDirection, float _speed, float _fallOff = 0, float _xOffset = 0, float _yOffset = 0) const;
public:
	explicit Enemy(WorldObject* _graphicObject, FMOD::Studio::EventDescription* _fireSound, FMOD::Studio::EventDescription* _hurtSound, FMOD::Studio::EventDescription* _deathSound, FMOD::Studio::EventDescription* _bulletExplosionSound, SDL_Rect& _hitbox, int _health, int _damage, float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);
	
	void Damage(int _amount, Entity* _source) override;
	void Kill(Entity* _source) override;
};

