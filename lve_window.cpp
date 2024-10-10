#include "lve_window.hpp"
#include <iostream>

namespace lve {

LveWindow::LveWindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{name} {
	initWindow();
}

LveWindow::~LveWindow() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void LveWindow::initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

void LveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
	if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface");
	}
}

VkExtent2D LveWindow::getExtent() {
	VkExtent2D extent;
	extent.width = (uint32_t)width;
	extent.height = (uint32_t)height;
	return extent;
}

}