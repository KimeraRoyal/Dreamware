#include "ScreenMenu.h"

#include <cstdio>

#include "Game.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "ScreenManager.h"

#include "ScreenGame.h"
#include "ScreenSoundTest.h"

void ScreenMenu::Load()
{
	m_cursor = new Sprite("Assets/Graphics/Menu/cursor.png");
	
	m_titleLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_titleFontSize, "- Dustworld -", c_textColour, c_titleMidpointX, c_titleMidpointY);
	m_copyrightLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_copyrightFontSize, "© 2021 Kim Royal", c_copyrightMidpointX, c_copyrightMidpointY);

	m_movementControlsLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_movementControlsFontSize, "Press WASD to move,", c_textColour, c_movementControlsMidpointX, c_movementControlsMidpointY);
	m_firingControlsLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_firingControlsFontSize, "Press Arrow Keys to fire,", c_textColour, c_firingControlsMidpointX, c_firingControlsMidpointY);
	m_goalLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_goalFontSize, "Get to a score of " + std::to_string(Game::GetInstance()->GetHighScore()) + " to win!", c_textColour, c_goalMidpointX, c_goalMidpointY);

	Text* optionLabels[c_optionCount] = {};
	optionLabels[0] = new Text("Assets/Fonts/bebaus_neue.ttf", c_optionFontSize, "Play", c_optionMidpointX, c_optionMidpointY);
	optionLabels[1] = new Text("Assets/Fonts/bebaus_neue.ttf", c_optionFontSize, "Sound Test", c_optionMidpointX, c_optionMidpointY);
	optionLabels[2] = new Text("Assets/Fonts/bebaus_neue.ttf", c_optionFontSize, "Exit", c_optionMidpointX, c_optionMidpointY);

	for(int i = 0; i < c_optionCount; i++)
	{
		const int y = c_optionLabelsY + c_optionLabelOffsetY * i;
		
		const int width = optionLabels[i]->GetWidth();
		const int height = optionLabels[i]->GetHeight();

		const int offsetX = static_cast<int>(static_cast<float>(width) * -optionLabels[i]->GetOffsetX());
		const int offsetY = static_cast<int>(static_cast<float>(height) * -optionLabels[i]->GetOffsetY());
		
		m_options[i] = new Button(optionLabels[i], c_optionLabelsX, y, width, height, c_optionButtonPadding, c_optionButtonPadding, offsetX, offsetY);
	}

	m_music = AudioManager::GetInstance()->GetEvent("event:/BGM/Overworld/Dreamscape/bgm_dreamscape");
	m_musicInstance = AudioManager::CreateEventInstance(m_music);
	m_musicInstance->start();
	
#ifdef _DEBUG
	printf("> Menu Loaded\n");
#endif
}

void ScreenMenu::Unload()
{
	m_musicInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
	
	m_music->releaseAllInstances();
	m_music->unloadSampleData();
	
	delete m_cursor;
	
	delete m_titleLabel;
	delete m_copyrightLabel;

	delete m_movementControlsLabel;
	delete m_firingControlsLabel;
	delete m_goalLabel;

	for(auto& option : m_options)
	{
		delete option;
	}
	
#ifdef _DEBUG
	printf("> Menu Unloaded\n");
#endif
}

bool ScreenMenu::Update()
{
	if(InputManager::GetInstance()->GetKeyPressed(Key::esc))
	{
		return false;
	}
	
	const auto mousePressed = InputManager::GetInstance()->GetMousePressed();
	
	for(int i = 0; i < c_optionCount; i++)
	{
		m_options[i]->Update();
		if (m_options[i]->IsMouseHovered() && mousePressed)
		{
			switch (i)
			{
				case 0:
				{
					ScreenManager::GetInstance()->SetScreen(new ScreenGame(), true);
					return true;
				}
				case 1:
				{
					ScreenManager::GetInstance()->SetScreen(new ScreenSoundTest(), true);
					return true;
				}
				case 2:
				{
					return false;
				}
				default:
				{
					break;
				}
			}
		}
	}
	
	return true;
}

void ScreenMenu::Draw(SDL_Renderer* _renderer)
{
	SDL_SetRenderDrawColor(_renderer, c_backgroundColour.r, c_backgroundColour.g, c_backgroundColour.b, c_backgroundColour.a);
	SDL_RenderClear(_renderer);

	m_titleLabel->Draw(_renderer, c_titleLabelX, c_titleLabelY);
	m_copyrightLabel->Draw(_renderer, c_copyrightLabelX, c_copyrightLabelY);

	m_movementControlsLabel->Draw(_renderer, c_movementControlsLabelX, c_movementControlsLabelY);
	m_firingControlsLabel->Draw(_renderer, c_firingControlsLabelX, c_firingControlsLabelY);
	m_goalLabel->Draw(_renderer, c_goalLabelX, c_goalLabelY);

	for(auto& option : m_options)
	{
		option->Draw(_renderer);
		if (option->IsMouseHovered())
		{
			m_cursor->Draw(_renderer, option->GetX() + option->GetOffsetX() + c_optionButtonOffsetX, option->GetY() + option->GetOffsetY() + c_optionButtonOffsetY);
		}
	}
}
