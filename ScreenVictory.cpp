#include "ScreenVictory.h"

#include <cstdio>

#include "Game.h"
#include "InputManager.h"
#include "ScreenManager.h"

#include "ScreenMenu.h"

ScreenVictory::ScreenVictory(Screen* _parent)
{
	m_parent = _parent;
}

void ScreenVictory::Load()
{
	m_cursor = new Sprite("Assets/Graphics/Menu/cursor.png");
	m_victorySplash = new Sprite("Assets/Graphics/UI/victory.png");

	m_titleLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_titleFontSize, "You're Winner!", c_textColour, c_titleMidpointX, c_titleMidpointY);
	m_highScoreLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_highScoreFontSize, "High Score: " + std::to_string(Game::GetInstance()->GetHighScore()), c_textColour, c_highScoreMidpointX, c_highScoreMidpointY);
	m_scoreLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_scoreFontSize, "Score: " + std::to_string(Game::GetInstance()->GetScore()), c_textColour, c_scoreMidpointX, c_scoreMidpointY);

	auto* continueLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_continueFontSize, "Continue", c_textColour, c_continueLabelMidpointX, c_continueLabelMidpointY);
	auto* menuLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_menuFontSize, "Menu", c_textColour, c_menuLabelMidpointX, c_menuLabelMidpointY);
	
	m_continueButton = new Button(continueLabel, c_continueLabelX, c_continueLabelY, continueLabel->GetWidth(), continueLabel->GetHeight(), c_menuButtonPadding, c_menuButtonPadding);
	m_menuButton = new Button(menuLabel, c_menuLabelX, c_menuLabelY, menuLabel->GetWidth(), menuLabel->GetHeight(), c_menuButtonPadding, c_menuButtonPadding);

#ifdef _DEBUG
	printf("> Victory Loaded\n");
#endif
}

void ScreenVictory::Unload()
{
	delete m_cursor;
	delete m_victorySplash;

	delete m_titleLabel;
	delete m_highScoreLabel;
	delete m_scoreLabel;

	delete m_continueButton;
	delete m_menuButton;

#ifdef _DEBUG
	printf("> Victory Unloaded\n");
#endif
}

bool ScreenVictory::Update()
{
	const auto mousePressed = InputManager::GetInstance()->GetMousePressed();

	m_continueButton->Update();
	if (m_continueButton->IsMouseHovered() && mousePressed)
	{
		Screen* self = this;
		
		m_parent->SetRunning(true);
		ScreenManager::GetInstance()->RemoveScreen(self);
		return true;
	}

	m_menuButton->Update();
	if (InputManager::GetInstance()->GetKeyPressed(Key::esc) || m_menuButton->IsMouseHovered() && mousePressed)
	{
		ScreenManager::GetInstance()->SetScreen(new ScreenMenu(), true);
		return true;
	}

	return true;
}

void ScreenVictory::Draw(SDL_Renderer* _renderer)
{
	m_victorySplash->Draw(_renderer, c_splashX, c_splashY);

	m_titleLabel->Draw(_renderer, c_titleLabelX, c_titleLabelY);
	m_highScoreLabel->Draw(_renderer, c_highScoreLabelX, c_highScoreLabelY);
	m_scoreLabel->Draw(_renderer, c_scoreLabelX, c_scoreLabelY);

	m_continueButton->Draw(_renderer);
	if (m_continueButton->IsMouseHovered())
	{
		m_cursor->Draw(_renderer, m_continueButton->GetX() + c_menuCursorOffsetX, m_continueButton->GetY() + c_menuCursorOffsetY);
	}

	m_menuButton->Draw(_renderer);
	if (m_menuButton->IsMouseHovered())
	{
		m_cursor->Draw(_renderer, m_menuButton->GetX() + c_menuCursorOffsetX, m_menuButton->GetY() + c_menuCursorOffsetY);
	}
}
