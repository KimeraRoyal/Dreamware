#pragma once

#include <vector>

#include <SDL.h>

#include "Screen.h"

class ScreenManager
{
private:
	static ScreenManager* s_instance;
	ScreenManager();

	std::vector<Screen*> m_screens;
	std::vector<Screen*> m_newScreens;
	std::vector<Screen*> m_removeScreens;

	bool m_flushingScreens = false;

	void UpdateScreenVector();
public:
	~ScreenManager();

	ScreenManager(ScreenManager const&) = delete;
	ScreenManager(ScreenManager const&&) = delete;
	void operator=(ScreenManager const&) = delete;
	void operator=(ScreenManager const&&) = delete;

	void Load();
	void Unload();
	bool Update();
	void Draw();

	void SetScreen(Screen* _screen, bool _loadScreen = false);
	void AddScreen(Screen* _screen, bool _loadScreen = false);
	void InsertScreen(Screen* _screen, unsigned _index, bool _loadScreen = false);
	
	void RemoveScreen(Screen*& _screen, bool _unloadScreen = false);
	Screen* RemoveScreenAt(unsigned _index, bool _unloadScreen = false);
	Screen* PopScreen(bool _unloadScreen = false);

	void FlushScreens();

	[[nodiscard]] int GetScreenIndex(Screen* _screen);

	static void UnloadScreen(Screen*& _screen);
	
	static ScreenManager* GetInstance();
	static void DeleteInstance();
};

