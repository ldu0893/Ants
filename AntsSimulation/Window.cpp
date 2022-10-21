#include <iostream>

#include "globals.h"
#include "Window.h"

Window::Window(GLFWwindow* w) {
	gameLoop();
}

void Window::gameLoop() {
	if (DEBUG) glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void mouse_button_callback(GLFWwindow* window_, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		int width, height;
		glfwGetWindowSize(window_, &width, &height);
		double xpos, ypos;
		glfwGetCursorPos(window_, &xpos, &ypos);
		std::cout << "Cursor position at (" << 2.0f * ((float)(xpos / width)) - 1.0f
			<< " : " << 1.0f - 2.0f * ((float)(ypos / height)) << ")" << std::endl;
	}
}
