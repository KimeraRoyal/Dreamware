#pragma once

#include <SDL.h>

class Time
{
private:
	static Time* s_instance;
	Time();
	
	Uint64 m_lastCounterValue = 0;

	float m_deltaTime = 0;
public:
	void Update();

	[[nodiscard]] float GetDeltaTime() const;

	static Time* GetInstance();
	static void DeleteInstance();
};

