#pragma once

#ifndef SHADER_H_GUARD
#define SHADER_H_GUARD 

#include "globals.h"

#include <string>
#include <glm/glm.hpp>

class Shader {
	public:
		unsigned int id;

		Shader() : id(0) {};
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

		Shader& use();

		void compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

		void setBool(const char* name, bool value, bool useShader = false);
		void setFloat(const char* name, float value, bool useShader = false);
		void setInteger(const char* name, int value, bool useShader = false);
		void setVector2f(const char* name, float x, float y, bool useShader = false);
		void setVector2f(const char* name, const glm::vec2& value, bool useShader = false);
		void setVector3f(const char* name, float x, float y, float z, bool useShader = false);
		void setVector3f(const char* name, const glm::vec3& value, bool useShader = false);
		void setVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
		void setVector4f(const char* name, const glm::vec4& value, bool useShader = false);
		void setMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);

	private:	
		void checkCompileErrors(unsigned int object, std::string type);

		std::string readShader(const char* filePath) const;
};


#endif