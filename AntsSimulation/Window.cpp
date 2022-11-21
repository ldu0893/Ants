#include <iostream>

#include "globals.h"
#include "Window.h"
#include "TextureManager.h"
#include "Shader.h"
#include "StaticImage.h"

Window::Window(GLFWwindow* w) : window(w) {
	loop();
}

void Window::loop() {
	StaticImage background("black.png", glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f));
	while (!glfwWindowShouldClose(window)) {
		processKeyboardInput();
	}
	//if (DEBUG) glfwSetMouseButtonCallback(window, mouse_button_callback);
}

void Window::processKeyboardInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
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
