#include "Sprite.h"

#include "FileManager.h"

Sprite::Sprite(const std::string& _fileName)
{
	Load(_fileName.c_str());
}

void Sprite::Load(const char* _textureFile)
{
	m_texture = FileManager::GetTexture(_textureFile);
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);

#ifdef _DEBUG
	printf(">> Sprite Loaded\n");
#endif
}

void Sprite::Load(const std::string& _fileName)
{
	Load((_fileName + ".png").c_str());
}

void Sprite::Update()
{
	// Static sprites have no update functionality
}

void Sprite::Draw(SDL_Renderer* _renderer, const int _x, const int _y, const double _angle) const
{
	SDL_Rect srcRect = { 0, 0, m_width, m_height };
	SDL_Rect destRect = { _x, _y, m_width, m_height };
	SDL_RenderCopyEx(_renderer, m_texture, &srcRect, &destRect, _angle, nullptr, SDL_FLIP_NONE);
}

void Sprite::Draw(SDL_Renderer* _renderer, const int _x, const int _y)
{
	SDL_Rect srcRect = { 0, 0, m_width, m_height };
	SDL_Rect destRect = { _x, _y, m_width, m_height };
	SDL_RenderCopy(_renderer, m_texture, &srcRect, &destRect);
}
