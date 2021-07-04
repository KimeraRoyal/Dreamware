#include "SpritesheetFrame.h"

SpritesheetFrame::SpritesheetFrame(Spritesheet* _spritesheet, const int _animation, const int _frame)
{
	m_spritesheet = _spritesheet;
	m_animation = _animation;
	m_frame = _frame;

#ifdef _DEBUG
	printf(">> Spritesheet Frame Loaded\n");
#endif
}

SpritesheetFrame::~SpritesheetFrame()
{
#ifdef _DEBUG
	printf(">> Spritesheet Frame Unloaded\n");
#endif
}

void SpritesheetFrame::Update()
{
	
}

void SpritesheetFrame::Draw(SDL_Renderer* _renderer, const int _x, const int _y)
{
	m_spritesheet->Draw(_renderer, _x, _y, m_animation, m_frame);
}
