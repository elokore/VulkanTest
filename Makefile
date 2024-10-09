VULKAN_SDK_PATH = ~/VulkanSDK/1.3.280.1/x86_64

CFLAGS = -std=c++17 -O3 -I$(VULKAN_SDK_PATH)/include
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanTest: main.cpp
	g++ $(CFLAGS) -o VulkanTest main.cpp lve_window.cpp lve_pipeline.cpp lve_device.cpp first_app.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	./VulkanTest

clean:
	rm -f VulkanTest