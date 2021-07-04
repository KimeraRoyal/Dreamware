#pragma once

#include "Entity.h"

#include <fmod_studio.hpp>

class EnemySpawner final : public Entity
{
private:
	
	static constexpr SDL_Rect c_spawnBounds = { -64, -64, 544, 416 };
	static constexpr SDL_Rect c_targetBounds = { 80, 80, 400, 272 };
	
	FMOD::Studio::EventDescription* m_fireSound = nullptr;
	FMOD::Studio::EventDescription* m_hurtSound = nullptr;
	FMOD::Studio::EventDescription* m_deathSound = nullptr;
	FMOD::Studio::EventDescription* m_bulletExplosionSound = nullptr;

	static constexpr float c_spawnTime = 8.0f;
	static constexpr float c_firstSpawnTime = 4.0f;

	float m_spawnTimer = 0.0f;

	void SpawnEnemy() const;
public:
	explicit EnemySpawner(int _tileWidth = 16, int _tileHeight = 16);
	~EnemySpawner() override;
	
	bool Update() override;
	void Draw(SDL_Renderer* _renderer) const override;
};

