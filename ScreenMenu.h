#pragma once

#include "Screen.h"

#include <fmod_studio.hpp>

#include "Sprite.h"
#include "Text.h"

#include "Button.h"

class ScreenMenu final : public Screen
{
private:
	static constexpr int c_optionCount = 3;
	
	static constexpr int c_titleLabelX = 240;
	static constexpr int c_titleLabelY = 24;
	static constexpr int c_titleFontSize = 80;
	static constexpr float c_titleMidpointX = 0.5f;
	static constexpr float c_titleMidpointY = 0.0f;

	static constexpr int c_copyrightLabelX = 472;
	static constexpr int c_copyrightLabelY = 346;
	static constexpr int c_copyrightFontSize = 18;
	static constexpr float c_copyrightMidpointX = 1.0f;
	static constexpr float c_copyrightMidpointY = 1.0f;

	static constexpr int c_optionLabelsX = 240;
	static constexpr int c_optionLabelsY = 144;
	static constexpr int c_optionLabelOffsetY = 54;
	static constexpr int c_optionFontSize = 40;
	static constexpr float c_optionMidpointX = 0.5f;
	static constexpr float c_optionMidpointY = 0.0f;

	static constexpr int c_movementControlsLabelX = 8;
	static constexpr int c_movementControlsLabelY = 306;
	static constexpr int c_movementControlsFontSize = 18;
	static constexpr float c_movementControlsMidpointX = 0.0f;
	static constexpr float c_movementControlsMidpointY = 1.0f;

	static constexpr int c_firingControlsLabelX = 8;
	static constexpr int c_firingControlsLabelY = 326;
	static constexpr int c_firingControlsFontSize = 18;
	static constexpr float c_firingControlsMidpointX = 0.0f;
	static constexpr float c_firingControlsMidpointY = 1.0f;

	static constexpr int c_goalLabelX = 8;
	static constexpr int c_goalLabelY = 346;
	static constexpr int c_goalFontSize = 18;
	static constexpr float c_goalMidpointX = 0.0f;
	static constexpr float c_goalMidpointY = 1.0f;

	static constexpr int c_optionButtonOffsetX = -24;
	static constexpr int c_optionButtonOffsetY = 12;
	static constexpr int c_optionButtonPadding = 4;

	static constexpr SDL_Color c_backgroundColour = { 50, 4, 38, 255 };
	static constexpr SDL_Color c_textColour = { 255, 255, 255, 255 };

	FMOD::Studio::EventDescription* m_music = nullptr;
	FMOD::Studio::EventInstance* m_musicInstance = nullptr;

	Sprite* m_cursor = nullptr;
	
	Text* m_titleLabel = nullptr;
	Text* m_copyrightLabel = nullptr;
	
	Text* m_movementControlsLabel = nullptr;
	Text* m_firingControlsLabel = nullptr;
	Text* m_goalLabel = nullptr;
	
	Button* m_options[c_optionCount] = {};
public:
	void Load() override;
	void Unload() override;
	bool Update() override;
	void Draw(SDL_Renderer* _renderer) override;
};

