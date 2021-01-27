#include "AudioSource.h"
#include "AudioHandler.h"

AudioSource::AudioSource(std::string fileName_, bool loop_, bool threeD_, bool play_)
{
	int channelID = -1;
	fileName = fileName_;
	AudioHandler::GetInstance()->LoadSound(fileName_, loop_, threeD_, play_);
}

AudioSource::~AudioSource()
{
	gameObject = nullptr;
}

bool AudioSource::OnCreate(GameObject* gameObject_)
{
	gameObject = gameObject_;

	return true;
}

void AudioSource::Update()
{
}

int AudioSource::PlaySound(std::string soundName_, glm::vec3 pos_, glm::vec3 vel_, float volume_)
{
	channelID = AudioHandler::GetInstance()->PlaySound(soundName_, pos_, vel_, volume_);
	return channelID;
}

bool AudioSource::IsPlaying()
{
	return AudioHandler::GetInstance()->isPlaying(channelID);
}
