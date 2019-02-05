/**
* The application handles the glfw window,
* as well as the vkInstance and vkSurface
* in NDEBUG, it also handles validation layers.
*
* This class can be seen as a the 'canvas' the renderer writes to.
* It answers the question 'Where' something needs to be rendered to.
*
* Alexander Zimmermann, 2019
*/


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <code/Assert.h>

namespace EngineCore
{
	class RenderCore;

#define VERSION_AZ VK_MAKE_VERSION(1,0,0);
#define VERSION_ENG_AZ VERSION_AZ
#define VERSION_APP_AZ VERSION_AZ

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	class Application
	{
	public:
		Application();
		~Application();
		void Run(const char * windowTitle, int width, int height);
		void QueryFramebufferSize(int & width, int & height);
		void GetWindowSize(int & width, int & height);

		VkInstance & GetInstance();
		VkSurfaceKHR & GetSurface();

	private:
		void InitWindow(const char * windowTitle, int width, int height);

		void CreateInstance();
		void SetupDebugCallback();
		void CreateSurface();

		static void OnWindowResized(GLFWwindow* window, int width, int height);
		bool bWindowResized = false;

		GLFWwindow* pWindow;
		RenderCore* pRenderer;

		VkInstance instance;
		VkSurfaceKHR surface;

		// Debugging and Validating
		VkDebugUtilsMessengerEXT callback;
		static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
		bool CheckValidationLayerSupport();
		std::vector<const char*> GetRequiredExtensions();

	};
}