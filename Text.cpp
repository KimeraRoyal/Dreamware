#include "Text.h"

#include "FileManager.h"
#include "GraphicManager.h"

Text::Text(const int _fontSize)
{
	m_fontSize = _fontSize;
}

Text::Text(const std::string& _fontName, const int _fontSize)
	: Text(_fontSize)
{
	Load(_fontName);
}

Text::Text(const std::string& _fontName, int _fontSize, const std::string& _text, const SDL_Color _colour)
	: Text(_fontName, _fontSize)
{
	SetText(_text);
	SetColour(_colour);

	CreateTexture();
}

Text::Text(const std::string& _fontName, const int _fontSize, const std::string& _text, const float _offsetX, const float _offsetY)
	: Text(_fontName, _fontSize)
{
	SetText(_text);
	SetOffset(_offsetX, _offsetY);

	CreateTexture();
}

Text::Text(const std::string& _fontName, const int _fontSize, const std::string& _text, const SDL_Color _colour, const float _offsetX, const float _offsetY)
	: Text(_fontName, _fontSize)
{
	SetText(_text);
	SetColour(_colour);
	SetOffset(_offsetX, _offsetY);

	CreateTexture();
}


Text::~Text()
{
	SDL_DestroyTexture(m_texture);
	
	m_texture = nullptr;
	m_font = nullptr;

#ifdef _DEBUG
	printf(">> Text Unloaded\n");
#endif
}

void Text::Load(const char* _fontName, const int _fontSize)
{
	m_font = FileManager::GetFont(_fontName, _fontSize);
	m_fontSize = _fontSize;

#ifdef _DEBUG
	printf(">> Text Loaded\n");
#endif
}

void Text::Load(const std::string& _fontName)
{
	Load(_fontName.c_str(), m_fontSize);
}

void Text::Update()
{
	if(m_dirty)
	{
		CreateTexture();
	}
}

void Text::Draw(SDL_Renderer* _renderer, const int _x, const int _y)
{
	SDL_Rect destRect = { _x - m_pixelOffsetX, _y - m_pixelOffsetY, m_width, m_height };
	SDL_RenderCopy(_renderer, m_texture, nullptr, &destRect);
}

void Text::CreateTexture()
{
	SDL_Surface* surface = nullptr;
	surface = TTF_RenderText_Blended(m_font, m_text.c_str(), m_colour);

	if(m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
	}
	m_texture = SDL_CreateTextureFromSurface(FindRenderer(), surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
	SetPixelOffset();
	
	m_dirty = false;
}

void Text::SetText(const std::string& _text)
{
	m_text = _text;
	m_dirty = true;
}

void Text::SetColour(const SDL_Color _colour)
{
	m_colour = _colour;
	m_dirty = true;
}

SDL_Renderer* Text::FindRenderer()
{
	if(m_renderer == nullptr)
	{
		m_renderer = GraphicManager::GetInstance()->GetRenderer();
	}
	
	return m_renderer;
}

int Text::GetFontSize() const
{
	return m_fontSize;
}

std::string& Text::GetText()
{
	return m_text;
}

float Text::GetOffsetX() const
{
	return m_offsetX;
}

float Text::GetOffsetY() const
{
	return m_offsetY;
}

int Text::GetWidth() const
{
	return m_width;
}

int Text::GetHeight() const
{
	return m_height;
}

void Text::SetPixelOffsetX()
{
	m_pixelOffsetX = static_cast<int>(static_cast<float>(m_width) * m_offsetX);
}

void Text::SetPixelOffsetY()
{
	m_pixelOffsetY = static_cast<int>(static_cast<float>(m_height) * m_offsetY);
}

void Text::SetPixelOffset()
{
	SetPixelOffsetX();
	SetPixelOffsetY();
}

void Text::SetOffsetX(const float _offsetX)
{
	m_offsetX = _offsetX;
	SetPixelOffsetX();
}

void Text::SetOffsetY(const float _offsetY)
{
	m_offsetY = _offsetY;
	SetPixelOffsetY();
}

void Text::SetOffset(const float _offsetX, const float _offsetY)
{
	SetOffsetX(_offsetX);
	SetOffsetY(_offsetY);
}
