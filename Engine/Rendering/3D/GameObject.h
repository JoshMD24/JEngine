#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "Component.h"

class GameObject
{
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();
	void Render(Camera* camera);
	void Update(const float deltaTime_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotaion() const;
	glm::vec3 GetScale() const;
	bool GetHit() const;

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetHit(bool hit_, int buttonType_);

	BoundingBox GetBoundingBox();

	std::vector<Component*> objects;

	std::string GetTag() const;
	void SetTag(std::string tag_);

	template<typename T, typename ... Args>
    void AddComponent(Args&& ... args_)
	{
		T* temp = new T(std::forward<Args>(args_)...);
		if (!dynamic_cast<Component*>(temp))
		{
			Debug::Error("Object is not a child of component. Deleting Components", "GameObject.cpp", __LINE__);
			delete temp;
			return;
		}
		if (this->GetComponent<T>()== nullptr)
		{
			objects.push_back(temp);
			objects[((objects.size()) - 1)]->OnCreate(this);
		}

		else
		{
			Debug::Error("Failed to add already existing component. Deleting Components", "GameObject.cpp", __LINE__);
			temp = nullptr;
			return;
		}
	}

	template<typename T>
    T* GetComponent()
	{
		for (int i = 0; i < (objects.size()); i++)
		{
			if (dynamic_cast<T*>(objects[i])!= nullptr)
			{
				return dynamic_cast<T*>(objects[i]);
			}
		}
		return nullptr;
	}

	template<typename T>
	void RemoveComponent()
	{
		for (int i = 0; i <= (objects.size()); i++)
		{
			if (dynamic_cast<T*>(objects[i]))
			{
				delete objects;
				objects = nullptr;
				objects.erase(objects.begin() + i);
				break;
			}
		}
	}
private:
	Model* model;

	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;

	int modelInstance;

	BoundingBox box;

	std::string tag;

	bool hit;
};

#endif // !GAMEOBJECT_H