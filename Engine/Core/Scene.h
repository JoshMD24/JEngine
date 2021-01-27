#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene() {}
	virtual ~Scene() {}
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
	virtual bool OnCreate() = 0;
	virtual void DrawGUI() = 0;
};


#endif // !SCENE_H

