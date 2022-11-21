#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "globals.h"
#include "forward_declarators.h"
#include "Window.h"

#include <vector>
#include <string>

GLFWwindow* setup_glfw_window() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ant Simulation", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
	});
	
	if (DEBUG) std::cout << "[Main] Successfully created window" << std::endl;
	return window;
}

int main(int argc, char* argv[]) {
	std::ofstream out("workingdir.txt");
	GLFWwindow* glfwWindow;
	Window* window;

	if (DEBUG) std::cout << "[Main] Starting application" << std::endl;
	glfwWindow = setup_glfw_window();
	window = new Window(glfwWindow);

	if (DEBUG) std::cout << "[Main] Terminating program" << std::endl;
	delete window;
	glfwTerminate();

	return 0;
}