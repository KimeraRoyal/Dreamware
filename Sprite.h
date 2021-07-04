#pragma once

#include "ISprite.h"

class Sprite final : public ISprite
{
public:
	Sprite() = default;
	explicit Sprite(const std::string& _fileName);
	
	void Load(const char* _textureFile);
	void Load(const std::string& _fileName);
	void Update() override;
	void Draw(SDL_Renderer* _renderer, int _x, int _y, double _angle) const;
	void Draw(SDL_Renderer* _renderer, int _x, int _y) override;
};
