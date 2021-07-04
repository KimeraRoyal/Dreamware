#pragma once

#include "Screen.h"

#include "Sprite.h"
#include "Text.h"

#include "Button.h"

class ScreenVictory final : public Screen
{
private:
	static constexpr int c_titleLabelX = 240;
	static constexpr int c_titleLabelY = 0;
	static constexpr int c_titleFontSize = 60;
	static constexpr float c_titleMidpointX = 0.5f;
	static constexpr float c_titleMidpointY = 0.0f;
	
	static constexpr int c_highScoreLabelX = 8;
	static constexpr int c_highScoreLabelY = 352;
	static constexpr int c_highScoreFontSize = 18;
	static constexpr float c_highScoreMidpointX = 0.0f;
	static constexpr float c_highScoreMidpointY = 1.0f;

	static constexpr int c_scoreLabelX = 472;
	static constexpr int c_scoreLabelY = 352;
	static constexpr int c_scoreFontSize = 18;
	static constexpr float c_scoreMidpointX = 1.0f;
	static constexpr float c_scoreMidpointY = 1.0f;

	static constexpr int c_continueLabelX = 24;
	static constexpr int c_continueLabelY = 64;
	static constexpr int c_continueFontSize = 24;
	static constexpr float c_continueLabelMidpointX = 0.0f;
	static constexpr float c_continueLabelMidpointY = 0.0f;

	static constexpr int c_menuLabelX = 24;
	static constexpr int c_menuLabelY = 102;
	static constexpr int c_menuFontSize = 24;
	static constexpr float c_menuLabelMidpointX = 0.0f;
	static constexpr float c_menuLabelMidpointY = 0.0f;

	static constexpr int c_menuCursorOffsetX = -20;
	static constexpr int c_menuCursorOffsetY = 6;
	static constexpr int c_menuButtonPadding = 4;

	static constexpr int c_splashX = 112;
	static constexpr int c_splashY = 70;

	static constexpr SDL_Color c_textColour = { 255, 255, 255, 255 };

	Screen* m_parent;

	Sprite* m_cursor = nullptr;
	Sprite* m_victorySplash = nullptr;

	Text* m_titleLabel = nullptr;
	Text* m_highScoreLabel = nullptr;
	Text* m_scoreLabel = nullptr;

	Button* m_continueButton = nullptr;
	Button* m_menuButton = nullptr;
public:
	ScreenVictory(Screen* _parent);
	
	void Load() override;
	void Unload() override;
	bool Update() override;
	void Draw(SDL_Renderer* _renderer) override;
};

