#include "Player.h"


#include "AudioManager.h"
#include "Bullet.h"
#include "Game.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "Time.h"

#include "Spritesheet.h"
#include "SingleGraphicObject.h"

#include "ScreenGameOver.h"

Player::Player(SDL_Rect& _hitbox, const int _health, const int _damage, const float _x, const float _y, const int _tileWidth, const int _tileHeight, const float _width, const float _height, const int _layer)
	: LivingEntity(nullptr, _hitbox, CollisionLayer::player, _health, _x, _y, _tileWidth, _tileHeight, _width, _height, _layer)
{
	m_playerGraphic = new LayeredGraphicObject("Assets/Graphics/Overworld/player", _x, _y, _tileWidth, _tileHeight);
	m_graphicObject = m_playerGraphic;

	m_damage = _damage;

	m_fireSound = AudioManager::GetInstance()->GetEvent("event:/SFX/Player/player_bullet");
	m_hurtSound = AudioManager::GetInstance()->GetEvent("event:/SFX/Player/player_hurt");
	m_deathSound = AudioManager::GetInstance()->GetEvent("event:/SFX/Player/player_killed");
	m_bulletExplosionSound = AudioManager::GetInstance()->GetEvent("event:/SFX/bullet_explosion");
	

	m_fireSound->loadSampleData();
	m_hurtSound->loadSampleData();
	m_deathSound->loadSampleData();
	m_bulletExplosionSound->loadSampleData();

#ifdef _DEBUG
	printf(">> Player Loaded\n");
#endif
}

Player::~Player()
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

bool Player::Update()
{
	if(m_currentHealth < 1)
	{
		return false;
	}
	
	m_lastMovementDirection = m_movementDirection;
	m_lastFacingDirection = m_facingDirection;

	m_wasMoving = m_isMoving;
	
	const float deltaTime = Time::GetInstance()->GetDeltaTime();

	if(m_bulletTimer > 0.0f)
	{
		m_bulletTimer -= deltaTime;
		if(m_bulletTimer < 0.0f)
		{
			m_bulletTimer = 0.0f;
		}
	}
	
	HandleMovement();
	HandleFiring();
	
	return LivingEntity::Update();
}

void Player::Draw(SDL_Renderer* _renderer) const
{
	if(m_movementDirection != m_lastMovementDirection || m_wasMoving != m_isMoving)
	{
		Spritesheet* playerBody = dynamic_cast<Spritesheet*>(m_playerGraphic->GetGraphicLayer(c_playerBodyLayer)->GetSprite());
		playerBody->SetAnimation(static_cast<int>(m_movementDirection) + m_isMoving * 4);
	}

	if(m_facingDirection != m_lastFacingDirection || m_wasMoving != m_isMoving)
	{
		Spritesheet* playerHead = dynamic_cast<Spritesheet*>(m_playerGraphic->GetGraphicLayer(c_playerHeadLayer)->GetSprite());
		playerHead->SetAnimation(static_cast<int>(m_facingDirection) + m_isMoving * 4);
	}
	
	LivingEntity::Draw(_renderer);
}

void Player::Damage(const int _amount, Entity* _source)
{
	Game::GetInstance()->RemoveScore(_amount * c_scorePerHit);

	auto* sound = AudioManager::CreateEventInstance(m_hurtSound);
	sound->start();
	sound->release();
	
	LivingEntity::Damage(_amount, _source);
}

void Player::Kill(Entity* _source)
{
	ScreenManager::GetInstance()->AddScreen(new ScreenGameOver(), true);

	auto* sound = AudioManager::CreateEventInstance(m_deathSound);
	sound->start();
	sound->release();
	
#ifdef _DEBUG
	printf(">> Player Killed!\n");
#endif
}

