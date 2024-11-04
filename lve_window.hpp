#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

namespace lve {

	class LveWindow {
	public:
		LveWindow(int w, int h, std::string name);
		~LveWindow();

		LveWindow(const LveWindow&) = delete;
		LveWindow &operator=(const LveWindow&) = delete;

		bool shouldClose() { return glfwWindowShouldClose(window); }
		void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);
		VkExtent2D getExtent();
		bool wasWindowResized() { return framebufferResized; };
		void resetWindowResizedFlag() { framebufferResized = false; };

		glm::vec2 getNormalizedCursorPos();
		bool getLeftMouseButtonDown();
		
	private:
		static void frameBufferResizedCallback(GLFWwindow* window, int width, int height);
		static void cursorPosCallback(GLFWwindow* window, double x, double y);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		void initWindow();

		static glm::vec2 cursorPos;
		static glm::vec2 normalizedCursorPos;
		static bool leftMouseButtonDown;

		int width;
		int height;
		bool framebufferResized = false;

		std::string windowName;
		GLFWwindow* window;
	};
}