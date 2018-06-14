// Alexander Zimmermann, 2017
#include <code/RenderCore.h>
#include <iostream>

// https://vulkan-tutorial.com/Texture_mapping/Image_view_and_sampler somewhere here I guess?

int main() {
    EngineCore::RenderCore rendCore{};
    
    try {
        rendCore.Run();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}