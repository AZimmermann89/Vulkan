#include "RenderCore.h"

RenderCore::RenderCore()
    : m_vkinstance{}
    , m_physicalDevices {}
    , m_logicalDevice{}
{
    Init();
}

RenderCore::~RenderCore()
{
}

VkResult RenderCore::Init()
{
    VkResult result{ VK_SUCCESS };
    result = InitInstance();

    if (result == VK_SUCCESS)
        result = InitPhysicalDevice();

    if (result == VK_SUCCESS)
        result = InitLogicalDevice();


//     // Getting the queue families from the physical device
//     if (result == VK_SUCCESS)
//     {
//         uint32_t queueFamilyCount{ 0 };
//         std::vector<VkQueueFamilyProperties> queueFamilyProperties{};
//         VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties{};
// 
//         vkGetPhysicalDeviceMemoryProperties(m_physicalDevices[0], &physicalDeviceMemoryProperties);
//         vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevices[0], &queueFamilyCount, nullptr);
// 
//         queueFamilyProperties.resize(queueFamilyCount);
// 
//         vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevices[0], &queueFamilyCount, queueFamilyProperties.data());
//     }

//     uint32_t numInstanceLayers{ 0 };
//     std::vector <VkLayerProperties> instanceLayerProperties;
// 
//     vkEnumerateInstanceLayerProperties(&numInstanceLayers, nullptr);
// 
//     if (numInstanceLayers != 0)
//     {
//         instanceLayerProperties.resize(numInstanceLayers);
//         vkEnumerateInstanceLayerProperties(&numInstanceLayers, instanceLayerProperties.data());
//     }

//     uint32_t numInstanceLayers{ 0 };
//     std::vector <VkLayerProperties> deviceLayerProperties;
// 
//     vkEnumerateDeviceLayerProperties(m_physicalDevices[0], &numInstanceLayers, nullptr);
// 
//     if (numInstanceLayers != 0)
//     {
//         deviceLayerProperties.resize(numInstanceLayers);
//         vkEnumerateDeviceLayerProperties(m_physicalDevices[0], &numInstanceLayers, deviceLayerProperties.data());
//     }

    return result;
}

VkResult RenderCore::InitLogicalDevice()
{
    VkPhysicalDeviceFeatures supportedFeatures{};
    VkPhysicalDeviceFeatures requredFeatures{};

    vkGetPhysicalDeviceFeatures(m_physicalDevices[0], &supportedFeatures);

    EnableDeviceFeatures(requredFeatures, supportedFeatures);

    const VkDeviceQueueCreateInfo deviceQueueCreateInfo{
        VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        nullptr,
        0,
        0,
        1,
        nullptr
    };

    const VkDeviceCreateInfo deviceCreateInfo{
        VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        nullptr,
        0,
        1,
        &deviceQueueCreateInfo,
        0,
        nullptr,
        0,
        nullptr,
        &requredFeatures
    };

    return vkCreateDevice(m_physicalDevices[0], &deviceCreateInfo, nullptr, &m_logicalDevice);
}

VkResult RenderCore::InitInstance()
{
    VkApplicationInfo appInfo{};
    VkInstanceCreateInfo instCreateInfo{};

    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = m_cApplicationName;
    appInfo.applicationVersion = m_cApplicationVersion;
    appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

    instCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instCreateInfo.pApplicationInfo = &appInfo;

    return vkCreateInstance(&instCreateInfo, nullptr, &m_vkinstance);
}

VkResult RenderCore::InitPhysicalDevice()
{
    VkResult result{ VK_SUCCESS };
    uint32_t physicalDeviceCount{ 0 };
    result = vkEnumeratePhysicalDevices(m_vkinstance, &physicalDeviceCount, nullptr);

    if (result == VK_SUCCESS)
    {
        m_physicalDevices.resize(physicalDeviceCount);
        result = vkEnumeratePhysicalDevices(m_vkinstance, &physicalDeviceCount, &m_physicalDevices[0]);
    }
    return result;
}

void RenderCore::EnableDeviceFeatures(VkPhysicalDeviceFeatures &requredFeatures, VkPhysicalDeviceFeatures &supportedFeatures)
{
    requredFeatures.multiDrawIndirect = supportedFeatures.multiDrawIndirect;
    requredFeatures.tessellationShader = VK_TRUE;
    requredFeatures.geometryShader = VK_TRUE;
}
