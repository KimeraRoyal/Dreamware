#pragma once

#include <vector>

#include "ISprite.h"
#include "SpriteAnimation.h"

class Spritesheet final : public ISprite
{
private:
	std::vector<SpriteAnimation*> m_animations;

	int m_spriteWidth = 0;
	int m_spriteHeight = 0;

	bool m_animated = false;
	int m_currentAnimation = 0;
	int m_currentFrame = 0;

	[[nodiscard]] SDL_Rect GetFrameRect(int _frame) const;
public:
	Spritesheet(int _startingAnimation = 0);
	explicit Spritesheet(const std::string& _fileName, int _startingAnimation = 0);
	~Spritesheet() override;

	void Load(SDL_Texture* _texture, const char* _animationFileName);
	void Load(const char* _textureFileName, const char* _animationFileName);
	void Load(const std::string& _fileName);
	void Update() override;
	void Draw(SDL_Renderer* _renderer, int _x, int _y, int _animation, int _currentFrame);
	void Draw(SDL_Renderer* _renderer, int _x, int _y) override;

	[[nodiscard]] int GetSpriteWidth() const;
	[[nodiscard]] int GetSpriteHeight() const;
	
	[[nodiscard]] int GetCurrentAnimation() const;
	
	void SetAnimation(int _animation);
};

