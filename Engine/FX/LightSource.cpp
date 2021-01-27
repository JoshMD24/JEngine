#include "LightSource.h"

glm::vec3 LightSource::GetLightPos() const
{
	return lightPos;
}

float *LightSource::GetAmbientVal()
{
	return &ambientVal;
}

float *LightSource::GetDiffuseVal()
{
	return &diffuseVal;
}

glm::vec3 LightSource::GetLightColor() const
{
	return lightColor;
}

void LightSource::SetLightPos(glm::vec3 lightPos_)
{
	lightPos = lightPos_;
}

void LightSource::SetAmbientVal(float ambientVal_)
{
	ambientVal = ambientVal_;
}

void LightSource::SetDiffuseVal(float diffuseVal_)
{
	diffuseVal = diffuseVal_;
}

void LightSource::SetLightColor(glm::vec3 lightColor_)
{
	lightColor = lightColor_;
}

LightSource::LightSource(glm::vec3 lightPos_, float ambientVal_, float diffuseVal_, glm::vec3 lightColor_)
{
	lightPos = lightPos_;
	ambientVal = ambientVal_;
	diffuseVal = diffuseVal_;
	lightColor = lightColor_;
}

LightSource::~LightSource()
{

}
