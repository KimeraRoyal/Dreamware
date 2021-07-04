#pragma once

#include "Entity.h"

class LivingEntity : public Entity
{
private:
	static constexpr int c_sparkLifetime = 55;
	
	void CheckHealth(Entity* _source = nullptr);
protected:
	int m_maxHealth = 0;
	int m_currentHealth = 0;

	void SpawnSpark(Entity* _source = nullptr) const;
public:
	explicit LivingEntity(WorldObject* _graphicObject, SDL_Rect& _hitbox, CollisionLayer _collisionLayer, int _health, float _x = 0, float _y = 0, int _tileWidth = 16, int _tileHeight = 16, float _width = 1, float _height = 1, int _layer = 0);
	
	[[nodiscard]] int GetMaxHealth() const;
	[[nodiscard]] int GetCurrentHealth() const;

	void SetMaxHealth(int _health, bool _heal = true);
	void SetCurrentHealth(int _health, Entity* _source = nullptr);

	virtual void Damage(int _amount, Entity* _source = nullptr);
	virtual void Heal(int _amount, Entity* _source = nullptr);
};

