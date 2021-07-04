#include "AudioManager.h"

#include <fmod_errors.h>
#include <cstdio>

#include "FileManager.h"

AudioManager* AudioManager::s_instance = nullptr;

AudioManager::AudioManager() = default;

AudioManager::~AudioManager()
{
	Unload();
}

void AudioManager::Load()
{
	ErrorCheck(FMOD::Studio::System::create(&m_studioSystem));
	ErrorCheck(m_studioSystem->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr));

	LoadBank("Master.bank");
	LoadBank("Master.strings.bank");

#ifdef _DEBUG
	printf("Audio Manager Loaded\n");
#endif
}

void AudioManager::Unload()
{
	for (auto* bank : m_banks)
	{
		bank->unload();
	}
	
	ErrorCheck(m_studioSystem->release());

#ifdef _DEBUG
	printf("Audio Manager Unloaded\n");
#endif
}

void AudioManager::Update() const
{
	m_studioSystem->update();
}

void AudioManager::LoadBank(const char* _bankName)
{
	FMOD::Studio::Bank* loadedBank;
	ErrorCheck(m_studioSystem->loadBankFile(FileManager::GetInstance()->GetRelativePath(_bankName).c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &loadedBank));

	m_banks.push_back(loadedBank);
}

FMOD::Studio::EventDescription* AudioManager::GetEvent(const char* _eventName) const
{
	FMOD::Studio::EventDescription* returnEvent;
	ErrorCheck(m_studioSystem->getEvent(_eventName, &returnEvent));

	return returnEvent;
}

FMOD::Studio::EventInstance* AudioManager::CreateEventInstance(FMOD::Studio::EventDescription* _eventDescription)
{
	FMOD::Studio::EventInstance* returnInstance;
	ErrorCheck(_eventDescription->createInstance(&returnInstance));

	return returnInstance;
}

void AudioManager::ErrorCheck(const FMOD_RESULT _result)
{
	if(_result != FMOD_OK)
	{
		printf("FMOD Encountered an Error: (%d) %s\n", _result, FMOD_ErrorString(_result));
		exit(-1);
	}
}

AudioManager* AudioManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new AudioManager();
	}

	return s_instance;
}

void AudioManager::DeleteInstance()
{
	if (s_instance != nullptr)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}
