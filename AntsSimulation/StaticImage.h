#pragma once

#include <glm/glm.hpp>

#include "Shader.h"

class StaticImage {
	public:
		StaticImage(const char* imagePath, glm::vec2 bottomLeft, glm::vec2 topRight);
		void draw();
	private:
		const char* imagePath;
		const glm::vec2 bottomLeft;
		const glm::vec2 topRight;
		unsigned int VAO, VBO;
		Shader shader;
		unsigned int textureID;
};
