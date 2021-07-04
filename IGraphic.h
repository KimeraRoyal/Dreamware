#pragma once

#include <string>

#include <SDL.h>

class IGraphic
{
public:
	virtual ~IGraphic() = default;
	
	virtual void Update() = 0;
	virtual void Draw(SDL_Renderer* _renderer, int _x, int _y) = 0;
};

