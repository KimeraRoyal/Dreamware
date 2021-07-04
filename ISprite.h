#pragma once

#include "IGraphic.h"

class ISprite : public IGraphic
{
protected:
	SDL_Texture* m_texture = nullptr;
	
	int m_width = 0;
	int m_height = 0;
public:
	virtual ~ISprite();

	[[nodiscard]] int GetWidth() const;
	[[nodiscard]] int GetHeight() const;
};
