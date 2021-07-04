#pragma once

#include "Spritesheet.h"

class SpritesheetFrame final : public IGraphic
{
private:
	Spritesheet* m_spritesheet = nullptr;

	int m_animation = 0;
	int m_frame = 0;
	
public:
	explicit SpritesheetFrame(Spritesheet* _spritesheet, int _animation = 0, int _frame = 0);
	virtual ~SpritesheetFrame();
	
	void Update() override;
	void Draw(SDL_Renderer* _renderer, int _x, int _y) override;
};

