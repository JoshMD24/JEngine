#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include "../Rendering/3D/Component.h"
#include <string>
#include <glm/glm.hpp>

class AudioSource : public virtual Component
{
public:
	AudioSource(std::string fileName_, bool loop_, bool threeD_, bool play_);
	~AudioSource();

	bool OnCreate(GameObject* gameobject_) override;
	void Update();

	int PlaySound(std::string soundName_, glm::vec3 pos_, glm::vec3 vel_ = glm::vec3(0), float volume_ = 1.0f);

	bool IsPlaying();

	std::string fileName;

	GameObject* gameObject;

	int channelID;
};

#endif