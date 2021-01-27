#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/gtc/matrix_transform.hpp>

class LightSource
{
public:
	glm::vec3 GetLightPos() const;
	float* GetAmbientVal();
	float* GetDiffuseVal();
	glm::vec3 GetLightColor() const;
	

	void SetLightPos(glm::vec3 lightPos_);
	void SetAmbientVal(float ambientVal_);
	void SetDiffuseVal(float diffuseVal_);
	void SetLightColor(glm::vec3 lightColor_);

	LightSource(glm::vec3 lightPos_, float ambientVal_, float diffuseVal_, glm::vec3 lightColor_);
	~LightSource();

private:
	glm::vec3 lightPos;
	float ambientVal;
	float diffuseVal;
	glm::vec3 lightColor;
};

#endif
