#include "SpriteSurface.h"

SpriteSurface::SpriteSurface(std::string imageName_, float scale_, float angle_, glm::vec4 tintColour_) : VAO(0), VBO(0), modelLoc(0), projLoc(0), colourLoc(0), textureLoc(0)
{
	vertexList.push_back(Vertex2D(glm::vec4(-0.5f, 0.5f, 0.0f, 0.0f)));
	vertexList.push_back(Vertex2D(glm::vec4(0.5f, 0.5f, 1.0f, 0.0f)));
	vertexList.push_back(Vertex2D(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f)));
	vertexList.push_back(Vertex2D(glm::vec4(0.5f, -0.5f, 1.0f, 1.0f)));

	scale = glm::vec2(0.1f, 0.1f);
	angle = 1.0f;
	tintColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	if (imageName_ != "")
	{
		imageName = imageName_;
	}

	if (TextureHandler::GetInstance()->GetTexture(imageName) == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(imageName, "./Resources/GUI/" + imageName + ".png");
	}

	textureID = TextureHandler::GetInstance()->GetTexture(imageName);

	width = TextureHandler::GetInstance()->GetTextureData(imageName)->width;
	height = TextureHandler::GetInstance()->GetTextureData(imageName)->height;

	GenerateBuffers();
}

SpriteSurface::~SpriteSurface()
{
	vertexList.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void SpriteSurface::Draw(Camera* camera_, glm::vec2 position_)
{
	glUniform1d(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glm::mat4 model;

	model = glm::translate(model, glm::vec3(position_.x, position_.y, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(width * scale.x, height * scale.y, 1.0f));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetOrthographic()));

	glUniform4fv(colourLoc, 1, glm::value_ptr(tintColour));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexList.size());
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SpriteSurface::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(Vertex2D), &vertexList[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)offsetof(Vertex2D, textureCoords));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shaderProgram = ShaderHandler::GetInstance()->GetShader("spriteShader");

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	colourLoc = glGetUniformLocation(shaderProgram, "tintColour");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
}