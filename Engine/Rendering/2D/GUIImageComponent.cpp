#include "GUIImageComponent.h"

GUIImageComponent::GUIImageComponent() : angle(0), scale(1), offset(glm::vec2(0.0f, 0.0f)), tintColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{

}

GUIImageComponent::~GUIImageComponent()
{

}

void GUIImageComponent::OnCreate(std::string image_)
{
	spriteSurface = new SpriteSurface(image_, scale, angle, tintColour);
}

void GUIImageComponent::Draw(Camera* camera_, glm::vec2 position_)
{
	spriteSurface->Draw(camera_, position_);
}

glm::vec2 GUIImageComponent::GetWidthHeight()
{
	return glm::vec2(spriteSurface->width, spriteSurface->height);
}

bool GUIImageComponent::FindContainingPoint(glm::vec2 mousePosition_, glm::vec2 guiPos)
{
	if (spriteSurface != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
