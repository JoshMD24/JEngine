#ifndef SPRITESURFACE_H
#define SPRITESURFACE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..//..//Camera/Camera.h"
#include "..//..//Graphics/ShaderHandler.h"
#include "..//..//Graphics/TextureHandler.h"

struct Vertex2D
{
	Vertex2D(glm::vec4 vertex2d_)
	{
		pos = glm::vec2(vertex2d_.x, vertex2d_.y);
		textureCoords = glm::vec2(vertex2d_.z, vertex2d_.w);
	}
	glm::vec2 pos;
	glm::vec2 textureCoords;
};

class SpriteSurface
{
public:
	SpriteSurface(std::string imageName_, float scale_ , float angle_, glm::vec4 tintColour_);
	~SpriteSurface();

	std::vector<Vertex2D> vertexList;

	void Draw(Camera* camera_, glm::vec2 position_);

	GLuint textureID = 0;

	std::string imageName;
	glm::vec4 tintColour;
	glm::vec2 scale;
	float angle;

	float width;
	float height;

private:
	void GenerateBuffers();

	GLuint VAO, VBO;
	GLuint modelLoc, projLoc, colourLoc, textureLoc;
	GLuint shaderProgram;
};

#endif