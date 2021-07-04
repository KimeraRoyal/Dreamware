#include "ScreenSoundTest.h"

#include <cstdio>

#include "AudioManager.h"
#include "FileManager.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "Time.h"

#include "ScreenMenu.h"

#include "SpritesheetFrame.h"

void ScreenSoundTest::Load()
{
	auto* soundTestJson = FileManager::GetTextFile("Assets/soundTest.json");
	
	rapidjson::Document soundTestDoc;
	soundTestDoc.Parse(soundTestJson);
	
	const auto& songs = soundTestDoc["songs"];
	assert(songs.IsArray());
	for (rapidjson::SizeType i = 0; i < songs.Size(); i++)
	{
		m_songs.push_back(new SongInfo(songs[i]));
		m_songEvents.push_back(AudioManager::GetInstance()->GetEvent(m_songs[i]->GetPath().c_str()));
		m_songInstances.push_back(AudioManager::CreateEventInstance(m_songEvents[i]));
	}
	
	m_cursor = new Sprite("Assets/Graphics/Menu/cursor.png");
	m_icons = new Spritesheet("Assets/Graphics/Menu/sound_test_icons");
	m_iconFrame = new Sprite("Assets/Graphics/Menu/frame.png");
	m_disc = new Sprite("Assets/Graphics/Menu/disc.png");

	auto* backLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_backFontSize, "Back", c_textColour, c_backLabelMidpointX, c_backLabelMidpointY);
	m_soundTestLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_soundTestFontSize, "Sound Test", c_textColour, c_soundTestMidpointX, c_soundTestMidpointY);
	m_songNameLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_songNameFontSize, "", c_textColour, c_songNameMidpointX, c_songNameMidpointY);
	m_songSubtitleLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_songSubtitleFontSize, "", c_textColour, c_songSubtitleMidpointX, c_songSubtitleMidpointY);
	m_songDetailsLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_songDetailsFontSize, "Kim Royal - Dustworld OST", c_textColour, c_songDetailsMidpointX, c_songDetailsMidpointY);

	m_backButton = new Button(backLabel, c_backLabelX, c_backLabelY, backLabel->GetWidth(), backLabel->GetHeight(), c_backButtonPadding, c_backButtonPadding);

	for (int i = 0; i < c_songCount; i++)
	{
		const auto x = (i % c_iconsPerRow) * c_iconOffsetX + c_iconsX;
		const auto y = (i / c_iconsPerRow) * c_iconOffsetY + c_iconsY;

		SpritesheetFrame* icon = new SpritesheetFrame(m_icons, 0, i);
		m_iconButtons[i] = new Button(icon, x, y, m_icons->GetSpriteWidth(), m_icons->GetSpriteHeight(), c_iconButtonPadding, c_iconButtonPadding);
	}
	
#ifdef _DEBUG
	printf("> Sound Test Loaded\n");
#endif
}

void ScreenSoundTest::Unload()
{
	for (auto& button : m_iconButtons)
	{
		delete button;
	}

	delete m_cursor;
	delete m_icons;
	delete m_iconFrame;
	delete m_disc;
	
	delete m_soundTestLabel;
	delete m_songNameLabel;
	delete m_songSubtitleLabel;
	delete m_songDetailsLabel;

	delete m_backButton;

	if (m_currentSong != nullptr)
	{
		m_currentSong->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
	}
	
	for(int i = 0; i < c_songCount; i++)
	{
		delete m_songs[i];
		m_songEvents[i]->releaseAllInstances();
		m_songEvents[i]->unloadSampleData();
	}
	m_songs.clear();
	m_songEvents.clear();
	
#ifdef _DEBUG
	printf("> Sound Test Unloaded\n");
#endif
}

bool ScreenSoundTest::Update()
{
	const auto mousePressed = InputManager::GetInstance()->GetMousePressed();
	
	m_backButton->Update();
	if(InputManager::GetInstance()->GetKeyPressed(Key::esc) || m_backButton->IsMouseHovered() && mousePressed)
	{
		ScreenManager::GetInstance()->SetScreen(new ScreenMenu(), true);
		return true;
	}

	for(int i = 0; i < c_songCount; i++)
	{
		auto& button = m_iconButtons[i];
		button->Update();
		if(button->IsMouseHovered() && mousePressed)
		{
			if(m_currentSong != nullptr)
			{
				m_currentSong->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
			}

			if(m_currentSongId == i)
			{
				m_currentSongId = -1;
				m_currentSong = nullptr;

#ifdef _DEBUG
				printf("Stopped Song\n");
#endif
			}
			else
			{
				m_currentSong = m_songInstances[i];
				m_currentSong->start();

				m_songNameLabel->SetText("- " + m_songs[i]->GetName() + " -");
				m_songSubtitleLabel->SetText("\"" + m_songs[i]->GetSubtitle() + "\"");
				m_currentSongId = i;

#ifdef _DEBUG
				printf("Playing Song: \"%s\"\n", m_songs[i]->GetName().c_str());
#endif
			}
		}
	}

	m_songNameLabel->Update();
	m_songSubtitleLabel->Update();

	if(m_currentSong != nullptr)
	{
		m_discAngle += c_discSpeed * static_cast<double>(Time::GetInstance()->GetDeltaTime());
	}

	return true;
}

void ScreenSoundTest::Draw(SDL_Renderer* _renderer)
{
	SDL_SetRenderDrawColor(_renderer, c_backgroundColour.r, c_backgroundColour.g, c_backgroundColour.b, c_backgroundColour.a);
	SDL_RenderClear(_renderer);
	
	m_soundTestLabel->Draw(_renderer, c_soundTestLabelX, c_soundTestLabelY);
	if(m_currentSong != nullptr)
	{
		m_songNameLabel->Draw(_renderer, c_songNameLabelX, c_songNameLabelY);
		m_songSubtitleLabel->Draw(_renderer, c_songSubtitleLabelX, c_songSubtitleLabelY);
		m_songDetailsLabel->Draw(_renderer, c_songDetailsLabelX, c_songDetailsLabelY);
	}

	m_disc->Draw(_renderer, c_discX, c_discY, m_discAngle);

	m_backButton->Draw(_renderer);
	if(m_backButton->IsMouseHovered())
	{
		m_cursor->Draw(_renderer, m_backButton->GetX() + c_backCursorOffsetX, m_backButton->GetY() + c_backCursorOffsetY);
	}
	
	for (int i = 0; i < c_songCount; i++)
	{
		auto& button = m_iconButtons[i];
		
		button->Draw(_renderer);
		m_iconFrame->Draw(_renderer, button->GetX() + c_iconFrameOffsetX, button->GetY() + c_iconFrameOffsetY);
		if(m_currentSongId == i || button->IsMouseHovered())
		{
			m_cursor->Draw(_renderer, button->GetX() + c_iconCursorOffsetX, button->GetY() + c_iconCursorOffsetY);
		}
	}
}
