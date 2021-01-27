#include "Particle.h"

Particle::Particle(GLuint shaderProgram_, GLuint textureID_, std::string filename_) : pos(glm::vec3(0.0f,0.0f,0.0f)), vel(glm::vec3(0.0f,0.0f,0.0f)), angle(0), lifeTime(1.0f), scale(glm::vec2(1.0f, 1.0f)),
colour(glm::vec3(1.0f,1.0f,1.0f)), VAO(0), VBO(0), modelLoc(0), projLoc(0), colourLoc(0), textureLoc(0)
{
	shaderProgram = shaderProgram_;
	textureID = textureID_;

	vertOne.pos = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertOne.textureCoords = glm::vec2(0.0f, 0.0f);
	vertexList.push_back(vertOne);

	vertTwo.pos = glm::vec3(0.5f, 0.5f, 0.0f);
	vertTwo.textureCoords = glm::vec2(1.0f, 0.0f);
	vertexList.push_back(vertTwo);

	vertThree.pos = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertThree.textureCoords = glm::vec2(0.0f, 1.0f);
	vertexList.push_back(vertThree);

	vertFour.pos = glm::vec3(0.5f, -0.5f, 0.0f);
	vertFour.textureCoords = glm::vec2(1.0f, 1.0f);
	vertexList.push_back(vertFour);


	GenerateBuffers();
}

Particle::~Particle()
{
	vertexList.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Particle::Render(Camera* camera_)
{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
	model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(scale.x, scale.y, 1.0f));

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glUniform3fv(colourLoc, 1, glm::value_ptr(colour));

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexList.size());

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Particle::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glBufferData(GL_ARRAY_BUFFER, vertexList.size() * sizeof(ParticleVertex2D), &vertexList[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex2D), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex2D), (GLvoid*)offsetof(ParticleVertex2D, textureCoords));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	colourLoc = glGetUniformLocation(shaderProgram, "particleColour");
	textureLoc = glGetUniformLocation(shaderProgram, "particleTexture");
}
