#include "Screen.h"

bool Screen::GetRunning() const
{
	return m_isRunning;
}

void Screen::SetRunning(const bool _running)
{
	m_isRunning = _running;
}
