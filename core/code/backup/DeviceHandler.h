/**
* Handles the Device as well as Queues and offers an interface for these.
*
* Alexander Zimmermann, 2019
*/
#pragma once

#include <vulkan/vulkan.h>
#include <optional>
#include <vector>

namespace EngineCore {

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool IsComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
	
	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	struct DeviceInfoBundle
	{
		VkDevice* pDevice = nullptr;
		VkPhysicalDevice* pPhysicalDevice = nullptr;

		
	};

	class DeviceHandler {

		VkInstance* pInstance;
		VkSurfaceKHR* pSurface;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		void PickPhysicalDevice(VkPhysicalDevice & physicalDevice, VkSampleCountFlagBits & msaaSamples) const;
		bool IsDeviceSuitable(const VkPhysicalDevice & device) const;
		QueueFamilyIndices FindQueueFamilies(const VkPhysicalDevice & device) const;
		bool CheckDeviceExtensionSupport(const VkPhysicalDevice & device) const;
		SwapChainSupportDetails QuerySwapChainSupport(const VkPhysicalDevice & device) const;

	public:
		DeviceHandler(VkInstance* instance, VkSurfaceKHR* surface);

		void InitDevice();
		void CleanUp();

	};
}

