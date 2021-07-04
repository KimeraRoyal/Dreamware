#include "InputManager.h"

#include <cstdio>

#include <SDL.h>

#include "Game.h"

InputManager* InputManager::s_instance = nullptr;

InputManager::InputManager() = default;

void InputManager::Update()
{
	m_lastMouseX = m_mouseX;
	m_lastMouseY = m_mouseY;
	m_lastMouseDown = m_mouseDown;

	m_lastKeyMap = m_keyMap;
}

void InputManager::HandleMouseInput(SDL_Event* _event)
{
	switch(_event->type)
	{
		case SDL_MOUSEMOTION:
		{
			SDL_GetMouseState(&m_mouseX, &m_mouseY);
			m_mouseX /= Game::GetWindowScale();
			m_mouseY /= Game::GetWindowScale();
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		{
			m_mouseDown = SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT);
			break;
		}
		default:
		{
			break;
		}
	}
}

void InputManager::HandleKeyboardInput(SDL_Event* _event)
{
	Key key = Key::none;
	for (const auto& keyInputPair : c_keys)
	{
		if(_event->key.keysym.scancode == keyInputPair.m_scancode)
		{
			key = keyInputPair.m_key;
			break;
		}
	}

	if(_event->type == SDL_KEYDOWN)
	{
		m_keyMap |= static_cast<unsigned short>(key);
	}
	else
	{
		m_keyMap &= ~static_cast<unsigned short>(key);
	}
}

int InputManager::GetMouseX() const
{
	return m_mouseX;
}

int InputManager::GetMouseY() const
{
	return m_mouseY;
}

bool InputManager::GetMouseMoved() const
{
	return m_mouseX != m_lastMouseX || m_mouseY != m_lastMouseY;
}

bool InputManager::GetMouseDown() const
{
	return m_mouseDown;
}

bool InputManager::GetMousePressed() const
{
	return m_mouseDown && !m_lastMouseDown;
}

bool InputManager::GetMouseUnpressed() const
{
	return !m_mouseDown && m_lastMouseDown;
}

bool InputManager::GetKeyDown(const Key _key) const
{
	return m_keyMap & static_cast<unsigned short>(_key);
}

bool InputManager::GetLastKeyDown(const Key _key) const
{
	return m_lastKeyMap & static_cast<unsigned short>(_key);
}

bool InputManager::GetKeyPressed(const Key _key) const
{
	return GetKeyDown(_key) && !GetLastKeyDown(_key);
}

bool InputManager::GetKeyUnpressed(const Key _key) const
{
	return !GetKeyDown(_key) && GetLastKeyDown(_key);
}

InputManager* InputManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new InputManager();
	}

	return s_instance;
}

void InputManager::DeleteInstance()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}
