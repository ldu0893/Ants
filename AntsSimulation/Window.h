#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
	public:
		Window(GLFWwindow* w);
	private:
		GLFWwindow* window;
		void loop();
		void processKeyboardInput();
};
