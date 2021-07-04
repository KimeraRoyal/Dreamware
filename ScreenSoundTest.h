#pragma once

#include <fmod_studio.hpp>

#include "Screen.h"

#include "Spritesheet.h"
#include "Sprite.h"
#include "Text.h"

#include "Button.h"

#include "SongInfo.h"

class ScreenSoundTest final : public Screen
{
private:
	static constexpr int c_songCount = 8;
	static constexpr int c_iconsPerRow = 4;

	static constexpr int c_iconsX = 40;
	static constexpr int c_iconsY = 108;
	static constexpr int c_iconOffsetX = 64;
	static constexpr int c_iconOffsetY = 52;
	static constexpr int c_iconFrameOffsetX = -4;
	static constexpr int c_iconFrameOffsetY = -4;

	static constexpr int c_discX = 312;
	static constexpr int c_discY = 86;
	static constexpr double c_discSpeed = 20.0;

	static constexpr int c_backLabelX = 24;
	static constexpr int c_backLabelY = 4;
	static constexpr int c_backFontSize = 24;
	static constexpr float c_backLabelMidpointX = 0.0f;
	static constexpr float c_backLabelMidpointY = 0.0f;

	static constexpr int c_soundTestLabelX = 240;
	static constexpr int c_soundTestLabelY = 16;
	static constexpr int c_soundTestFontSize = 64;
	static constexpr float c_soundTestMidpointX = 0.5f;
	static constexpr float c_soundTestMidpointY = 0.0f;

	static constexpr int c_songNameLabelX = 240;
	static constexpr int c_songNameLabelY = 282;
	static constexpr int c_songNameFontSize = 40;
	static constexpr float c_songNameMidpointX = 0.5f;
	static constexpr float c_songNameMidpointY = 1.0f;

	static constexpr int c_songSubtitleLabelX = 240;
	static constexpr int c_songSubtitleLabelY = 276;
	static constexpr int c_songSubtitleFontSize = 24;
	static constexpr float c_songSubtitleMidpointX = 0.5f;
	static constexpr float c_songSubtitleMidpointY = 0.0f;

	static constexpr int c_songDetailsLabelX = 240;
	static constexpr int c_songDetailsLabelY = 346;
	static constexpr int c_songDetailsFontSize = 32;
	static constexpr float c_songDetailsMidpointX = 0.5f;
	static constexpr float c_songDetailsMidpointY = 1.0f;

	static constexpr int c_iconCursorOffsetX = -24;
	static constexpr int c_iconCursorOffsetY = 10;
	static constexpr int c_iconButtonPadding = 2;

	static constexpr int c_backCursorOffsetX = -20;
	static constexpr int c_backCursorOffsetY = 6;
	static constexpr int c_backButtonPadding = 4;

	static constexpr SDL_Color c_backgroundColour = { 20, 8, 45, 255 };
	static constexpr SDL_Color c_textColour = { 255, 255, 255, 255 };

	Sprite* m_cursor = nullptr;
	Spritesheet* m_icons = nullptr;
	Sprite* m_iconFrame = nullptr;
	Sprite* m_disc = nullptr;

	Text* m_soundTestLabel = nullptr;
	Text* m_songNameLabel = nullptr;
	Text* m_songSubtitleLabel = nullptr;
	Text* m_songDetailsLabel = nullptr;

	Button* m_backButton = nullptr;
	Button* m_iconButtons[c_songCount] = {};

	std::vector<SongInfo*> m_songs;
	std::vector<FMOD::Studio::EventDescription*> m_songEvents;
	std::vector<FMOD::Studio::EventInstance*> m_songInstances;

	FMOD::Studio::EventInstance* m_currentSong = nullptr;
	int m_currentSongId = -1;

	double m_discAngle = 0.0;
	
public:
	void Load() override;
	void Unload() override;
	bool Update() override;
	void Draw(SDL_Renderer* _renderer) override;
};

