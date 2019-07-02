// Alexander Zimmermann, 2019
#include "Application.h"
#include <code/RenderCore.h>

#include <iostream>

using namespace EngineCore;

Application::Application()
{
	pRenderer = new RenderCore(pWindow, &instance, &surface);
}

Application::~Application()
{
	delete pRenderer;
}

void Application::Run(const char * windowTitle, int width, int height)
{
	InitWindow(windowTitle, width, height);

	CreateInstance();
	CreateSurface();

	pRenderer->InitRenderer();
	
	while (!glfwWindowShouldClose(pWindow))
	{
		glfwPollEvents();
		pRenderer->RenderTick();
	}

	pRenderer->CleanUp();	

	if (enableValidationLayers) {
		DestroyDebugUtilsMessengerEXT(instance, callback, nullptr);
	}

	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyInstance(instance, nullptr);

	glfwDestroyWindow(pWindow);

	glfwTerminate();
}

VkInstance & EngineCore::Application::GetInstance()
{
	return instance;
}

VkSurfaceKHR & EngineCore::Application::GetSurface()
{	
	return surface;
}

void Application::InitWindow(const char * windowTitle, int width, int height) 
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	pWindow = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);

	glfwSetWindowUserPointer(pWindow, this);
	glfwSetWindowSizeCallback(pWindow, Application::OnWindowResized);
}

void Application::CreateInstance()
{
	if (enableValidationLayers && !CheckValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VERSION_ENG_AZ;
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VERSION_APP_AZ;
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = GetRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}
	VulkCheck(vkCreateInstance(&createInfo, nullptr, &instance));
}

void Application::SetupDebugCallback()
{
	if (!enableValidationLayers) return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = DebugCallback;

	VulkCheck(CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &callback));
}

void Application::CreateSurface()
{
	VulkCheck(glfwCreateWindowSurface(instance, pWindow, nullptr, &surface));
}

void Application::OnWindowResized(GLFWwindow * window, int width, int height)
{
	if (width == 0 || height == 0) return;

	Application* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
	app->bWindowResized = true;
}

VKAPI_ATTR VkBool32 VKAPI_CALL Application::DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData, void * pUserData)
{
	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

	return VK_FALSE;
}

bool EngineCore::Application::CheckValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

std::vector<const char*> EngineCore::Application::GetRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}
