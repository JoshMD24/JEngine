#include "Camera.h"
#include "..//Core/CoreEngine.h"
#include <vector>

Camera::Camera() : position(glm::vec3())
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView, CoreEngine::GetInstance()->GetWindowSize().x / CoreEngine::GetInstance()->GetWindowSize().y, nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x, 0.0f, CoreEngine::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);

	UpdateCameraVector();
}

Camera::~Camera()
{
	OnDestroy();
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVector();
}

void Camera::SetRotaion(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVector();
}

glm::mat4 Camera::GetView() const
{
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec2 Camera::GetClippingPlanes() const
{
	return glm::vec2(nearPlane, farPlane);
}

void Camera::AddLightSources(LightSource* light)
{
	lights.push_back(light);
}

std::vector<LightSource*> Camera::GetLightSources()
{
	return lights;
}

glm::vec3 Camera::GetCameraPosition()
{
	return position;
}

void Camera::ProcessMouseMovement(glm::vec2 offset_)
{
	offset_ *= 0.05f;

	yaw += offset_.x;
	pitch += offset_.y;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < 89.0f)
	{
		//pitch = 89.0f;
	}

	if (yaw < 0.0f)
	{
		yaw += 360.0f;
	}
	if (yaw > 360.0f)
	{
		yaw -= 360.0f;
	}
	UpdateCameraVector();
}

