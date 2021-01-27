#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 textureCoords;

out vec2 TextureCoords;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
uniform vec3 position;

void main()
{
	TextureCoords = textureCoords;
	gl_Position = proj * model * view * vec4(pos, 1.0f);
}