#pragma once

#include <SDL_ttf.h>

#include "IGraphic.h"

class Text final : public IGraphic
{
private:
	SDL_Renderer* m_renderer = nullptr;
	
	TTF_Font* m_font = nullptr;
	SDL_Texture* m_texture = nullptr;

	int m_fontSize;
	std::string m_text = "";
	SDL_Color m_colour = {255, 255, 255, 255};

	float m_offsetX = 0.0f;
	float m_offsetY = 0.0f;
	int m_pixelOffsetX = 0;
	int m_pixelOffsetY = 0;
	
	int m_width = 0;
	int m_height = 0;

	bool m_dirty = false;

	void CreateTexture();

	void SetPixelOffsetX();
	void SetPixelOffsetY();
	void SetPixelOffset();

	SDL_Renderer* FindRenderer();
	
public:
	explicit Text(int _fontSize);
	explicit Text(const std::string& _fontName, int _fontSize);
	explicit Text(const std::string& _fontName, int _fontSize, const std::string& _text, SDL_Color _colour);
	explicit Text(const std::string& _fontName, int _fontSize, const std::string& _text, float _offsetX = 0.0f, float _offsetY = 0.0f);
	explicit Text(const std::string& _fontName, int _fontSize, const std::string& _text, SDL_Color _colour, float _offsetX = 0.0f, float _offsetY = 0.0f);

	~Text() override;
	
	void Load(const char* _fontName, int _fontSize);
	void Load(const std::string& _fontName);
	void Update() override;
	void Draw(SDL_Renderer* _renderer, int _x, int _y) override;

	[[nodiscard]] int GetFontSize() const;
	std::string& GetText();

	[[nodiscard]] float GetOffsetX() const;
	[[nodiscard]] float GetOffsetY() const;

	[[nodiscard]] int GetWidth() const;
	[[nodiscard]] int GetHeight() const;

	void SetText(const std::string& _text);

	void SetColour(SDL_Color _colour);
	
	void SetOffsetX(float _offsetX);
	void SetOffsetY(float _offsetY);
	void SetOffset(float _offsetX, float _offsetY);
};

