#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

class RenderCore {

    const char* m_cApplicationName = "MyApplication";
    const int   m_cApplicationVersion = 1;

public:
    RenderCore();
    ~RenderCore();

    VkResult Init();

private:
    VkInstance m_vkinstance;
    std::vector<VkPhysicalDevice> m_physicalDevices;
    VkDevice m_logicalDevice;

    VkResult InitInstance();
    VkResult InitPhysicalDevice();
    VkResult InitLogicalDevice();

    void EnableDeviceFeatures(VkPhysicalDeviceFeatures &requredFeatures, VkPhysicalDeviceFeatures &supportedFeatures);
};