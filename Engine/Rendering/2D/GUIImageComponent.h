#ifndef GUIIMAGECOMPONENT_H
#define GUIIMAGECOMPONENT_H

#include <string>
#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..//..//Camera/Camera.h"
#include "..//2D/GUIComponent.h"
#include "..//2D/SpriteSurface.h"
#include "..//..//Graphics/ShaderHandler.h"

class GUIImageComponent : public GUIComponent
{
public:
	GUIImageComponent();
	virtual ~GUIImageComponent();

	void OnCreate(std::string image_);
	virtual void Draw(Camera* camera_, glm::vec2 position_);
	glm::vec2 GetWidthHeight();
	virtual bool FindContainingPoint(glm::vec2 mousePosition_, glm::vec2 guiPos);

	SpriteSurface* spriteSurface;

private:
	
	std::string image;
	glm::vec2 offset;
	float scale;
	float angle;
	glm::vec4 tintColour;
};

#endif