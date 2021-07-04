#include "LivingEntity.h"

#include <string>

#include "Effect.h"
#include "SingleGraphicObject.h"
#include "Spritesheet.h"

LivingEntity::LivingEntity(WorldObject* _graphicObject, SDL_Rect& _hitbox, const CollisionLayer _collisionLayer, const int _health, const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
	: Entity(_graphicObject, _hitbox, _collisionLayer, _x, _y, _tileWidth, _tileHeight, _width, _height, _layer)
{
	SetMaxHealth(_health);
}

void LivingEntity::CheckHealth(Entity* _source)
{
	if (m_currentHealth <= 0)
	{
		Kill(_source);
	}
	else if (m_currentHealth > m_maxHealth)
	{
		m_currentHealth = m_maxHealth;
	}
}

void LivingEntity::SpawnSpark(Entity* _source) const
{
	std::string spritesheetName = "Assets/Graphics/Overworld/hit_spark";
	float offset = 0;

	if(_source != nullptr)
	{
		const float sourceX = _source->GetX() + static_cast<float>(_source->GetHitboxX()) + static_cast<float>(_source->GetHitboxWidth()) / 2;
		const float targetX = GetX() + static_cast<float>(GetHitboxX()) + static_cast<float>(GetHitboxWidth()) / 2;
		if (sourceX < targetX)
		{
			spritesheetName += "_right";
			offset = 24;
		}
	}

	Spritesheet* bulletSprite = new Spritesheet(spritesheetName);
	WorldObject* bulletGraphic = new SingleGraphicObject(bulletSprite, m_X + offset, m_Y - 8, m_tileWidth, m_tileHeight);

	m_entityHandler->AddEntity(new Effect(bulletGraphic, c_sparkLifetime, m_X + offset, m_Y - 8, m_tileWidth, m_tileHeight));
}

int LivingEntity::GetMaxHealth() const
{
	return m_maxHealth;
}

int LivingEntity::GetCurrentHealth() const
{
	return m_currentHealth;
}

void LivingEntity::SetMaxHealth(const int _health, const bool _heal)
{
	m_maxHealth = _health;
	if (m_maxHealth < m_currentHealth || _heal)
	{
		SetCurrentHealth(_health);
	}
}

void LivingEntity::SetCurrentHealth(const int _health, Entity* _source)
{
	m_currentHealth = _health;
	CheckHealth(_source);
}

void LivingEntity::Damage(const int _amount, Entity* _source)
{
	SpawnSpark(_source);
	SetCurrentHealth(m_currentHealth - _amount, _source);
}

void LivingEntity::Heal(const int _amount, Entity* _source)
{
	SetCurrentHealth(m_currentHealth + _amount, _source);
}