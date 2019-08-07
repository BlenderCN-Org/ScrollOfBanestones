#version 410 core

out vec3 color;
in vec3 fragmentColour;

void main()
{
	color = fragmentColour;
}