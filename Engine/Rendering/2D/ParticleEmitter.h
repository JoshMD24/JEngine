#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include <SDL.h>
#include <glew.h>
#include <string>
#include <iostream>
#include "..//..//Camera/Camera.h"
#include "Particle.h"
#include "..//..//Graphics/ShaderHandler.h"
#include "..//..//Core/Randomizer.h"

class ParticleEmitter
{
public:
	ParticleEmitter(int numParticles_, std::string textureName_, std::string shaderName_);
	~ParticleEmitter();

	void Render(Camera* camera_);
	void Update(float deltaTime_);
	void SetTag(std::string tag_);

private:
	int numParticles;
	std::string textureName;
	std::string shaderName;
	std::string tag;

	std::vector<Particle*> particles;

	void CreateParticles();

	//Renderer::RENDERER_TYPE rendertype;

	GLuint textureID;
	GLuint shaderID;
	GLuint LoadTexture(std::string fileName_);
};

#endif