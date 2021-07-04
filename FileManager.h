#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

class FileManager
{
private:
	static FileManager* s_instance;
	FileManager();
	
	std::string m_basePath;
	
public:
	~FileManager();
	
	FileManager(FileManager const&) = delete;
	FileManager(FileManager const&&) = delete;
	void operator=(FileManager const&) = delete;
	void operator=(FileManager const&&) = delete;
	
	void Load();
	static void Unload();
	
	[[nodiscard]] std::string GetRelativePath(const std::string& _fileName) const;
	[[nodiscard]] static SDL_Texture* GetTexture(const std::string& _fileName);
	[[nodiscard]] static char* GetTextFile(const std::string& _fileName);
	[[nodiscard]] static TTF_Font* GetFont(const std::string& _fileName, int _fontSize);

	[[nodiscard]] static char* ReadTextFile(const char* _fileName, size_t* _fileSize);
	[[nodiscard]] static char* ReadTextFile(const char* _fileName);
	
	[[nodiscard]] static SDL_Texture* LoadTexture(const char* _fileName);
	[[nodiscard]] static TTF_Font* LoadFont(const char* _fileName, int _fontSize);

	static FileManager* GetInstance();
	static void DeleteInstance();
};
