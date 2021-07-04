#include "ScreenGame.h"

#include <cstdio>

#include "AudioManager.h"
#include "FileManager.h"
#include "InputManager.h"
#include "ScreenManager.h"

#include "EnemySpawner.h"
#include "Game.h"

#include "ScreenMenu.h"
#include "ScreenVictory.h"

void ScreenGame::Load()
{
	Game::GetInstance()->SetScore(0);
	
	m_entityHandler = new EntityHandler();

	m_tilemap = new Tilemap("Assets/Maps/mapSand0.json");

	SDL_Rect playerHitbox = { 8, 24, 16, 24 };
	m_player = new Player(playerHitbox, 3, 1, c_playerStartingX, c_playerStartingY, m_tilemap->GetTileWidth(), m_tilemap->GetTileHeight());
	m_entityHandler->AddEntity(m_player);

	m_entityHandler->AddEntity(new EnemySpawner(m_tilemap->GetTileWidth(), m_tilemap->GetTileHeight()));
	
	m_playerHealth = new Spritesheet("Assets/Graphics/UI/health");
	
	m_highScoreLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_highScoreFontSize, "High Score: " + std::to_string(Game::GetInstance()->GetHighScore()), c_textColour, c_highScoreMidpointX, c_highScoreMidpointY);
	m_scoreLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_scoreFontSize, "Score: " + std::to_string(Game::GetInstance()->GetScore()), c_textColour, c_scoreMidpointX, c_scoreMidpointY);

	m_clearScore = Game::GetInstance()->GetHighScore();

	m_music = AudioManager::GetInstance()->GetEvent("event:/BGM/Battle/bgm_default_battle");
	m_musicInstance = AudioManager::CreateEventInstance(m_music);
	m_musicInstance->start();
	
#ifdef _DEBUG
	printf("> Overworld Loaded\n");
#endif
}

void ScreenGame::Unload()
{
	m_musicInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);

	m_music->releaseAllInstances();
	m_music->unloadSampleData();
	
	delete m_entityHandler;

	delete m_tilemap;
	delete m_playerHealth;

#ifdef _DEBUG
	printf("> Overworld Unloaded\n");
#endif
}

bool ScreenGame::Update()
{
	if (InputManager::GetInstance()->GetKeyPressed(Key::esc))
	{
		ScreenManager::GetInstance()->SetScreen(new ScreenMenu(), true);
	}
	else
	{
		if(!m_entityHandler->Update())
		{
			SetRunning(false);
		}
	}

	const int score = Game::GetInstance()->GetScore();
	const int highScore = Game::GetInstance()->GetHighScore();

	if (m_lastHighScore != highScore)
	{
		m_lastHighScore = highScore;
		m_highScoreLabel->SetText("High Score: " + std::to_string(highScore));
		m_highScoreLabel->Update();
	}
	
	if(m_lastScore != score)
	{
		m_lastScore = score;
		m_scoreLabel->SetText("Score: " + std::to_string(score));
		m_scoreLabel->Update();
	}

	// Lol magic numbers
	if(!m_beaten && score >= m_clearScore)
	{
		m_beaten = true;

		ScreenManager::GetInstance()->AddScreen(new ScreenVictory(this), true);
		SetRunning(false);
	}
	
	return true;
}

void ScreenGame::Draw(SDL_Renderer* _renderer)
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);

	m_tilemap->Draw(_renderer);
	m_entityHandler->Draw(_renderer);

	for(int i = 0; i < m_player->GetMaxHealth(); i++)
	{
		const int x = c_playerHealthX + c_playerHealthOffset * i;
		m_playerHealth->Draw(_renderer, x, c_playerHealthY, 0, i + 1 > m_player->GetCurrentHealth());
	}

	if (!GetRunning())
	{
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 125);
		SDL_RenderFillRect(_renderer, nullptr);
	}
	else
	{
		m_highScoreLabel->Draw(_renderer, c_highScoreLabelX, c_highScoreLabelY);
		m_scoreLabel->Draw(_renderer, c_scoreLabelX, c_scoreLabelY);
	}
}
