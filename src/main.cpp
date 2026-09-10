#include <iostream>
#include <SDL3/SDL.h>

#include "Application.h"

int main() {
    Application app;
    ApplicationConfig config;
    config.title = "My OpenGL App";
    config.windowWidth = 800;
    config.windowHeight = 600;

    if (!app.Initialize(config)) {
        std::cerr << "Failed to initialize application." << std::endl;
        return -1;
    }

    return app.Run();
}