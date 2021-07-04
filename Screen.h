#pragma once

#include "SDL.h"

class Screen
{
private:
	bool m_isRunning = true;
public:
	virtual ~Screen() = default;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual bool Update() = 0;
	virtual void Draw(SDL_Renderer* _renderer) = 0;

	bool GetRunning() const;
	void SetRunning(bool _running);
};

