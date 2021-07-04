#pragma once

#include <vector>

#include "rapidjson/document.h"

struct SpriteAnimation
{
private:
	bool m_resetFrames = false;
	int m_length = 0;
	std::vector<int> m_frames;
public:
	explicit SpriteAnimation(const rapidjson::Value& _animation);

	[[nodiscard]] bool ResetsFrames() const;
	[[nodiscard]] int GetLength() const;
	[[nodiscard]] int GetFrameCount() const;
	
	[[nodiscard]] int GetFrame(int _index);
};

