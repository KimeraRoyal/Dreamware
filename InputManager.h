#pragma once

#include <SDL_events.h>

enum class Key : unsigned short
{
	none =	0x0000,
	w =			0x0001,
	a =			0x0002,
	s =			0x0004,
	d =			0x0008,
	up =		0x0010,
	left =	0x0020,
	down =	0x0040,
	right = 0x0080,
	space = 0x0100,
	z =			0x0200,
	x =			0x0400,
	c =			0x0800,
	esc =		0x1000,
	all =		0x1FFF
};

struct KeyInputPair
{
	SDL_Scancode m_scancode = SDL_SCANCODE_UNKNOWN;
	Key m_key = Key::none;
};

class InputManager
{
private:
	static constexpr KeyInputPair c_keys[] =
	{
		{ SDL_SCANCODE_W, Key::w },
		{ SDL_SCANCODE_A, Key::a },
		{ SDL_SCANCODE_S, Key::s },
		{ SDL_SCANCODE_D, Key::d },
		{ SDL_SCANCODE_UP, Key::up },
		{ SDL_SCANCODE_LEFT, Key::left },
		{ SDL_SCANCODE_DOWN, Key::down },
		{ SDL_SCANCODE_RIGHT, Key::right },
		{ SDL_SCANCODE_SPACE, Key::space },
		{ SDL_SCANCODE_Z, Key::z },
		{ SDL_SCANCODE_X, Key::x },
		{ SDL_SCANCODE_C, Key::c },
		{ SDL_SCANCODE_ESCAPE, Key::esc },
	};
	
	static InputManager* s_instance;
	InputManager();

	int m_mouseX = 0;
	int m_mouseY = 0;

	int m_lastMouseX = 0;
	int m_lastMouseY = 0;

	bool m_mouseDown = false;
	bool m_lastMouseDown = false;

	unsigned short m_keyMap = 0;
	unsigned short m_lastKeyMap = 0;

	[[nodiscard]] bool GetLastKeyDown(Key _key) const;
public:
	~InputManager() = default;

	InputManager(InputManager const&) = delete;
	InputManager(InputManager const&&) = delete;
	void operator=(InputManager const&) = delete;
	void operator=(InputManager const&&) = delete;

	void Update();

	void HandleMouseInput(SDL_Event* _event);
	void HandleKeyboardInput(SDL_Event* _event);

	[[nodiscard]] int GetMouseX() const;
	[[nodiscard]] int GetMouseY() const;

	[[nodiscard]] bool GetMouseMoved() const;
	[[nodiscard]] bool GetMouseDown() const;
	[[nodiscard]] bool GetMousePressed() const;
	[[nodiscard]] bool GetMouseUnpressed() const;

	[[nodiscard]] bool GetKeyDown(Key _key) const;
	[[nodiscard]] bool GetKeyPressed(Key _key) const;
	[[nodiscard]] bool GetKeyUnpressed(Key _key) const;

	static InputManager* GetInstance();
	static void DeleteInstance();
};

