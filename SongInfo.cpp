#include "SongInfo.h"

SongInfo::SongInfo(const rapidjson::Value& _song)
{
	m_name = _song["name"].GetString();
	m_subtitle = _song["subtitle"].GetString();
	m_path = _song["path"].GetString();
}

std::string& SongInfo::GetName()
{
	return m_name;
}

std::string& SongInfo::GetSubtitle()
{
	return m_subtitle;
}

std::string& SongInfo::GetPath()
{
	return m_path;
}
