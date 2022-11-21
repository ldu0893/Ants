#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture1;
uniform int frameNum;
uniform float frameHorizSize;
uniform int direction;

void main()
{
	vec2 actualTexCoord;
	if (direction == 1) {
		actualTexCoord = vec2(frameHorizSize + 1.0 - texCoord.x + frameNum * frameHorizSize, texCoord.y);
	} else {
		actualTexCoord = vec2(texCoord.x + frameNum * frameHorizSize, texCoord.y);
	}
	FragColor = texture(texture1, actualTexCoord);
}



