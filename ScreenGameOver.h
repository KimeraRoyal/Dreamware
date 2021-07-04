#pragma once

#include "Screen.h"

#include "Sprite.h"
#include "Text.h"

#include "Button.h"

class ScreenGameOver final : public Screen
{
private:
	static constexpr int c_titleLabelX = 240;
	static constexpr int c_titleLabelY = 24;
	static constexpr int c_titleFontSize = 80;
	static constexpr float c_titleMidpointX = 0.5f;
	static constexpr float c_titleMidpointY = 0.0f;

	static constexpr int c_highScoreLabelX = 240;
	static constexpr int c_highScoreLabelY = 200;
	static constexpr int c_highScoreFontSize = 40;
	static constexpr float c_highScoreMidpointX = 0.5f;
	static constexpr float c_highScoreMidpointY = 0.0f;

	static constexpr int c_scoreLabelX = 240;
	static constexpr int c_scoreLabelY = 260;
	static constexpr int c_scoreFontSize = 40;
	static constexpr float c_scoreMidpointX = 0.5f;
	static constexpr float c_scoreMidpointY = 0.0f;
	
	static constexpr int c_backLabelX = 24;
	static constexpr int c_backLabelY = 4;
	static constexpr int c_backFontSize = 24;
	static constexpr float c_backLabelMidpointX = 0.0f;
	static constexpr float c_backLabelMidpointY = 0.0f;

	static constexpr int c_backCursorOffsetX = -20;
	static constexpr int c_backCursorOffsetY = 6;
	static constexpr int c_backButtonPadding = 4;
	
	static constexpr SDL_Color c_textColour = { 255, 255, 255, 255 };

	Sprite* m_cursor = nullptr;
	
	Text* m_titleLabel = nullptr;
	Text* m_highScoreLabel = nullptr;
	Text* m_scoreLabel = nullptr;
	Button* m_backButton = nullptr;
	
public:
	void Load() override;
	void Unload() override;
	bool Update() override;
	void Draw(SDL_Renderer* _renderer) override;
};

