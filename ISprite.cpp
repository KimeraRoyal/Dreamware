#include "ISprite.h"

ISprite::~ISprite()
{
	m_texture = nullptr;

#ifdef _DEBUG
	printf(">> ISprite Unloaded\n");
#endif
}

int ISprite::GetWidth() const
{
	return m_width;
}

int ISprite::GetHeight() const
{
	return m_height;
}
