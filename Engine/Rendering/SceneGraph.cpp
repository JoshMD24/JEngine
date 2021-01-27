#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();
std::map<std::string, GUIObject*> SceneGraph::sceneGUIObjects = std::map<std::string, GUIObject*>();
std::map<std::string, ParticleEmitter*> SceneGraph::sceneParicles = std::map<std::string, ParticleEmitter*>();

SceneGraph::SceneGraph()
{
}

SceneGraph::~SceneGraph()
{
	OnDestroy();
}


SceneGraph* SceneGraph::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr)
	{
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy()
{
	if (sceneGameObjects.size() > 0)
	{
		for (auto go : sceneGameObjects)
		{
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}
	if (sceneModels.size() > 0)
	{
		for (auto entry : sceneModels)
		{
			if (entry.second.size() > 0)
			{
				for (auto m : entry.second)
				{
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}

	if (sceneGUIObjects.size() > 0)
	{
		for (auto gui : sceneGUIObjects)
		{
			delete gui.second;
			gui.second = nullptr;
		}
		sceneGUIObjects.clear();
	}

	if (sceneParicles.size() > 0)
	{
		for (auto go : sceneParicles)
		{
			delete go.second;
			go.second = nullptr;
		}
		sceneParicles.clear();
	}
}

void SceneGraph::AddModel(Model* model_)
{
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end())
	{
		std::vector<Model*> tmp = std::vector<Model*>();
		tmp.reserve(10);
		tmp.push_back(model_);
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(model_->GetShaderProgram(), tmp));
	}
	else
	{
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}
}

void SceneGraph::AddGameObject(GameObject* go_, std::string tag_)
{
	if (tag_ == "")
	{
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end())
	{
		go_->SetTag(tag_);
		sceneGameObjects[tag_] = go_;
	}
	else
	{
		Debug::Error("Trying to add a GameObject with a tag " + tag_ + " that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	CollisionHandler::GetInstance()->AddObject(go_);
}

GameObject* SceneGraph::GetGameObject(std::string tag_)
{
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end())
	{
		return sceneGameObjects[tag_];
	}
	return nullptr;
}

void SceneGraph::AddGUIObject(GUIObject* gui_, std::string tag_)
{
	if (tag_ == "")
	{
		std::string newTag = "GUIObject" + std::to_string(sceneGUIObjects.size() + 1);
		gui_->SetTag(newTag);
		sceneGUIObjects[newTag] = gui_;
	}
	else if (sceneGUIObjects.find(tag_) == sceneGUIObjects.end())
	{
		gui_->SetTag(tag_);
		sceneGUIObjects[tag_] = gui_;
	}
	else
	{
		Debug::Error("Trying to add GUI with a tag" + tag_ + "that already exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GUIObject" + std::to_string(sceneGUIObjects.size() + 1);
		gui_->SetTag(newTag);
		sceneGUIObjects[newTag] = gui_;
	}
}

GUIObject* SceneGraph::GetGUIObject(std::string tag_)
{
	if (sceneGUIObjects.find(tag_) != sceneGUIObjects.end())
	{
		return sceneGUIObjects[tag_];
	}
	return nullptr;
}

void SceneGraph::AddParticleEmitter(ParticleEmitter* go_, std::string tag_)
{
	if (tag_ == "")
	{
		std::string newTag = "ParticleEmitter" + std::to_string(sceneParicles.size() + 1);
		go_->SetTag(newTag);
		sceneParicles[newTag] = go_;
	}
	else if (sceneParicles.find(tag_) == sceneParicles.end())
	{
		go_->SetTag(tag_);
		sceneParicles[tag_] = go_;
	}
	else
	{
		Debug::Error("Trying to add Emitter with a tag" + tag_ + "that already exist", "SceneGraph.cpp", __LINE__);
		std::string newTag = "ParticleEmitter" + std::to_string(sceneParicles.size() + 1);
		go_->SetTag(newTag);
		sceneParicles[newTag] = go_;
	}
}

ParticleEmitter* SceneGraph::GetAddParticleEmitter(std::string tag_)
{
	if (sceneParicles.find(tag_) != sceneParicles.end())
	{
		return sceneParicles[tag_];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_)
{
	for (auto go : sceneGameObjects)
	{
		go.second->Update(deltaTime_);
	}
	
	for (auto go : sceneParicles)
	{
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_)
{
	for (auto entry : sceneModels)
	{
		glUseProgram(entry.first);
		for (auto m : entry.second)
		{
			m->Render(camera_);
		}
	}
}

void SceneGraph::Draw(Camera* camera_)
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint guiProgram = ShaderHandler::GetInstance()->GetShader("spriteShader");
	glUseProgram(guiProgram);

	for (auto gui : sceneGUIObjects)
	{
		gui.second->DrawObject(camera_);
	}

	GLuint particleProgram = ShaderHandler::GetInstance()->GetShader("particleShader");
	glUseProgram(particleProgram);

	for (auto go : sceneParicles)
	{
		go.second->Render(camera_);
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}