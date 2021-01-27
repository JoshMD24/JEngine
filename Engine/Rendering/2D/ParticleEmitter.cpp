#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(int numParticles_, std::string textureName_, std::string shaderName_)
{
	numParticles = numParticles_;
	textureName = textureName_;
	shaderName = shaderName_;

	textureID = LoadTexture(textureName);
	shaderID = ShaderHandler::GetInstance()->GetShader(shaderName);

	if (shaderID != 0 && textureID != 0)
	{
		if (numParticles > 0)
		{
			CreateParticles();
		}
	}
}

ParticleEmitter::~ParticleEmitter()
{
	if (particles.size() > 0)
	{
		particles.clear();
	}
}

void ParticleEmitter::Render(Camera* camera_)
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->Render(camera_);
	}
}

void ParticleEmitter::Update(float deltaTime_)
{
	MATH::Randomizer random;

	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i]->lifeTime > 0)
		{
			particles[i]->lifeTime -= deltaTime_;

			particles[i]->pos += particles[i]->vel * deltaTime_;
		}
		else
		{
			particles[i]->pos = glm::vec3(3.0f, 3.0f, -10.0f);
			particles[i]->lifeTime = 1.5f;
			particles[i]->vel = glm::vec3(random.rand(-10.0f, 10.0f), random.rand(-10.0f, 10.0f), 0);
		}
	}
}

void ParticleEmitter::SetTag(std::string tag_)
{
	tag = tag_;
}

void ParticleEmitter::CreateParticles()
{
	particles.reserve(numParticles);
	MATH::Randomizer random;

	for (int i = 0; i < numParticles; i++)
	{
		particles.push_back(new Particle(shaderID, textureID, textureName));
		particles[i]->pos = glm::vec3(3.0f, 3.0f, -10.0f);
		particles[i]->scale = glm::vec2(1.0f, 1.0f);
		particles[i]->vel = glm::vec3(random.rand(-10.0f, 10.0f), random.rand(-10.0f, 10.0f), 0.0f);
	}
}

GLuint ParticleEmitter::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_);
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
