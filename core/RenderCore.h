// Alexander Zimmermann, 2017
#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <vector>
#include <array>

const int WIDTH = 800;
const int HEIGHT = 600;
const bool FULLSCREEN = false;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

inline VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
    auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pCallback);
    }
    else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

inline void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
    if (func != nullptr) {
        func(instance, callback, pAllocator);
    }
}

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;
    int transferFamily = -1;

    bool IsComplete() {
        return graphicsFamily >= 0 && presentFamily >= 0 && transferFamily >= 0;
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
    glm::vec2 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription GetBindingDescription()
    {
        VkVertexInputBindingDescription bindingDescription{};

        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions {};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

const std::vector<Vertex> vertices = {
    { { -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f } },
    { { 0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f } },
    { { 0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f } },
    { { -0.5f, 0.5f },{ 1.0f, 1.0f, 1.0f } }
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0
};

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

class RenderCore {

public:
    RenderCore();
    ~RenderCore();

    void Run();

private:
    GLFWwindow* m_pWindow;

    VkInstance m_instance;
    VkDebugReportCallbackEXT m_callback;
    VkSurfaceKHR m_surface;

    VkPhysicalDevice m_physicalDevice;
    VkDevice m_device;

    VkQueue m_graphicsQueue;
    VkQueue m_presentQueue;
    VkQueue m_transferQueue;

    VkSwapchainKHR m_swapChain;
    std::vector<VkImage> m_swapChainImages;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;
    std::vector<VkImageView> m_swapChainImageViews;
    std::vector<VkFramebuffer> m_swapChainFramebuffers;

    VkRenderPass m_renderPass;
    VkDescriptorSetLayout m_descriptorSetLayout;
    VkPipelineLayout m_pipelineLayout;
    VkPipeline m_graphicsPipeline;

    VkCommandPool m_graphicsCommandPool;
    VkCommandPool m_transferCommandPool;
    std::vector<VkCommandBuffer> m_commandBuffers;

    VkSemaphore m_imageAvailableSemaphore;
    VkSemaphore m_renderFinishedSemaphore;

    VkBuffer m_vertexBuffer;
    VkDeviceMemory m_vertexBufferMemory;
    VkBuffer m_indexBuffer;
    VkDeviceMemory m_indexBufferMemory;
    VkBuffer m_uniformBuffer;
    VkDeviceMemory m_uniformBufferMemory;

    void InitWindow();
    void InitVulkan();
    void MainLoop();
    void CleanUpSwapChain();
    void CleanUp();

    static void OnWindowResized(GLFWwindow* window, int width, int height);

    void RecreateSwapChain();
    void CreateInstance();
    void SetupDebugCallback();
    void CreateSurface();
    void PickPhysicalDevice();
    void CreateLogicalDevice();
    void CreateSwapChain();
    void CreateImageViews();
    void CreateRenderPass();
    void CreateDescriptorSetLayout();
    void CreateGraphicsPipeline();
    void CreateFramebuffers();
    void CreateCommandPool();
    void CreateCommandBuffers();
    void CreateSemaphores();
    void CreateVertexBuffer();
    void CreateIndexBuffer();
    void CreateUniformBuffer();
    
    void UpdateUniformBuffer();
    void DrawFrame();
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);


    VkShaderModule CreateShaderModule(const std::vector<char>& code);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    bool IsDeviceSuitable(VkPhysicalDevice device);
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    std::vector<const char*> GetRequiredExtensions();
    bool CheckValidationLayerSupport();
    static std::vector<char> ReadFile(const std::string& filename);
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
};

/* 
TODO:

It should be noted that in a real world application, you're not supposed to actually call vkAllocateMemory for every individual buffer.
The maximum number of simultaneous memory allocations is limited by the maxMemoryAllocationCount physical device limit, 
which may be as low as 4096 even on high end hardware like an NVIDIA GTX 1080. 
The right way to allocate memory for a large number of objects at the same time is to create a custom allocator that splits up a single allocation among many different objects
by using the offset parameters that we've seen in many functions.

You can either implement such an allocator yourself, or use the VulkanMemoryAllocator library provided by the GPUOpen initiative. 
However, for this tutorial it's okay to use a separate allocation for every resource, 
because we won't come close to hitting any of these limits for now.
______________________________________________________________________________________________________________________________

The previous chapter already mentioned that you should allocate multiple resources like buffers from a single memory allocation, 
but in fact you should go a step further. Driver developers recommend that you also store multiple buffers, like the vertex and index buffer, 
into a single VkBuffer and use offsets in commands like vkCmdBindVertexBuffers. 
The advantage is that your data is more cache friendly in that case, because it's closer together. 
It is even possible to reuse the same chunk of memory for multiple resources if they are not used during the same render operations,
provided that their data is refreshed, of course. 
This is known as aliasing and some Vulkan functions have explicit flags to specify that you want to do this.
______________________________________________________________________________________________________________________________



*/