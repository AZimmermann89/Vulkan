// Alexander Zimmermann, 2017
#include <code/RenderCore.h>
#include <iostream>

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