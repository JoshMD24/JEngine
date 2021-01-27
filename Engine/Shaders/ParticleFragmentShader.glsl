#version 450 core

in vec2 TextureCoords;

out vec4 colour;

uniform vec3 particleColour;
uniform sampler2D particleTexture;

void main()
{
	vec4 tempColour = vec4(particleColour, 1.0f) * texture(particleTexture, TextureCoords);
	colour = tempColour;
}