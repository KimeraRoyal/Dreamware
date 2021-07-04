#include "Game.h"

#include <cstdio>

#include "Time.h"
#include "FileManager.h"
#include "InputManager.h"
#include "GraphicManager.h"
#include "AudioManager.h"
#include "ScreenManager.h"

#include "SDL_ttf.h"

Game* Game::s_instance = nullptr;

Game::~Game()
{
	Unload();
}

void Game::Init()
{
	const auto sdlResult = SDL_Init(c_sdlFlags);
	if (sdlResult < 0)
	{
#ifdef _DEBUG
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
#endif
		exit(-1);
	}

	const auto imgResult = IMG_Init(c_imgFlags);
	if (!(imgResult & c_imgFlags))
	{
#ifdef _DEBUG
		printf("SDL Image Extension could not initialize! SDL_image Error: %s\n", IMG_GetError());
#endif
		exit(-1);
	}

	const auto ttfResult = TTF_Init();
	if(ttfResult < 0)
	{
#ifdef _DEBUG
		printf("SDL TrueType Font Extension could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
#endif
		exit(-1);
	}

	m_window = SDL_CreateWindow(c_windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, c_windowWidth * c_windowScale, c_windowHeight * c_windowScale, c_windowFlags);
	if (m_window == nullptr)
	{
#ifdef _DEBUG
		printf("SDL Window could not be created! SDL Error: %s\n", SDL_GetError());
#endif
		exit(-1);
	}

#ifdef _DEBUG
	printf("- Game Initialized -\n\n");
#endif
	
	Load();
}

void Game::Load() const
{
	Time::GetInstance();
	FileManager::GetInstance()->Load();
	GraphicManager::GetInstance()->Load(m_window);
	AudioManager::GetInstance()->Load();
	ScreenManager::GetInstance()->Load();

#ifdef _DEBUG
	printf("- Game Loaded -\n\n");
#endif
}


void Game::Unload() const
{
	ScreenManager::DeleteInstance();
	AudioManager::DeleteInstance();
	GraphicManager::DeleteInstance();
	FileManager::DeleteInstance();
	Time::DeleteInstance();
	
	IMG_Quit();
	
	SDL_DestroyWindow(m_window);
	SDL_Quit();

#ifdef _DEBUG
	printf("- Game Unloaded -\n\n");
#endif
}

void Game::GameLoop()
{
	auto running = true;

	while(running)
	{
		running = PollEvents() && Update();
	}
}

bool Game::PollEvents()
{
	auto returnValue = true;
	
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			returnValue = false;
		}
		else if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		{
			InputManager::GetInstance()->HandleMouseInput(&e);
		}
		else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
		{
			InputManager::GetInstance()->HandleKeyboardInput(&e);
		}
	}

	return returnValue;
}

bool Game::Update()
{
	Time::GetInstance()->Update();
	if(!ScreenManager::GetInstance()->Update())
	{
		return false;
	}
	GraphicManager::GetInstance()->Update();
	AudioManager::GetInstance()->Update();
	InputManager::GetInstance()->Update();

	return true;
}

void Game::SetScore(const int _score)
{
	m_currentScore = _score;
	if(m_currentScore < 0)
	{
		m_currentScore = 0;
	}
	else if(m_currentScore > m_highScore)
	{
		m_highScore = m_currentScore;
	}
}

void Game::AddScore(const int _score)
{
	SetScore(GetScore() + _score);
}

void Game::RemoveScore(const int _score)
{
	SetScore(GetScore() - _score);
}

int Game::GetScore() const
{
	return m_currentScore;
}

int Game::GetHighScore() const
{
	return m_highScore;
}

Game* Game::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Game();
		s_instance->Init();
	}

	return s_instance;
}

void Game::DeleteInstance()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

int Game::GetWindowWidth()
{
	return c_windowWidth;
}

int Game::GetWindowHeight()
{
	return c_windowHeight;
}

int Game::GetWindowScale()
{
	return c_windowScale;
}

const char* Game::GetWindowName()
{
	return c_windowName;
}
