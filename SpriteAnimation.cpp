#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(const rapidjson::Value& _animation)
{
	if(_animation.HasMember("resetFrames"))
	{
		m_resetFrames = _animation["resetFrames"].GetBool();
	}
	m_length = _animation["length"].GetInt();
	
	const auto& frames = _animation["frames"];
	assert(frames.IsArray());
	for(rapidjson::SizeType i = 0; i < frames.Size(); i++)
	{
		m_frames.push_back(frames[i].GetInt());
	}
}

bool SpriteAnimation::ResetsFrames() const
{
	return m_resetFrames;
}

int SpriteAnimation::GetLength() const
{
	return m_length;
}

int SpriteAnimation::GetFrameCount() const
{
	return m_frames.size();
}

int SpriteAnimation::GetFrame(const int _index)
{
	return m_frames[_index];
}
