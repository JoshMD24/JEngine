#include "AudioHandler.h"

std::map<std::string, FMOD::Sound*> AudioHandler::sounds = std::map<std::string, FMOD::Sound*>();
std::map<int, FMOD::Channel*> AudioHandler::channels = std::map<int, FMOD::Channel*>();
std::unique_ptr<AudioHandler> AudioHandler::audioInstance = nullptr;

AudioHandler::AudioHandler() : pos(glm::vec3(0)), vel(glm::vec3(0)), forwardDir(glm::vec3(0,0,-1)), upDir(glm::vec3(0,1,0))
{
	Initialize(pos, vel, forwardDir, upDir);
}

AudioHandler::~AudioHandler()
{
	if (audioInstance == nullptr)
	{
		OnDestroy();
	}
}

AudioHandler* AudioHandler::GetInstance()
{
	if (audioInstance.get() == nullptr)
	{
		audioInstance.reset(new AudioHandler);
		return audioInstance.get();
	}
}

bool AudioHandler::Initialize(glm::vec3 pos_, glm::vec3 vel_, glm::vec3 forwardDir_, glm::vec3 upDir_)
{
	pos = pos_;
	vel = vel_;
	forwardDir = forwardDir_;
	upDir = upDir_;

	FMOD::System_Create(&soundSystem);

	soundSystem->getNumDrivers(&drivers);
	if (drivers == 0)
	{
		return false;
	}

	soundSystem->init(createdChannels, FMOD_INIT_NORMAL | FMOD_3D | FMOD_INIT_3D_RIGHTHANDED, nullptr);
	soundSystem->set3DListenerAttributes(0, &glmToFMOD(pos), &glmToFMOD(vel), &glmToFMOD(forwardDir), &glmToFMOD(upDir));

	return true;
}

void AudioHandler::OnDestroy()
{
	if (sounds.size() > 0)
	{
		for (auto go : sounds)
		{
			go.second->release();
			go.second = nullptr;
		}
		sounds.clear();
	}

	if (channels.size() > 0)
	{
		for (auto go : channels)
		{
			go.second->stop();
			go.second = nullptr;
		}
		channels.clear();
	}

	soundSystem->release();
	soundSystem = nullptr;
}

void AudioHandler::Update()
{
	soundSystem->update();
}

FMOD_VECTOR AudioHandler::glmToFMOD(glm::vec3 input_)
{
	FMOD_VECTOR fmodVector;

	fmodVector.x = input_.x;
	fmodVector.y = input_.y;
	fmodVector.z = input_.z;

	return fmodVector;
}

void AudioHandler::LoadSound(std::string fileName_, bool loop_, bool threeD_, bool play_)
{
	if (GetSound(fileName_) != nullptr)
	{
		return;
	}

	FMOD_MODE mode = FMOD_DEFAULT;
	if (loop_ == true)
	{
		mode |= FMOD_LOOP_NORMAL;
	}
	else
	{
		mode |= FMOD_LOOP_OFF;
	}
	if (threeD_ == true)
	{
		mode |= FMOD_3D;
	}
	else
	{
		mode |= FMOD_2D;
	}
	if (play_ == true)
	{
		mode |= FMOD_CREATESTREAM;
	}
	else
	{
		mode |= FMOD_CREATECOMPRESSEDSAMPLE;
	}

	std::string filepath("./Resources/Audio/" + fileName_ + ".mp3");

	FMOD::Sound* sound = nullptr;
	FMOD_RESULT result;
	
	result = soundSystem->createSound(filepath.c_str(), mode, nullptr, &sound);

	if (result == FMOD_OK)
	{
		sounds[fileName_] = sound;
	}
}

FMOD::Sound* AudioHandler::GetSound(std::string sound_)
{
	if (sounds.find(sound_) != sounds.end())
	{
		return sounds[sound_];
	}

	return nullptr;
}

int AudioHandler::PlaySound(std::string soundName_, glm::vec3 pos_, glm::vec3 vel_, float volume_)
{
	int channelID = -1;

	if (GetSound(soundName_) == nullptr)
	{
		LoadSound(soundName_, true, true, true);
	}

	FMOD::Channel* fmodChannel = nullptr;
	FMOD_RESULT result;
	result = soundSystem->playSound(sounds[soundName_], nullptr, true, &fmodChannel);

	if (result == FMOD_OK)
	{
		fmodChannel->set3DAttributes(&glmToFMOD(pos_), &glmToFMOD(vel_));
		fmodChannel->setVolume(volume_);
		fmodChannel->setPaused(false);

		channelID = createdChannels;
		createdChannels++;
		channels[channelID] = fmodChannel;
	}

	return channelID;
}

void AudioHandler::UpdatePosAndVel(int channelID_, glm::vec3 pos_, glm::vec3 vel_)
{
	if (channels[channelID_] != nullptr)
	{
		channels[channelID_]->set3DAttributes(&glmToFMOD(pos_), &glmToFMOD(vel_));
	}
}

bool AudioHandler::isPlaying(int channel_)
{
	if (channels[channel_] != nullptr)
	{
		bool isPlaying;
		channels[channel_]->isPlaying(&isPlaying);
		return isPlaying;
	}

	return false;
}
