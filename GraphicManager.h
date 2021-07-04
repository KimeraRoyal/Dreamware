#pragma once

#include <SDL.h>

class GraphicManager
{
private:
	static constexpr bool c_vsyncEnabled = true;
	
	static GraphicManager* s_instance;
	GraphicManager();

	SDL_Window* m_window = nullptr;
	SDL_Surface* m_surface = nullptr;
	SDL_Renderer* m_renderer = nullptr;
public:
	~GraphicManager();

	GraphicManager(GraphicManager const&) = delete;
	GraphicManager(GraphicManager const&&) = delete;
	void operator=(GraphicManager const&) = delete;
	void operator=(GraphicManager const&&) = delete;

	void Load(SDL_Window* _window);
	void Unload();

	void Update() const;

	[[nodiscard]] SDL_Surface* GetSurface() const;
	[[nodiscard]] SDL_Renderer* GetRenderer() const;
	
	static GraphicManager* GetInstance();
	static void DeleteInstance();
};

