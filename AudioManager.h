#pragma once

#include <vector>

#include <fmod_studio.hpp>

class AudioManager
{
private:
	static AudioManager* s_instance;
	AudioManager();
	
	FMOD::Studio::System* m_studioSystem = nullptr;
	
	std::vector<FMOD::Studio::Bank*> m_banks;
public:
	~AudioManager();

	AudioManager(AudioManager const&) = delete;
	AudioManager(AudioManager const&&) = delete;
	void operator=(AudioManager const&) = delete;
	void operator=(AudioManager const&&) = delete;
	
	void Load();
	void Unload();
	void Update() const;

	void LoadBank(const char* _bankName);
	
	[[nodiscard]] FMOD::Studio::EventDescription* GetEvent(const char* _eventName) const;
	[[nodiscard]] static FMOD::Studio::EventInstance* CreateEventInstance(FMOD::Studio::EventDescription* _eventDescription);

	static void ErrorCheck(FMOD_RESULT _result);

	static AudioManager* GetInstance();
	static void DeleteInstance();
};