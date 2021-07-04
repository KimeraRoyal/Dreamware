#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Game
{
private:
	static Game* s_instance;
	Game() = default;
	
	static constexpr int c_windowWidth = 480;
	static constexpr int c_windowHeight = 352;
	static constexpr int c_windowScale = 2;
	static constexpr char c_windowName[] = "Dustworld";

	static constexpr int c_imgFlags = IMG_INIT_PNG;
	static constexpr int c_sdlFlags = SDL_INIT_VIDEO;
	static constexpr int c_windowFlags = SDL_WINDOW_SHOWN;
	
	SDL_Window* m_window = nullptr;

	int m_highScore = 2000;
	int m_currentScore = 0;
public:
	~Game();

	Game(Game const&) = delete;
	Game(Game const&&) = delete;
	void operator=(Game const&) = delete;
	void operator=(Game const&&) = delete;
	
	void Init();
	void Load() const;
	void Unload() const;

	void GameLoop();
	static bool PollEvents();
	static bool Update();

	void SetScore(int _score);
	
	void AddScore(int _score);
	void RemoveScore(int _score);

	[[nodiscard]] int GetScore() const;
	[[nodiscard]] int GetHighScore() const;

	static Game* GetInstance();
	static void DeleteInstance();

	static int GetWindowWidth();
	static int GetWindowHeight();
	static int GetWindowScale();
	static const char* GetWindowName();
};