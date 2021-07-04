#include "EnemyDrone.h"

#include "Time.h"

#include "Spritesheet.h"

EnemyDrone::EnemyDrone(SDL_Rect& _hitbox, FMOD::Studio::EventDescription* _fireSound, FMOD::Studio::EventDescription* _hurtSound, FMOD::Studio::EventDescription* _deathSound, FMOD::Studio::EventDescription* _bulletExplosionSound, const int _health, const int _damage, const float _targetX, const float _targetY, const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
	: Enemy(nullptr, _fireSound, _hurtSound, _deathSound, _bulletExplosionSound, _hitbox, _health, _damage, _x, _y, _tileWidth, _tileHeight, _width, _height, _layer)
{
	m_enemyGraphic = new LayeredGraphicObject("Assets/Graphics/Overworld/enemy0", _x, _y, _tileWidth, _tileHeight);
	m_graphicObject = m_enemyGraphic;

	m_targetX = _targetX;
	m_targetY = _targetY;

	m_fireDelay = c_fireFrames;
		
#ifdef _DEBUG
	printf(">> Enemy Drone Loaded\n");
#endif
}

bool EnemyDrone::Update()
{
	Move();
	
	m_lastGunDirection = m_gunDirection;
	
	m_rotationTimer++;
	if(m_rotationTimer % m_fireDelay == 0)
	{
		m_gunDirection = static_cast<DiagonalDirection>((static_cast<unsigned short>(m_gunDirection) + 1) % 8);

		float bulletX, bulletY;
		GetDirectionVector(m_gunDirection, bulletX, bulletY);

		SpawnBullet(bulletX, bulletY, c_bulletSpeed, c_bulletFalloff, c_bulletOffsetX, c_bulletOffsetY);
	}
	
	return Enemy::Update();
}

void EnemyDrone::Draw(SDL_Renderer* _renderer) const
{
	if(m_gunDirection != m_lastGunDirection)
	{
		Spritesheet* droneGun = dynamic_cast<Spritesheet*>(m_enemyGraphic->GetGraphicLayer(c_gunLayer)->GetSprite());
		droneGun->SetAnimation(static_cast<int>(m_gunDirection));
	}
	
	Enemy::Draw(_renderer);
}

void EnemyDrone::Move()
{
	const float deltaTime = Time::GetInstance()->GetDeltaTime();

	float xDifference = m_targetX - m_X;
	float yDifference = m_targetY - m_Y;
	
	const double dX = static_cast<double>(xDifference);
	const double dY = static_cast<double>(yDifference);
	const float length = static_cast<float>(sqrt(dX * dX + dY * dY));

	if(length > 1)
	{
		xDifference /= length;
		yDifference /= length;
	}
	else
	{
		m_fireDelay = c_stationaryFireFrames;
	}
	
	SetX(GetX() + xDifference * c_movementSpeed * deltaTime);
	SetY(GetY() + yDifference * c_movementSpeed * deltaTime);
}
