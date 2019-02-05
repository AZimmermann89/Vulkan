// Alexander Zimmermann, 2017
#include <code/Application.h>
#include <iostream>

int main() {
	EngineCore::Application app{};

    try {
		app.Run("ARenderer_v1", 800, 600);
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*


TODO:
____________________________________________________________________________________

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

Replace the Image Loader by an own image loader

*/
