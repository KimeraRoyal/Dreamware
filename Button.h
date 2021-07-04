#pragma once

#include "IGraphic.h"

class Button
{
private:
	IGraphic* m_graphic = nullptr;

	int m_X = 0;
	int m_Y = 0;

	int m_width = 0;
	int m_height = 0;

	int m_offsetX = 0;
	int m_offsetY = 0;

	int m_paddingX = 0;
	int m_paddingY = 0;

	bool m_isMouseHovered = false;
public:
	Button(IGraphic* _graphic, int _x, int _y, int _width, int _height, int _paddingX, int _paddingY, int _offsetX = 0, int _offsetY = 0);
	~Button();

	void Update();
	void Draw(SDL_Renderer* _renderer) const;

	[[nodiscard]] bool IsPointWithinBounds(int _x, int _y) const;

	[[nodiscard]] int GetX() const;
	[[nodiscard]] int GetY() const;

	[[nodiscard]] int GetWidth() const;
	[[nodiscard]] int GetHeight() const;

	[[nodiscard]] int GetPaddingX() const;
	[[nodiscard]] int GetPaddingY() const;

	[[nodiscard]] int GetOffsetX() const;
	[[nodiscard]] int GetOffsetY() const;

	[[nodiscard]] bool IsMouseHovered() const;
	
	void SetX(int _x);
	void SetY(int _y);
	void SetPosition(int _x, int _y);

	void SetWidth(int _width);
	void SetHeight(int _height);
	void SetSize(int _width, int _height);

	void SetRect(int _x, int _y, int _width, int _height);

	void SetPaddingX(int _padding);
	void SetPaddingY(int _padding);
	void SetPadding(int _x, int _y);
	void SetPadding(int _padding);

	void SetOffsetX(int _x);
	void SetOffsetY(int _y);
	void SetOffset(int _x, int _y);
};

