#include "lve_window.hpp"
#include <iostream>

namespace lve {

glm::vec2 LveWindow::cursorPos = glm::vec2{};
glm::vec2 LveWindow::normalizedCursorPos = glm::vec2{};
bool LveWindow::leftMouseButtonDown = false;

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
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, frameBufferResizedCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
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

glm::vec2 LveWindow::getNormalizedCursorPos() {
	float centerX = width * 0.5f;
	float centerY = height * 0.5f;

	float relativeX = LveWindow::cursorPos.x - centerX;
	float relativeY = LveWindow::cursorPos.y - centerY;

	LveWindow::normalizedCursorPos.x = relativeX / centerX;
	LveWindow::normalizedCursorPos.y = relativeY / centerY;

	return LveWindow::normalizedCursorPos;
}

bool LveWindow::getLeftMouseButtonDown() {
	return leftMouseButtonDown;
}

void LveWindow::frameBufferResizedCallback(GLFWwindow* window, int width, int height) {
	auto lveWindow = reinterpret_cast<LveWindow*>(glfwGetWindowUserPointer(window));
	lveWindow->framebufferResized = true;
	lveWindow->width = width;
	lveWindow->height = height;
}

void LveWindow::cursorPosCallback(GLFWwindow* window, double x, double y) {
	LveWindow::cursorPos.x = (float)x;
	LveWindow::cursorPos.y = (float)y;
}

void LveWindow::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button != GLFW_MOUSE_BUTTON_1) return;

	if (action == GLFW_PRESS) {
		LveWindow::leftMouseButtonDown = true;
	}
	else if (action == GLFW_RELEASE) {
		LveWindow::leftMouseButtonDown = false;
	}
}
}