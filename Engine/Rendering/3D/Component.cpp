#include "Component.h"

Component::Component()
{
	parent = nullptr;
}

Component::~Component()
{
	parent = nullptr;
}

bool Component::OnCreate(GameObject* parent_)
{
	return true;
}

void Component::Update(float deltaTime_)
{
}
