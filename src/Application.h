#pragma once

#include "Define.h"

#include <SDL3/SDL.h>
#include <string>

struct ApplicationConfig
{
    std::string title = "OpenGL Engine";
    int windowWidth = 800;
    int windowHeight = 600;
    bool fullscreen = false;
    bool resizable = true;
    bool maximize = false;
};

class Application
{
public:
    Application() = default;
    virtual ~Application();

    NODISCARD bool Initialize(const ApplicationConfig& config);

    NODISCARD int Run();
    void RequestQuit();

protected:
    NODISCARD bool InitializeOpenGL();

    void PollEvents(SDL_Event& e);
    virtual void OnEvent(const SDL_Event& e) {}

private:
    SDL_Window* m_window = nullptr;
    SDL_GLContext m_glContext = nullptr;
    bool m_quit = false;
};