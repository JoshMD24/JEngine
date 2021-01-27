#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GUIComponent.h"
#include "../../Camera/Camera.h"
#include "../../Event/MouseEventListener.h"

class GUIObject
{
public:
	GUIObject(glm::vec2 pos_);
	~GUIObject();

	void DrawObject(Camera* camera);

	std::string GetTag() const;
	void SetTag(std::string tag_);

	void MouseInGUI();

	std::vector<GUIComponent*> GuiComponent;

	template<typename T>
	void AddComponent()
	{
		T* temp = new T();
		if (!dynamic_cast<GUIComponent*>(temp)) 
		{
			Debug::Error("wrong type of GUI component was added", "GuiObject.h", __LINE__);
			delete temp;
			temp = nullptr;
			return;
		}

		if (!this->GetComponent<T>()) 
		{
			GuiComponents.push_back(temp);
			std::cout << "GUI component added" << std::endl;
		}
		else 
		{
			Debug::Error("GUI component already exists", "GuiObject.cpp", __LINE__);
			delete temp;
			temp = nullptr;
			return;
		}
	}

	template<typename T>
	inline T* GetComponent()
	{
		for (int i = 0; i < (GuiComponents.size()); i++) 
		{
			if (dynamic_cast<T*>(GuiComponents[i]) != nullptr) 
			{
				return dynamic_cast<T*>(GuiComponents[i]);
			}
		}
		return nullptr;
	}

	template<typename T>
	inline void RemoveComponent()
	{
		for (int i = 0; i < (GuiComponents.size()); i++) 
		{
			if (dynamic_cast<T*>(GuiComponents[i]))
			{
				delete GuiComponents[i];
				GuiComponents[i] = nullptr;
				GuiComponents.erase(GuiComponents.begin() + i);
				std::cout << "GUI component removed" << std::endl;
				return;
			}
		}
	}

private:
	glm::vec2 pos;
	std::string tag;

	std::vector<GUIComponent*> GuiComponents;
};

#endif