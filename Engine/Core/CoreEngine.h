#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"
#include "..//Rendering/3D/GameObject.h"
#include "..//Rendering/SceneGraph.h"
#include "..//Graphics/ShaderHandler.h"
#include "..//Graphics/TextureHandler.h"

#include "..//Camera/Camera.h"

#include "..//Event/EventListener.h"

class CoreEngine
{
public:
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator = (const CoreEngine&) = delete;
	CoreEngine& operator = (CoreEngine&&) = delete;
	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	bool GetIsRunning() const;

	static CoreEngine* GetInstance();

	void SetGameInterface(GameInterface* gameInterface_);

	glm::vec2 GetWindowSize() const;
	Camera* GetCamera() const;
	
	int GetCurrentScene();
	void SetCurrentScene(int sceneNum_);
	void SetCamera(Camera* camera_);


	void Exit();

	void NotifyOfMousePressed(glm::vec2 mouse_);
	void NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_);
	void NotifyOfMouseMoved(glm::vec2 mouse_);
	void NotifyOfMouseScroll(int y_);
private:
	CoreEngine();
	~CoreEngine();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();
	Window* window;
	bool isRunning;

	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;

};

#endif // !COREENGINE_H