void Camera::ProcessMouseZoom(int y_)
{
	if (y_ < 0 || y_ > 0)
	{
		position += static_cast<float>(y_) * (forward * 2.0f);
	}
	UpdateCameraVector();
}

	//void Camera::GetFrustum()
	//{
	//		glm::mat4 viewMatrix = GetView();
	//		glm::mat4 projectionMatrix = GetPerspective();
	//
	//		topFrustum = glm::vec4(0);
	//		bottomFrustum = glm::vec4(0);
	//		leftFrustum = glm::vec4(0);
	//		backFrustum = glm::vec4(0);
	//		frontFrustum = glm::vec4(0);
	//		rightFrustum = glm::vec4(0);
	//
	//		double clip[4][4];
	//		clip[0][0] = viewMatrix[0][0] * projectionMatrix[0][0] + viewMatrix[0][1] * projectionMatrix[1][0] + viewMatrix[0][2] * projectionMatrix[2][0] + viewMatrix[0][3] * projectionMatrix[3][0];
	//		clip[0][1] = viewMatrix[0][0] * projectionMatrix[0][1] + viewMatrix[0][1] * projectionMatrix[1][1] + viewMatrix[0][2] * projectionMatrix[2][1] + viewMatrix[0][3] * projectionMatrix[3][1];
	//		clip[0][2] = viewMatrix[0][0] * projectionMatrix[0][2] + viewMatrix[0][1] * projectionMatrix[1][2] + viewMatrix[0][2] * projectionMatrix[2][2] + viewMatrix[0][3] * projectionMatrix[3][2];
	//		clip[0][3] = viewMatrix[0][0] * projectionMatrix[0][3] + viewMatrix[0][1] * projectionMatrix[1][3] + viewMatrix[0][2] * projectionMatrix[2][3] + viewMatrix[0][3] * projectionMatrix[3][3];
	//
	//		clip[1][0] = viewMatrix[1][0] * projectionMatrix[0][0] + viewMatrix[1][1] * projectionMatrix[1][0] + viewMatrix[1][2] * projectionMatrix[2][0] + viewMatrix[1][3] * projectionMatrix[3][0];
	//		clip[1][1] = viewMatrix[1][0] * projectionMatrix[0][1] + viewMatrix[1][1] * projectionMatrix[1][1] + viewMatrix[1][2] * projectionMatrix[2][1] + viewMatrix[1][3] * projectionMatrix[3][1];
	//		clip[1][2] = viewMatrix[1][0] * projectionMatrix[0][2] + viewMatrix[1][1] * projectionMatrix[1][2] + viewMatrix[1][2] * projectionMatrix[2][2] + viewMatrix[1][3] * projectionMatrix[3][2];
	//		clip[1][3] = viewMatrix[1][0] * projectionMatrix[0][3] + viewMatrix[1][1] * projectionMatrix[1][3] + viewMatrix[1][2] * projectionMatrix[2][3] + viewMatrix[1][3] * projectionMatrix[3][3];
	//
	//		clip[2][0] = viewMatrix[2][0] * projectionMatrix[0][0] + viewMatrix[2][1] * projectionMatrix[1][0] + viewMatrix[2][2] * projectionMatrix[2][0] + viewMatrix[2][3] * projectionMatrix[3][0];
	//		clip[2][1] = viewMatrix[2][0] * projectionMatrix[0][1] + viewMatrix[2][1] * projectionMatrix[1][1] + viewMatrix[2][2] * projectionMatrix[2][1] + viewMatrix[2][3] * projectionMatrix[3][1];
	//		clip[2][2] = viewMatrix[2][0] * projectionMatrix[0][2] + viewMatrix[2][1] * projectionMatrix[1][2] + viewMatrix[2][2] * projectionMatrix[2][2] + viewMatrix[2][3] * projectionMatrix[3][2];
	//		clip[2][3] = viewMatrix[2][0] * projectionMatrix[0][3] + viewMatrix[2][1] * projectionMatrix[1][3] + viewMatrix[2][2] * projectionMatrix[2][3] + viewMatrix[2][3] * projectionMatrix[3][3];
	//
	//		clip[3][0] = viewMatrix[3][0] * projectionMatrix[0][0] + viewMatrix[3][1] * projectionMatrix[1][0] + viewMatrix[3][2] * projectionMatrix[2][0] + viewMatrix[3][3] * projectionMatrix[3][0];
	//		clip[3][1] = viewMatrix[3][0] * projectionMatrix[0][1] + viewMatrix[3][1] * projectionMatrix[1][1] + viewMatrix[3][2] * projectionMatrix[2][1] + viewMatrix[3][3] * projectionMatrix[3][1];
	//		clip[3][2] = viewMatrix[3][0] * projectionMatrix[0][2] + viewMatrix[3][1] * projectionMatrix[1][2] + viewMatrix[3][2] * projectionMatrix[2][2] + viewMatrix[3][3] * projectionMatrix[3][2];
	//		clip[3][3] = viewMatrix[3][0] * projectionMatrix[0][3] + viewMatrix[3][1] * projectionMatrix[1][3] + viewMatrix[3][2] * projectionMatrix[2][3] + viewMatrix[3][3] * projectionMatrix[3][3];
	//
	//		rightFrustum.x = clip[0][3] - clip[0][0];
	//		rightFrustum.y = clip[1][3] - clip[1][0];
	//		rightFrustum.z = clip[2][3] - clip[2][0];
	//		rightFrustum.w = clip[3][3] - clip[3][0];
	//		glm::normalize(right);
	//
	//		leftFrustum.x = clip[0][3] + clip[0][0];
	//		leftFrustum.y = clip[1][3] + clip[1][0];
	//		leftFrustum.z = clip[2][3] + clip[2][0];
	//		leftFrustum.w = clip[3][3] + clip[3][0];
	//		glm::normalize(leftFrustum);
	//
	//		bottomFrustum.x = clip[0][3] + clip[0][1];
	//		bottomFrustum.y = clip[1][3] + clip[1][1];
	//		bottomFrustum.z = clip[2][3] + clip[2][1];
	//		bottomFrustum.w = clip[3][3] + clip[3][1];
	//		glm::normalize(bottomFrustum);
	//
	//		topFrustum.x = clip[0][3] - clip[0][1];
	//		topFrustum.y = clip[1][3] - clip[1][1];
	//		topFrustum.z = clip[2][3] - clip[2][1];
	//		topFrustum.w = clip[3][3] - clip[3][1];
	//		glm::normalize(topFrustum);
	//
	//		frontFrustum.x = clip[0][3] - clip[0][2];
	//		frontFrustum.y = clip[1][3] - clip[1][2];
	//		frontFrustum.z = clip[2][3] - clip[2][2];
	//		frontFrustum.w = clip[3][3] - clip[3][2];
	//		glm::normalize(frontFrustum);
	//
	//		backFrustum.x = clip[0][3] + clip[0][2];
	//		backFrustum.y = clip[1][3] + clip[1][2];
	//		backFrustum.z = clip[2][3] + clip[2][2];
	//		backFrustum.w = clip[3][3] + clip[3][2];
	//		glm::normalize(backFrustum);
	//}

void Camera::UpdateCameraVector()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));
}

void Camera::OnDestroy()
{
	if (lights.size() > 0) 
	{
		for (LightSource* l : lights) {
			delete l;
			l = nullptr;
		}
	}
}

