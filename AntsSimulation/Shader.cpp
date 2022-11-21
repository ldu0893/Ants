#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) : id(0) {
	if (VERBOSE) std::cout << "vertexPath: " << vertexPath;

	// read files
	std::string vertexSource = readShader(vertexPath);
	std::string fragmentSource = readShader(fragmentPath);
	std::string geometrySource = readShader(geometryPath);

	// get C-string versions of files
	const char* vertexSourcePtr = vertexSource.length() == 0 ? nullptr : vertexSource.c_str();
	const char* fragmentSourcePtr = fragmentSource.length() == 0 ? nullptr : fragmentSource.c_str();
	const char* geometrySourcePtr = geometrySource.length() == 0 ? nullptr : geometrySource.c_str();

	// assert that at least vertex and fragment shaders exist
	if (!vertexSourcePtr) {
		std::cout << "[Shader] vertexSourcePtr is nullptr" << std::endl;
		exit(-1);
	}
	if (!fragmentSourcePtr) {
		std::cout << "[Shader] fragmentSourcePtr is nullptr" << std::endl;
		exit(-1);
	}

	// compile shader
	compile(vertexSourcePtr, fragmentSourcePtr, geometrySourcePtr);

	if (DEBUG && VERBOSE) std::cout << "[Shader] successfully compiled shaders; "
		<< "vertex = " << (vertexPath ? vertexPath : "nullptr")
		<< ", fragment = " << (fragmentPath ? fragmentPath : "nullptr")
		<< ", geometry = " << (geometryPath ? geometryPath : "nullptr") << std::endl;
}

Shader& Shader::use() {
	glUseProgram(id);
	return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
	unsigned int sVertex, sFragment, gShader;

	// vertex shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");

	// fragment shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");

	// geometry shader (optional, can be nullptr)
	if (geometrySource != nullptr) {
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}

	// shader program
	id = glCreateProgram();
	glAttachShader(id, sVertex);
	glAttachShader(id, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(id, gShader);
	glLinkProgram(id);
	checkCompileErrors(id, "PROGRAM");

	// delete used shaders
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		glDeleteShader(gShader);
}

void Shader::setBool(const char* name, bool value, bool useShader) {
	if (useShader) use();
	glUniform1i(glGetUniformLocation(id, name), (int)value);
}

void Shader::setFloat(const char* name, float value, bool useShader) {
	if (useShader) use();
	glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::setInteger(const char* name, int value, bool useShader) {
	if (useShader) use();
	glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::setVector2f(const char* name, float x, float y, bool useShader) {
	if (useShader) use();
	glUniform2f(glGetUniformLocation(id, name), x, y);
}

void Shader::setVector2f(const char* name, const glm::vec2& value, bool useShader) {
	if (useShader) use();
	glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}

void Shader::setVector3f(const char* name, float x, float y, float z, bool useShader) {
	if (useShader) use();
	glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void Shader::setVector3f(const char* name, const glm::vec3& value, bool useShader) {
	if (useShader) use();
	glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const char* name, float x, float y, float z, float w, bool useShader) {
	if (useShader) use();
	glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}

void Shader::setVector4f(const char* name, const glm::vec4& value, bool useShader) {
	if (useShader) use();
	glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const char* name, const glm::mat4& matrix, bool useShader) {
	if (useShader) use();
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n-- ---------------------------------------------------- --"
				<< std::endl;
			exit(-1);
		}
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n-- ------------------------------------------------------ --"
				<< std::endl;
			exit(-1);
		}
	}
}

std::string Shader::readShader(const char* filePath) const {
	if (filePath == nullptr) return std::string();

	std::string code;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	if (DEBUG) std::cout << "[Shader] Reading file" << std::endl;
	try {
		// read file into stream
		shaderFile.open(filePath);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		// turn stream into string
		code = shaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}

	return code;
}
