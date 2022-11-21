#pragma once

#include <map>
#include <string>
#include <tuple>
#include "stb_image.h"

class TextureManager {
public:
	static TextureManager& getInstance() {
		static TextureManager instance;
		return instance;
	}
	std::tuple<int, int> registerTexture(const char* textureName);
	unsigned int getTextureID(const char* tex) { return textures[tex]; }

private:
	std::map<const char*, unsigned int> textures;
	TextureManager() { stbi_set_flip_vertically_on_load(true); }
};


