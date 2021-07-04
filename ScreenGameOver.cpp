#include "ScreenGameOver.h"

#include <cstdio>

#include "Game.h"
#include "InputManager.h"
#include "ScreenManager.h"

#include "ScreenMenu.h"

void ScreenGameOver::Load()
{
	m_cursor = new Sprite("Assets/Graphics/Menu/cursor.png");
	
	m_titleLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_titleFontSize, "Game Over!", c_textColour, c_titleMidpointX, c_titleMidpointY);
	m_highScoreLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_highScoreFontSize, "High Score: " + std::to_string(Game::GetInstance()->GetHighScore()), c_textColour, c_highScoreMidpointX, c_highScoreMidpointY);
	m_scoreLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_scoreFontSize, "Score: " + std::to_string(Game::GetInstance()->GetScore()), c_textColour, c_scoreMidpointX, c_scoreMidpointY);

	auto* backLabel = new Text("Assets/Fonts/bebaus_neue.ttf", c_backFontSize, "Back", c_textColour, c_backLabelMidpointX, c_backLabelMidpointY);
	m_backButton = new Button(backLabel, c_backLabelX, c_backLabelY, backLabel->GetWidth(), backLabel->GetHeight(), c_backButtonPadding, c_backButtonPadding);
	
#ifdef _DEBUG
	printf("> Game Over Loaded\n");
#endif
}

void ScreenGameOver::Unload()
{
	delete m_cursor;

	delete m_titleLabel;
	delete m_highScoreLabel;
	delete m_scoreLabel;
	
	delete m_backButton;
	
#ifdef _DEBUG
	printf("> Game Over Unloaded\n");
#endif
}

bool ScreenGameOver::Update()
{
	const auto mousePressed = InputManager::GetInstance()->GetMousePressed();

	m_backButton->Update();
	if (InputManager::GetInstance()->GetKeyPressed(Key::esc) || m_backButton->IsMouseHovered() && mousePressed)
	{
		ScreenManager::GetInstance()->SetScreen(new ScreenMenu(), true);
		return true;
	}

	return true;
}

void ScreenGameOver::Draw(SDL_Renderer* _renderer)
{
	m_titleLabel->Draw(_renderer, c_titleLabelX, c_titleLabelY);
	m_highScoreLabel->Draw(_renderer, c_highScoreLabelX, c_highScoreLabelY);
	m_scoreLabel->Draw(_renderer, c_scoreLabelX, c_scoreLabelY);
	
	m_backButton->Draw(_renderer);
	if (m_backButton->IsMouseHovered())
	{
		m_cursor->Draw(_renderer, m_backButton->GetX() + c_backCursorOffsetX, m_backButton->GetY() + c_backCursorOffsetY);
	}
}
