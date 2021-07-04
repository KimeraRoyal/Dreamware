#include "GraphicManager.h"

#include <cstdio>

#include "ScreenManager.h"
#include "Game.h"

GraphicManager* GraphicManager::s_instance = nullptr;

GraphicManager::GraphicManager() = default;

GraphicManager::~GraphicManager()
{
	Unload();
}

void GraphicManager::Load(SDL_Window* _window)
{
	m_window = _window;
	m_surface = SDL_GetWindowSurface(_window);
	m_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | (c_vsyncEnabled ? SDL_RENDERER_PRESENTVSYNC : 0));

	SDL_RenderSetLogicalSize(m_renderer, Game::GetWindowWidth(), Game::GetWindowHeight());
	SDL_RenderSetIntegerScale(m_renderer, SDL_TRUE);

	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
	
#ifdef _DEBUG
	printf("Graphic Manager Loaded\n");
#endif
}

void GraphicManager::Unload()
{
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;

#ifdef _DEBUG
	printf("Graphic Manager Unloaded\n");
#endif
}

void GraphicManager::Update() const
{
	// SDL_RenderClear(m_renderer);
	ScreenManager::GetInstance()->Draw();
	SDL_RenderPresent(m_renderer);
}

SDL_Surface* GraphicManager::GetSurface() const
{
	return m_surface;
}

SDL_Renderer* GraphicManager::GetRenderer() const
{
	return m_renderer;
}

GraphicManager* GraphicManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new GraphicManager();
	}

	return s_instance;
}

void GraphicManager::DeleteInstance()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}
