#include "Enemy.h"

#include "AudioManager.h"

#include "Spritesheet.h"
#include "SingleGraphicObject.h"
#include "Bullet.h"
#include "Game.h"

Enemy::Enemy(WorldObject* _graphicObject, FMOD::Studio::EventDescription* _fireSound, FMOD::Studio::EventDescription* _hurtSound, FMOD::Studio::EventDescription* _deathSound, FMOD::Studio::EventDescription* _bulletExplosionSound, SDL_Rect& _hitbox, const int _health, const int _damage, const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
	: LivingEntity(_graphicObject, _hitbox, CollisionLayer::enemy, _health, _x, _y, _tileWidth, _tileHeight, _width, _height, _layer)
{
	m_damage = _damage;

	m_fireSound = _fireSound;
	m_hurtSound = _hurtSound;
	m_deathSound = _deathSound;
	m_bulletExplosionSound = _bulletExplosionSound;
}

void Enemy::Damage(const int _amount, Entity* _source)
{
	Game::GetInstance()->AddScore(c_scorePerHit);
	
	auto* sound = AudioManager::CreateEventInstance(m_hurtSound);
	sound->start();
	sound->release();
	
	LivingEntity::Damage(_amount, _source);
}

void Enemy::Kill(Entity* _source)
{
	Game::GetInstance()->AddScore(c_scoreValue);
	
	auto* sound = AudioManager::CreateEventInstance(m_deathSound);
	sound->start();
	sound->release();

	LivingEntity::Kill(_source);
}

void Enemy::SpawnBullet(float _xDirection, float _yDirection, const float _speed, const float _fallOff, const float _xOffset, const float _yOffset) const
{
	const double dX = static_cast<double>(_xDirection);
	const double dY = static_cast<double>(_yDirection);
	const float length = static_cast<float>(sqrt(dX * dX + dY * dY));

	_xDirection /= length;
	_yDirection /= length;

	Spritesheet* bulletSprite = new Spritesheet("Assets/Graphics/Overworld/enemy_bullet");
	WorldObject* bulletGraphic = new SingleGraphicObject(bulletSprite, m_X + _xOffset, m_Y + _yOffset, m_tileWidth, m_tileHeight, 0.5f, 0.5f);

	SDL_Rect bulletHitbox = { 0, 0, 8, 8 };
	m_entityHandler->AddEntity(new Bullet(bulletGraphic, m_bulletExplosionSound, _xDirection * _speed, _yDirection * _speed, _fallOff, CollisionLayer::player, m_damage, bulletHitbox, CollisionLayer::bullet, m_X + _xOffset, m_Y + _yOffset, m_tileWidth, m_tileHeight, 0.5f, 0.5f));

	auto* sound = AudioManager::CreateEventInstance(m_fireSound);
	sound->start();
	sound->release();
}