void Player::HandleMovement()
{
	const float deltaTime = Time::GetInstance()->GetDeltaTime();

	m_movementX = static_cast<float>(InputManager::GetInstance()->GetKeyDown(Key::d));
	m_movementY = static_cast<float>(InputManager::GetInstance()->GetKeyDown(Key::s));

	m_movementX -= static_cast<float>(InputManager::GetInstance()->GetKeyDown(Key::a));
	m_movementY -= static_cast<float>(InputManager::GetInstance()->GetKeyDown(Key::w));

	if (m_movementY != 0.0f)
	{
		m_movementDirection = m_movementY > 0 ? CardinalDirection::down : CardinalDirection::up;
	}
	else if (m_movementX != 0.0f)
	{
		m_movementDirection = m_movementX > 0 ? CardinalDirection::right : CardinalDirection::left;
	}

	m_isMoving = m_movementX * m_movementY + m_movementX + m_movementY != 0.0f;
	if (m_isMoving)
	{
		const double dX = static_cast<double>(m_movementX);
		const double dY = static_cast<double>(m_movementY);
		const float length = static_cast<float>(sqrt(dX * dX + dY * dY));

		m_movementX /= length;
		m_movementY /= length;

		SetX(GetX() + m_movementX * c_walkSpeed * deltaTime);
		SetY(GetY() + m_movementY * c_walkSpeed * deltaTime);

		if (GetX() + static_cast<float>(m_hitboxX) < c_movementBounds.x)
		{
			SetX(c_movementBounds.x - static_cast<float>(m_hitboxX));
		}
		else if (GetX() + static_cast<float>(m_hitboxX + m_hitboxWidth) > c_movementBounds.w)
		{
			SetX(c_movementBounds.w - static_cast<float>(m_hitboxX + m_hitboxWidth));
		}

		if (GetY() + static_cast<float>(m_hitboxY) < c_movementBounds.y)
		{
			SetY(c_movementBounds.y - static_cast<float>(m_hitboxY));
		}
		else if (GetY() + static_cast<float>(m_hitboxY + m_hitboxHeight) > c_movementBounds.h)
		{
			SetY(c_movementBounds.h - static_cast<float>(m_hitboxY + m_hitboxHeight));
		}
	}
}

void Player::HandleFiring()
{
	const bool firing = InputManager::GetInstance()->GetKeyDown(static_cast<Key>(static_cast<unsigned short>(Key::up) | static_cast<unsigned short>(Key::left) | static_cast<unsigned short>(Key::down) | static_cast<unsigned short>(Key::right)));
	if (firing)
	{
		if (InputManager::GetInstance()->GetKeyPressed(Key::up))
		{
			m_facingDirection = CardinalDirection::up;
		}
		else if (InputManager::GetInstance()->GetKeyPressed(Key::left))
		{
			m_facingDirection = CardinalDirection::left;
		}
		else if (InputManager::GetInstance()->GetKeyPressed(Key::down))
		{
			m_facingDirection = CardinalDirection::down;
		}
		else if (InputManager::GetInstance()->GetKeyPressed(Key::right))
		{
			m_facingDirection = CardinalDirection::right;
		}

		GetDirectionVector(m_facingDirection, m_facingX, m_facingY);
		if (m_bulletTimer <= 0.0f)
		{
			m_bulletTimer = c_bulletDelay;
			SpawnBullet();
		}
	}
}

void Player::SpawnBullet() const
{
	const float bulletX = m_X + c_bulletOffsetX;
	const float bulletY = m_Y + c_bulletOffsetY;

	float bulletFiringX = m_facingX + m_movementX * c_playerMovementInfluence;
	float bulletFiringY = m_facingY + m_movementY * c_playerMovementInfluence;

	const double dX = static_cast<double>(bulletFiringX);
	const double dY = static_cast<double>(bulletFiringY);
	const float length = static_cast<float>(sqrt(dX * dX + dY * dY));

	bulletFiringX /= length;
	bulletFiringY /= length;

	Spritesheet* bulletSprite = new Spritesheet("Assets/Graphics/Overworld/player_bullet");
	WorldObject* bulletGraphic = new SingleGraphicObject(bulletSprite, bulletX, bulletY, m_tileWidth, m_tileHeight, 0.5f, 0.5f);

	SDL_Rect bulletHitbox = { 0, 0, 8, 8 };
	m_entityHandler->AddEntity(new Bullet(bulletGraphic, m_bulletExplosionSound, bulletFiringX * c_bulletSpeed, bulletFiringY * c_bulletSpeed, 0.3f, CollisionLayer::enemy, m_damage, bulletHitbox, CollisionLayer::bullet, bulletX, bulletY, m_tileWidth, m_tileHeight, 0.5f, 0.5f));

	auto* sound = AudioManager::CreateEventInstance(m_fireSound);
	sound->start();
	sound->release();
}