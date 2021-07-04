#include "EnemySpawner.h"

#include "AudioManager.h"

#include "EnemyDrone.h"
#include "Time.h"

EnemySpawner::EnemySpawner(const int _tileWidth, const int _tileHeight)
	: Entity(nullptr, 0, 0, 0, 0, CollisionLayer::none, 0, 0, _tileWidth, _tileHeight, 0, 0, 0)
{
	m_spawnTimer = c_spawnTime - c_firstSpawnTime;

	m_fireSound = AudioManager::GetInstance()->GetEvent("event:/SFX/Enemy/enemy_bullet");
	m_hurtSound = AudioManager::GetInstance()->GetEvent("event:/SFX/Enemy/enemy_hurt");
	m_deathSound = AudioManager::GetInstance()->GetEvent("event:/SFX/Enemy/enemy_killed");
	m_bulletExplosionSound = AudioManager::GetInstance()->GetEvent("event:/SFX/bullet_explosion");

	m_fireSound->loadSampleData();
	m_hurtSound->loadSampleData();
	m_deathSound->loadSampleData();
	m_bulletExplosionSound->loadSampleData();
}

EnemySpawner::~EnemySpawner()
{
	m_fireSound->releaseAllInstances();
	m_hurtSound->releaseAllInstances();
	m_deathSound->releaseAllInstances();
	m_bulletExplosionSound->releaseAllInstances();

	m_fireSound->unloadSampleData();
	m_hurtSound->unloadSampleData();
	m_deathSound->unloadSampleData();
	m_bulletExplosionSound->unloadSampleData();
}

bool EnemySpawner::Update()
{
	const float deltaTime = Time::GetInstance()->GetDeltaTime();

	m_spawnTimer += deltaTime;
	while(m_spawnTimer >= c_spawnTime)
	{
		m_spawnTimer -= c_spawnTime;
		SpawnEnemy();
	}
	
	return true;
}

void EnemySpawner::Draw(SDL_Renderer* _renderer) const
{
	
}

void EnemySpawner::SpawnEnemy() const
{
	const bool horizontal = rand() % 2;
	int x, y;

	const bool side = rand() % 2;
	if(horizontal)
	{
		x = rand() % (c_spawnBounds.w - c_spawnBounds.x) + c_spawnBounds.x;
		y = side * (c_spawnBounds.h - c_spawnBounds.y) + c_spawnBounds.y;
	}
	else
	{
		x = side * (c_spawnBounds.w - c_spawnBounds.x) + c_spawnBounds.x;
		y = rand() % (c_spawnBounds.h - c_spawnBounds.y) + c_spawnBounds.y;
	}

	const int targetX = rand() % (c_targetBounds.w - c_targetBounds.x) + c_targetBounds.x;
	const int targetY = rand() % (c_targetBounds.h - c_targetBounds.y) + c_targetBounds.y;
	
	SDL_Rect enemyHitbox = { 8, 2, 16, 12 };
	m_entityHandler->AddEntity(new EnemyDrone(enemyHitbox, m_fireSound, m_hurtSound, m_deathSound, m_bulletExplosionSound, 3, 1, targetX, targetY, x, y, m_tileWidth, m_tileHeight));
}
