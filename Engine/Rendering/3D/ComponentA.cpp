#include "ComponentA.h"

ComponentA::ComponentA()
{
}

ComponentA::~ComponentA()
{
	parent = nullptr;
}

bool ComponentA::OnCreate(GameObject* parent_)
{
	parent = parent_;
	return true;
}

void ComponentA::Update(float deltaTime_)
{
	std::cout << " ComponentA is being updated " << std::endl;
}
