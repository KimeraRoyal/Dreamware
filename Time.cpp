#include "Time.h"

Time* Time::s_instance = nullptr;

Time::Time() = default;

void Time::Update()
{
	const Uint64 currentCounterValue = SDL_GetPerformanceCounter();

	if (m_lastCounterValue)
	{
		m_deltaTime = static_cast<float>((currentCounterValue - m_lastCounterValue) * 1000) / static_cast<float>(SDL_GetPerformanceFrequency()) * 0.001f;
	}
	
	m_lastCounterValue = currentCounterValue;
}

float Time::GetDeltaTime() const
{
	return m_deltaTime;
}

Time* Time::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Time();
	}

	return s_instance;
}

void Time::DeleteInstance()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}
