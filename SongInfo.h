#pragma once

#include <string>
#include <rapidjson/document.h>

struct SongInfo
{
private:
	std::string m_name;
	std::string m_subtitle;
	std::string m_path;
public:
	explicit SongInfo(const rapidjson::Value& _song);

	std::string& GetName();
	std::string& GetSubtitle();
	std::string& GetPath();
};

