#include "GUIObject.h"

GUIObject::GUIObject(glm::vec2 pos_)
{
	pos = pos_;
}

GUIObject::~GUIObject()
{
	GuiComponents.clear();
}

void GUIObject::DrawObject(Camera* camera)
{
	for (int i = 0; i < (GuiComponents.size()); i++)
	{
		GuiComponents[i]->Draw(camera, pos);
	}
}

void GUIObject::SetTag(std::string tag_)
{
	tag = tag_;
}

std::string GUIObject::GetTag() const
{
	return tag;
}

void GUIObject::MouseInGUI()
{
	for (int i = 0; i < (GuiComponents.size()); i++)
	{
		GuiComponents[i]->FindContainingPoint(MouseEventListener::GetMousePosition(), pos);
	}
}
