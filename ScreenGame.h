#pragma once

#include "Screen.h"

#include "EntityHandler.h"

#include "Spritesheet.h"
#include "Tilemap.h"
#include "Player.h"
#include "Text.h"

class ScreenGame final : public Screen
{
private:
	static constexpr int c_highScoreLabelX = 472;
	static constexpr int c_highScoreLabelY = 4;
	static constexpr int c_highScoreFontSize = 18;
	static constexpr float c_highScoreMidpointX = 1.0f;
	static constexpr float c_highScoreMidpointY = 0.0f;

	static constexpr int c_scoreLabelX = 472;
	static constexpr int c_scoreLabelY = 28;
	static constexpr int c_scoreFontSize = 18;
	static constexpr float c_scoreMidpointX = 1.0f;
	static constexpr float c_scoreMidpointY = 0.0f;

	static constexpr SDL_Color c_textColour = { 255, 255, 255, 255 };
	
	static constexpr int c_playerHealthX = 8;
	static constexpr int c_playerHealthY = 8;
	static constexpr int c_playerHealthOffset = 24;
	
	static constexpr float c_playerStartingX = 64;
	static constexpr float c_playerStartingY = 64;

	FMOD::Studio::EventDescription* m_music = nullptr;
	FMOD::Studio::EventInstance* m_musicInstance = nullptr;
	
	EntityHandler* m_entityHandler = nullptr;
	
	Tilemap* m_tilemap = nullptr;
	Player* m_player = nullptr;

	Spritesheet* m_playerHealth = nullptr;
	
	Text* m_highScoreLabel = nullptr;
	Text* m_scoreLabel = nullptr;

	int m_lastScore = 0;
	int m_lastHighScore = 0;

	bool m_beaten = false;
	int m_clearScore = 0;
public:
	void Load() override;
	void Unload() override;
	bool Update() override;
	void Draw(SDL_Renderer* _renderer) override;
};

