#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include "SpriteSurface.h"

class GUIComponent
{
public:
	GUIComponent();
	virtual ~GUIComponent();

	virtual void Draw(Camera* camera_, glm::vec2 pos_) = 0;
	virtual bool FindContainingPoint(glm::vec2 mousePosition_, glm::vec2 guiPos) = 0;

private:
	SpriteSurface* spriteSurface;
};

#endif