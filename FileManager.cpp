#include "FileManager.h"

#include <SDL_image.h>

#include "AssetManager.h"
#include "GraphicManager.h"

FileManager* FileManager::s_instance = nullptr;

FileManager::FileManager() = default;

FileManager::~FileManager()
{
	Unload();
}

void FileManager::Load()
{
	auto* basePath = SDL_GetBasePath();
	m_basePath = basePath;
	
	SDL_free(basePath);

#ifdef _DEBUG
	printf("File Manager Loaded\n");
#endif
}

void FileManager::Unload()
{
	AssetManager::DeleteInstance();
	
#ifdef _DEBUG
	printf("File Manager Unloaded\n");
#endif
}

std::string FileManager::GetRelativePath(const std::string& _fileName) const
{
	return m_basePath + _fileName;
}

SDL_Texture* FileManager::GetTexture(const std::string& _fileName)
{
	auto* texture = AssetManager::GetInstance()->GetTexture(_fileName);
	if(texture != nullptr)
	{
		return texture;
	}
	
	texture = LoadTexture(_fileName.c_str());
	AssetManager::GetInstance()->AddTexture(_fileName, texture);

	return texture;
}

char* FileManager::GetTextFile(const std::string& _fileName)
{
	auto* textFile = AssetManager::GetInstance()->GetTextFile(_fileName);
	if(textFile != nullptr)
	{
		return textFile;
	}

	textFile = ReadTextFile(_fileName.c_str());
	AssetManager::GetInstance()->AddTextFile(_fileName, textFile);

	return textFile;
}

TTF_Font* FileManager::GetFont(const std::string& _fileName, const int _fontSize)
{
	const auto fontKey = _fileName + std::to_string(_fontSize);
	auto* font = AssetManager::GetInstance()->GetFont(fontKey);
	if (font != nullptr)
	{
		return font;
	}

	font = LoadFont(_fileName.c_str(), _fontSize);
	AssetManager::GetInstance()->AddFont(fontKey, font);

	return font;
}

char* FileManager::ReadTextFile(const char* _fileName, size_t* _fileSize)
{
	auto* fileRw = SDL_RWFromFile(_fileName, "rb");
	if (fileRw == nullptr)
	{
		printf("File at %s could not be loaded! SDL Error:%s\n", _fileName, SDL_GetError());
		exit(-1);
	}

	const auto fileSize = static_cast<size_t>(SDL_RWsize(fileRw));
	auto* fileData = static_cast<char*>(malloc(fileSize + 1));

	size_t totalDataRead = 0;
	size_t dataRead = 1;

	auto* buffer = fileData;
	while (totalDataRead < fileSize && dataRead != 0)
	{
		dataRead = SDL_RWread(fileRw, buffer, 1, (fileSize - totalDataRead));
		totalDataRead += dataRead;
		buffer += dataRead;
	}

	SDL_RWclose(fileRw);
	if (totalDataRead != fileSize)
	{
		printf("File at %s was not read correctly! SDL Error:%s\n", _fileName, SDL_GetError());
		free(fileData);
		exit(-1);
	}

	if(_fileSize != nullptr)
	{
		*_fileSize = fileSize;
	}

	fileData[totalDataRead] = '\0';
	return fileData;
}

char* FileManager::ReadTextFile(const char* _fileName)
{
	return ReadTextFile(_fileName, nullptr);
}

SDL_Texture* FileManager::LoadTexture(const char* _fileName)
{
	SDL_Texture* texture = nullptr;

	auto* textureSurface = IMG_Load(_fileName);
	if(textureSurface == nullptr)
	{
		printf("File at %s could not be loaded! SDL Error:%s\n", _fileName, SDL_GetError());
		exit(-1);
	}

	texture = SDL_CreateTextureFromSurface(GraphicManager::GetInstance()->GetRenderer(), textureSurface);
	SDL_FreeSurface(textureSurface);
	if(texture == nullptr)
	{
		printf("File at %s could not be converted to a texture! SDL Error:%s\n", _fileName, SDL_GetError());
		exit(-1);
	}
	
	return texture;
}

TTF_Font* FileManager::LoadFont(const char* _fileName, const int _fontSize)
{
	TTF_Font* font = TTF_OpenFont(_fileName, _fontSize);
	if(font == nullptr)
	{
		printf("File at %s could not be loaded! SDL Error:%s\n", _fileName, SDL_GetError());
		exit(-1);
	}

	return font;
}

FileManager* FileManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new FileManager();
	}

	return s_instance;
}

void FileManager::DeleteInstance()
{
	if(s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}
