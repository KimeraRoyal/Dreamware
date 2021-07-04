#include "Spritesheet.h"

#include "FileManager.h"

Spritesheet::Spritesheet(const int _startingAnimation)
{
	SetAnimation(_startingAnimation);
}

Spritesheet::Spritesheet(const std::string& _fileName, const int _startingAnimation)
	: Spritesheet(_startingAnimation)
{
	Load(_fileName);
}

Spritesheet::~Spritesheet()
{
	for (auto* animation : m_animations)
	{
		delete animation;
	}
	m_animations.clear();

#ifdef _DEBUG
	printf(">> Spritesheet Unloaded\n");
#endif
}

void Spritesheet::Load(SDL_Texture* _texture, const char* _animationFileName)
{
	m_texture = _texture;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);

	auto* animationJson = FileManager::GetTextFile(_animationFileName);

	rapidjson::Document animationDoc;
	animationDoc.Parse(animationJson);

	m_spriteWidth = animationDoc["width"].GetInt();
	m_spriteHeight = animationDoc["height"].GetInt();

	if (animationDoc.HasMember("animated"))
	{
		m_animated = animationDoc["animated"].GetBool();
	}

	const auto& animations = animationDoc["animations"];
	assert(animations.IsArray());
	for (rapidjson::SizeType i = 0; i < animations.Size(); i++)
	{
		m_animations.push_back(new SpriteAnimation(animations[i]));
	}

#ifdef _DEBUG
	printf(">> Spritesheet Loaded\n");
#endif
}

void Spritesheet::Load(const char* _textureFileName, const char* _animationFileName)
{
	SDL_Texture* texture = FileManager::GetTexture(_textureFileName);
	Load(texture, _animationFileName);
}

void Spritesheet::Load(const std::string& _fileName)
{
	Load((_fileName + ".png").c_str(), (_fileName + ".json").c_str());
}

void Spritesheet::Update()
{
	if(!m_animated)
	{
		return;
	}
	
	m_currentFrame++;
}

void Spritesheet::Draw(SDL_Renderer* _renderer, const int _x, const int _y, const int _animation, const int _currentFrame)
{
	const auto spritesheetFrame = m_animations[_animation]->GetFrame(_currentFrame / m_animations[_animation]->GetLength() % m_animations[_animation]->GetFrameCount());

	auto srcRect = GetFrameRect(spritesheetFrame);
	SDL_Rect destRect = { _x, _y, m_spriteWidth, m_spriteHeight };
	SDL_RenderCopy(_renderer, m_texture, &srcRect, &destRect);
}

void Spritesheet::Draw(SDL_Renderer* _renderer, const int _x, const int _y)
{
	Draw(_renderer, _x, _y, m_currentAnimation, m_currentFrame);
}

SDL_Rect Spritesheet::GetFrameRect(const int _frame) const
{
	const auto rows = m_width / m_spriteWidth;
	const auto x = _frame % rows;
	const auto y = _frame / rows;

	const SDL_Rect returnRect = { x * m_spriteWidth, y * m_spriteHeight, m_spriteWidth, m_spriteHeight };
	return returnRect;
}

int Spritesheet::GetSpriteWidth() const
{
	return m_spriteWidth;
}

int Spritesheet::GetSpriteHeight() const
{
	return m_spriteHeight;
}

int Spritesheet::GetCurrentAnimation() const
{
	return m_currentAnimation;
}


void Spritesheet::SetAnimation(const int _animation)
{
	m_currentAnimation = _animation;
}