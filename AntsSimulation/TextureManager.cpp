#include "TextureManager.h"

#include <iostream>
#include <glad/glad.h>

#include "globals.h"

/*
* Loads and caches the desired texture with OpenGL, to be retrieved/used later
* @param textureName: relative path to texture file should be IMAGES_DIR + textureName
* @returns tuple (width, height) of loaded texture file
*/
std::tuple<int, int> TextureManager::registerTexture(const char* textureName) {
	int width, height, numChannels;
	std::string loc = std::string(IMAGES_DIR) + textureName;
	unsigned char* data = stbi_load(loc.c_str(), &width, &height, &numChannels, 0);
	if (!data) {
		std::cout << "Failed to load texture at " << loc << std::endl;
		exit(-1);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_image_free(data);

	if (DEBUG && VERBOSE) std::cout << "[TextureManager] Successfully loaded image at "
		<< loc << "; width = " << width
		<< ", height = " << height
		<< ", numChannels = " << numChannels
		<< ", textureID = " << textureID << std::endl;
	textures[textureName] = textureID;
	return std::make_tuple(width, height);
}

