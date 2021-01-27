#include "GameScene.h"

GameScene::GameScene() : Scene()
{
}

GameScene::~GameScene()
{
	SceneGraph::GetInstance()->OnDestroy();
}

bool GameScene::OnCreate()
{
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));

	LightSource* light = new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	CoreEngine::GetInstance()->GetCamera()->AddLightSources(light);

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	//apple
	Model* appleModel = new Model("./Resources/Models/Apple.obj", "./Resources/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(appleModel);

	GameObject* apple = new GameObject(appleModel, glm::vec3(0.0f, -1.0f, 0.0f)); //vec3 is its position
	apple->SetScale(glm::vec3(0.5f));
	/*apple->AddComponent<ComponentA>();*/
	SceneGraph::GetInstance()->AddGameObject(apple, "apple");

	//dice
	Model* diceModel = new Model("./Resources/Models/Dice.obj", "./Resources/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(diceModel);

	GameObject* dice = new GameObject(diceModel, glm::vec3(-3.0f, -1.0f, 0.0f)); //vec3 is its position
	SceneGraph::GetInstance()->AddGameObject(dice, "dice");

	GUIObject* gui = new GUIObject(glm::vec2(CoreEngine::GetInstance()->GetWindowSize().x / 2.0f, CoreEngine::GetInstance()->GetWindowSize().x / 2.0f));

	gui->AddComponent<GUIImageComponent>();
	gui->GetComponent<GUIImageComponent>()->OnCreate("RedBall");

	SceneGraph::GetInstance()->AddGUIObject(gui, "RedBallGUI");

	apple->AddComponent<AudioSource>("BackgroundMusic", true, true, true);
	apple->GetComponent<AudioSource>()->PlaySound("BackgroundMusic", apple->GetPosition());

	ParticleEmitter* p1 = new ParticleEmitter(50, "Apple_Body.JPG", "particleShader");
	SceneGraph::GetInstance()->AddParticleEmitter(p1, "p1");

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());
	//glPolygonMode
}

void GameScene::DrawGUI()
{
	SceneGraph::GetInstance()->Draw(CoreEngine::GetInstance()->GetCamera());
}
