#include "ScreenManager.h"

#include "GraphicManager.h"

#include "ScreenMenu.h"

ScreenManager* ScreenManager::s_instance = nullptr;

ScreenManager::ScreenManager() = default;

ScreenManager::~ScreenManager()
{
	Unload();
}

void ScreenManager::Load()
{
	AddScreen(new ScreenMenu(), true);
	
#ifdef _DEBUG
	printf("Screen Manager Loaded\n");
#endif
}

void ScreenManager::Unload()
{
	FlushScreens();

#ifdef _DEBUG
	printf("Screen Manager Unloaded\n");
#endif
}

bool ScreenManager::Update()
{
	UpdateScreenVector();
	
	for(auto& screen : m_screens)
	{
		if(!screen->GetRunning())
		{
			continue;
		}
		
		if(!screen->Update())
		{
			return false;
		}
	}

	UpdateScreenVector();
	
	return true;
}

void ScreenManager::Draw()
{
	for (auto& screen : m_screens)
	{
		screen->Draw(GraphicManager::GetInstance()->GetRenderer());
	}
}

void ScreenManager::UpdateScreenVector()
{
	if(m_flushingScreens)
	{
		for (auto& screen : m_screens)
		{
			UnloadScreen(screen);
		}
		m_screens.clear();
		m_removeScreens.clear();

		m_flushingScreens = false;
	}
	
	if (!m_removeScreens.empty())
	{
		for (auto& screen : m_removeScreens)
		{
			const auto index = GetScreenIndex(screen);
			if (index >= 0)
			{
				m_screens.erase(m_screens.begin() + index);
				delete screen;
				screen = nullptr;
			}
		}

		m_removeScreens.clear();
	}
	
	if (!m_newScreens.empty())
	{
		for (auto& screen : m_newScreens)
		{
			m_screens.push_back(screen);
		}

		m_newScreens.clear();
	}
}

void ScreenManager::SetScreen(Screen* _screen, const bool _loadScreen)
{
	FlushScreens();
	AddScreen(_screen, _loadScreen);
}

void ScreenManager::AddScreen(Screen* _screen, const bool _loadScreen)
{
	if(_screen == nullptr)
	{
		return;
	}
	
	if(_loadScreen)
	{
		_screen->Load();
	}
	m_newScreens.push_back(_screen);
}

void ScreenManager::InsertScreen(Screen* _screen, const unsigned _index, const bool _loadScreen)
{
	if (_screen == nullptr)
	{
		return;
	}
	
	const auto insertIndex = m_screens.begin() + _index;
	if(std::distance(insertIndex, m_screens.end()) == 0)
	{
		AddScreen(_screen, _loadScreen);
	}
	else
	{
		if(_loadScreen)
		{
			_screen->Load();
		}
		m_screens.insert(insertIndex, _screen);
	}
}

void ScreenManager::RemoveScreen(Screen*& _screen, const bool _unloadScreen)
{
	m_removeScreens.push_back(_screen);
}

Screen* ScreenManager::RemoveScreenAt(const unsigned _index, const bool _unloadScreen)
{
	auto& screen = m_newScreens[_index];
	m_removeScreens.push_back(screen);

	return screen;
}

Screen* ScreenManager::PopScreen(const bool _unloadScreen)
{
	auto& returnScreen = m_screens.back();
	m_screens.pop_back();

	if (_unloadScreen)
	{
		UnloadScreen(returnScreen);
	}

	return returnScreen;
}

void ScreenManager::FlushScreens()
{
	m_flushingScreens = true;
}

int ScreenManager::GetScreenIndex(Screen* _screen)
{
	auto returnIndex = -1;
	for (unsigned i = 0; i < m_screens.size(); i++)
	{
		if (m_screens[i] == _screen)
		{
			returnIndex = i;
		}
	}

	return returnIndex;
}

void ScreenManager::UnloadScreen(Screen*& _screen)
{
	_screen->Unload();
	delete _screen;
	_screen = nullptr;
}

ScreenManager* ScreenManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new ScreenManager();
	}

	return s_instance;
}

void ScreenManager::DeleteInstance()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}
