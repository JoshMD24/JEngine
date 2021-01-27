#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <string>
#include <map>
#include <memory>
#include <fmod.hpp>
#include <glm/glm.hpp>
#include "..//Core/Debug.h"
#include "AudioSource.h"

class AudioHandler
{
public:

	AudioHandler(const AudioHandler&) = delete;
	AudioHandler(AudioHandler&&) = delete;
	AudioHandler& operator = (const AudioHandler&) = delete;
	AudioHandler& operator = (AudioHandler&&) = delete;

	static AudioHandler* GetInstance();

	bool Initialize(glm::vec3 pos_, glm::vec3 vel_, glm::vec3 forwardDir_, glm::vec3 upDir_);
	void OnDestroy();
	void Update();

private:
	AudioHandler();
	~AudioHandler();

	friend class AudioSource;

	static std::unique_ptr<AudioHandler> audioInstance;
	friend std::default_delete<AudioHandler>;

	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 forwardDir;
	glm::vec3 upDir;

	FMOD_VECTOR glmToFMOD(glm::vec3 input_);
	void LoadSound(std::string fileName_, bool loop_, bool threeD_, bool play_);
	FMOD::Sound* GetSound(std::string sound_);
	int PlaySound(std::string soundName_, glm::vec3 pos_, glm::vec3 vel_, float volume_);
	void UpdatePosAndVel(int channelID_, glm::vec3 pos_, glm::vec3 vel_);
	bool isPlaying(int channel_);

	int drivers;
	FMOD::System* soundSystem;
	static std::map<std::string, FMOD::Sound*> sounds;
	static std::map<int, FMOD::Channel*> channels;
	int createdChannels = 1;
};

#endif