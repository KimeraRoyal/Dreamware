#include "AssetManager.h"

AssetManager* AssetManager::s_instance = nullptr;

AssetManager::AssetManager() = default;

AssetManager::~AssetManager()
{
	Unload();
}

void AssetManager::Unload()
{
	ClearTextures();
	ClearTextFiles();
	ClearFonts();
	
#ifdef _DEBUG
	printf("Asset Manager Unloaded\n");
#endif
}

SDL_Texture* AssetManager::GetTexture(const std::string& _name)
{
	const auto& iterator = m_textures.find(_name);
	if (iterator != m_textures.end())
	{
		auto& result = iterator->second;
		return result;
	}
	return nullptr;
}

char* AssetManager::GetTextFile(const std::string& _name)
{
	const auto &iterator = m_textFiles.find(_name);
	if (iterator != m_textFiles.end())
	{
		auto& result = iterator->second;
		return result;
	}
	return nullptr;
}

TTF_Font* AssetManager::GetFont(const std::string& _name)
{
	const auto& iterator = m_fonts.find(_name);
	if (iterator != m_fonts.end())
	{
		auto& result = iterator->second;
		return result;
	}
	return nullptr;
}

void AssetManager::AddTexture(const std::string& _name, SDL_Texture* _texture)
{
	m_textures.try_emplace(_name, _texture);
}

void AssetManager::AddTextFile(const std::string& _name, char* _textFile)
{
	m_textFiles.try_emplace(_name, _textFile);
}

void AssetManager::AddFont(const std::string& _name, TTF_Font* _font)
{
	m_fonts.try_emplace(_name, _font);
}

void AssetManager::RemoveTexture(const std::string& _name)
{
	const auto& textureIterator = m_textures.find(_name);
	auto& texture = textureIterator->second;
	SDL_DestroyTexture(texture);
	m_textures.erase(textureIterator);
}

void AssetManager::RemoveTextFile(const std::string& _name)
{
	const auto& textIterator = m_textFiles.find(_name);
	auto& textFile = textIterator->second;
	free(textFile);
	m_textFiles.erase(textIterator);
}

void AssetManager::RemoveFont(const std::string& _name)
{
	const auto& fontIterator = m_fonts.find(_name);
	auto& font = fontIterator->second;
	TTF_CloseFont(font);
	m_fonts.erase(fontIterator);
}

void AssetManager::ClearTextures()
{
	for (auto& [first, second] : m_textures)
	{
		auto& texture = second;
		SDL_DestroyTexture(texture);
	}
	
	m_textures.clear();
}

void AssetManager::ClearTextFiles()
{
	for (auto& [first, second] : m_textFiles)
	{
		char* textFile = second;
		free(textFile);
	}
	
	m_textFiles.clear();
}

void AssetManager::ClearFonts()
{
	for (auto& [first, second] : m_fonts)
	{
		auto& font = second;
		TTF_CloseFont(font);
	}

	m_fonts.clear();
}

AssetManager* AssetManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new AssetManager();
	}

	return s_instance;
}

void AssetManager::DeleteInstance()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}