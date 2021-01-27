#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "..////FX/LightSource.h"
#include <vector>

class Camera
{
public:
	Camera();
	~Camera();
	void SetPosition(glm::vec3 position_);
	void SetRotaion(float yaw_, float pitch_);

	float idk;

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;

	glm::vec2 GetClippingPlanes() const;

	void AddLightSources(LightSource* light);
	std::vector<LightSource*> GetLightSources();
	glm::vec3 GetCameraPosition();

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);

	glm::vec4 frontFrustum, backFrustum, leftFrustum, rightFrustum, topFrustum, bottomFrustum;
	void GetFrustum();

private:
	void UpdateCameraVector();
	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;
	void OnDestroy();
	std::vector<LightSource*> lights;
};

#endif