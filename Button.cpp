#include "Button.h"

#include "InputManager.h"

Button::Button(IGraphic* _graphic, const int _x, const int _y, const int _width, const int _height, const int _paddingX, const int _paddingY, const int _offsetX, const int _offsetY)
{
	m_graphic = _graphic;
	SetRect(_x, _y, _width, _height);
	SetPadding(_paddingX, _paddingY);
	SetOffset(_offsetX, _offsetY);
}

Button::~Button()
{
	delete m_graphic;
	m_graphic = nullptr;
}

void Button::Update()
{
	m_isMouseHovered = IsPointWithinBounds(InputManager::GetInstance()->GetMouseX(), InputManager::GetInstance()->GetMouseY());
	
	m_graphic->Update();
}

void Button::Draw(SDL_Renderer* _renderer) const
{
	m_graphic->Draw(_renderer, m_X, m_Y);
}

bool Button::IsPointWithinBounds(const int _x, const int _y) const
{
	return
		_x > m_X + m_offsetX - m_paddingX &&
		_x < m_X + m_offsetX + m_width + m_paddingX &&
		_y > m_Y + m_offsetY - m_paddingY &&
		_y < m_Y + m_offsetY + m_height + m_paddingY;
}

int Button::GetX() const
{
	return m_X;
}

int Button::GetY() const
{
	return m_Y;
}

int Button::GetWidth() const
{
	return m_width;
}

int Button::GetHeight() const
{
	return m_height;
}

int Button::GetPaddingX() const
{
	return m_paddingX;
}

int Button::GetPaddingY() const
{
	return m_paddingY;
}

int Button::GetOffsetX() const
{
	return m_offsetX;
}

int Button::GetOffsetY() const
{
	return m_offsetY;
}

bool Button::IsMouseHovered() const
{
	return m_isMouseHovered;
}

void Button::SetX(const int _x)
{
	m_X = _x;
}

void Button::SetY(const int _y)
{
	m_Y = _y;
}

void Button::SetPosition(const int _x, const int _y)
{
	SetX(_x);
	SetY(_y);
}

void Button::SetWidth(const int _width)
{
	m_width = _width;
}

void Button::SetHeight(const int _height)
{
	m_height = _height;
}

void Button::SetSize(const int _width, const int _height)
{
	SetWidth(_width);
	SetHeight(_height);
}

void Button::SetRect(const int _x, const int _y, const int _width, const int _height)
{
	SetPosition(_x, _y);
	SetSize(_width, _height);
}

void Button::SetPaddingX(const int _padding)
{
	m_paddingX = _padding;
}

void Button::SetPaddingY(const int _padding)
{
	m_paddingY = _padding;
}

void Button::SetPadding(const int _x, const int _y)
{
	SetPaddingX(_x);
	SetPaddingY(_y);
}

void Button::SetPadding(const int _padding)
{
	SetPadding(_padding, _padding);
}

void Button::SetOffsetX(const int _x)
{
	m_offsetX = _x;
}

void Button::SetOffsetY(const int _y)
{
	m_offsetY = _y;
}

void Button::SetOffset(const int _x, const int _y)
{
	SetOffsetX(_x);
	SetOffsetY(_y);
}
