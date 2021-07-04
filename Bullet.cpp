#include "Bullet.h"

#include "AudioManager.h"
#include "Time.h"

#include "EntityHandler.h"
#include "LivingEntity.h"

#include "Spritesheet.h"
#include "SingleGraphicObject.h"
#include "Effect.h"

Bullet::Bullet(WorldObject* _graphicObject, FMOD::Studio::EventDescription* _explosionSound, const float _xSpeed, const float _ySpeed, const float _falloff, const CollisionLayer _targetLayer, const int _damage, SDL_Rect& _hitbox, const CollisionLayer _collisionLayer, const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
	: Entity(_graphicObject, _hitbox, _collisionLayer, _x, _y, _tileWidth, _tileHeight, _width, _height, _layer)
{
	m_xSpeed = _xSpeed;
	m_ySpeed = _ySpeed;

	m_originalXSpeed = _xSpeed;
	m_originalYSpeed = _ySpeed;

	m_falloffRate = _falloff;
	m_currentFalloff = 1.0f;

	m_targetLayer = _targetLayer;
	m_damage = _damage;

	m_explosionSound = _explosionSound;

#ifdef _DEBUG
	printf(">> Bullet Loaded\n");
#endif
}

bool Bullet::Update()
{
	const float deltaTime = Time::GetInstance()->GetDeltaTime();
	
	SetX(GetX() + m_xSpeed * deltaTime);
	SetY(GetY() + m_ySpeed * deltaTime);

	for(auto& entity : m_entityHandler->GetEntities())
	{
		if(entity->GetCollisionLayer() != m_targetLayer || dynamic_cast<LivingEntity*>(entity) == nullptr || !CheckCollision(entity))
		{
			continue;
		}

		LivingEntity* target = dynamic_cast<LivingEntity*>(entity);
		target->Damage(m_damage, this);

		SpawnExplosion();
		Kill();
		return true;
	}

	if (
		GetX() + static_cast<float>(m_hitboxX) < c_bulletBounds.x ||
		GetX() + static_cast<float>(m_hitboxX + m_hitboxWidth) > c_bulletBounds.w ||
		GetY() + static_cast<float>(m_hitboxY) < c_bulletBounds.y ||
		GetY() + static_cast<float>(m_hitboxY + m_hitboxHeight) > c_bulletBounds.h)
	{
		Kill();
		return true;
	}
	
	m_currentFalloff -= m_falloffRate * deltaTime;
	m_xSpeed = m_originalXSpeed * m_currentFalloff;
	m_ySpeed = m_originalYSpeed * m_currentFalloff;

	if(m_currentFalloff <= c_minimumFalloff)
	{
		SpawnExplosion();
		Kill();
		return true;
	}
	
	return Entity::Update();
}

void Bullet::SpawnExplosion() const
{
	auto* sound = AudioManager::CreateEventInstance(m_explosionSound);
	sound->start();
	sound->release();
	
	Spritesheet* bulletSprite = new Spritesheet("Assets/Graphics/Overworld/bullet_explosion");
	WorldObject* bulletGraphic = new SingleGraphicObject(bulletSprite, m_X + c_explosionOffsetX, m_Y + c_explosionOffsetY, m_tileWidth, m_tileHeight);

	m_entityHandler->AddEntity(new Effect(bulletGraphic, c_explosionLifetime, m_X + c_explosionOffsetX, m_Y + c_explosionOffsetY, m_tileWidth, m_tileHeight));
}