#ifndef COMPONENTA_H
#define COMPONENTA_H

#include "Component.h"
#include <stdio.h>
#include <iostream>

class ComponentA : public virtual Component
{
public:
	ComponentA();
	~ComponentA();

    bool OnCreate(GameObject* parent_)override;

	void Update(float deltaTime_)override;
};

#endif // COMPONENTA_H