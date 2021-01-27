#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
class Component
{
public:
    Component();
	virtual ~Component();
	virtual bool OnCreate(GameObject* parent_);
	virtual void Update(float deltaTime_);
protected:
	GameObject* parent;
};

#endif
