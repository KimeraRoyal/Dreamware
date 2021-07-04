#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_ttf.h>

class AssetManager
{
private:
	static AssetManager* s_instance;
	AssetManager();

	std::unordered_map<std::string, SDL_Texture*> m_textures;
	std::unordered_map<std::string, char*> m_textFiles;
	std::unordered_map<std::string, TTF_Font*> m_fonts;
	
public:
	~AssetManager();

	AssetManager(AssetManager const&) = delete;
	AssetManager(AssetManager const&&) = delete;
	void operator=(AssetManager const&) = delete;
	void operator=(AssetManager const&&) = delete;

	void Unload();
	
	SDL_Texture* GetTexture(const std::string& _name);
	char* GetTextFile(const std::string& _name);
	TTF_Font* GetFont(const std::string& _name);

	void AddTexture(const std::string& _name, SDL_Texture* _texture);
	void AddTextFile(const std::string& _name, char* _textFile);
	void AddFont(const std::string& _name, TTF_Font* _font);

	void RemoveTexture(const std::string& _name);
	void RemoveTextFile(const std::string& _name);
	void RemoveFont(const std::string& _name);

	void ClearTextures();
	void ClearTextFiles();
	void ClearFonts();
	
	static AssetManager* GetInstance();
	static void DeleteInstance();
};

