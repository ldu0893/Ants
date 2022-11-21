#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoordInput;

out vec2 texCoord;
uniform vec2 actualPosition;

void main()
{
	gl_Position = vec4(position + actualPosition, 0.0, 1.0);
	texCoord = texCoordInput;
}

