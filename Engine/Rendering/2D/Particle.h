#ifndef PARTICLE_H
#define PARTICLE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..//..//Camera/Camera.h"
#include "..//..///Graphics/MaterialHandler.h"
#include "..//..//Graphics/TextureHandler.h"
#include <string>

struct ParticleVertex2D
{
	glm::vec3 pos;
	glm::vec2 textureCoords;
};

class Particle
{
public:
	Particle(GLuint shaderProgram_, GLuint textureID_, std::string filename_);
	~Particle();

	glm::vec3 pos;
	glm::vec3 vel;
	float lifeTime;
	glm::vec3 colour;
	float size;
	glm::vec2 scale;
	float angle;

	GLuint shaderProgram;
	GLuint textureID = 0;
	GLuint VAO, VBO;
	GLuint modelLoc, viewLoc, colourLoc, projLoc, textureLoc, posLoc;


	void Render(Camera* camera_);
	void GenerateBuffers();

	float getWidth();
	float getHeight();

	std::vector<ParticleVertex2D> vertexList;
	ParticleVertex2D vertOne;
	ParticleVertex2D vertTwo;
	ParticleVertex2D vertThree;
	ParticleVertex2D vertFour;
};

#endif