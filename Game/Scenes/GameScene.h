#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "..//..//Engine/Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>
#include "..//..//Engine/Rendering/3D/ComponentA.h"
#include "..//..//Engine/Rendering/2D/GUIObject.h"
#include "..//..//Engine/Rendering/2D/GUIImageComponent.h"
#include "..//..//Engine/Audio/AudioSource.h"
#include "..//..//Engine/Rendering/2D/ParticleEmitter.h"

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();
	virtual void DrawGUI();
private:
};

#endif // !GAMESCENE_H