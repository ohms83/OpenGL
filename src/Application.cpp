#include "Application.h"

#include "logging/Log.h"

#include <glad/glad.h>
#include <sstream>

DEFINE_LOG(Application);

Application::~Application()
{
    SDL_Quit();
}

bool Application::Initialize(const ApplicationConfig &config)
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) == false )
    {
        LOG_ERROR(LogApplication, std::format("SDL could not initialize! SDL error: {}\n", SDL_GetError()));
        return false;
    }

    int flags = config.fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    flags |= config.resizable ? SDL_WINDOW_RESIZABLE : 0;
    flags |= config.maximize ? SDL_WINDOW_MAXIMIZED : 0;

    flags |= SDL_WINDOW_OPENGL;
    flags |= SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS;
    
    m_window = SDL_CreateWindow(config.title.c_str(), config.windowWidth, config.windowHeight, flags);
    if (!m_window)
    {
        LOG_ERROR(LogApplication, std::format("Window could not be created! SDL error: {}\n", SDL_GetError()));
        return false;
    }

    if (!InitializeOpenGL())
    {
        LOG_ERROR(LogApplication, "Failed to initialize OpenGL.");
        return false;
    }

    return true;
}

int Application::Run()
{
    SDL_Event e;
    SDL_zero(e);

    while (!m_quit)
    {
        PollEvents(e);
        // Rendering code would go here

        SDL_GL_SwapWindow(m_window);
    }
    return 0;
}

void Application::RequestQuit()
{
    if (m_quit)
    {
        LOG_WARNING(LogApplication, "Quit has already been requested.");
        return;
    }

    m_quit = true;
    LOG_INFO(LogApplication, "Quit requested.");
}

bool Application::InitializeOpenGL()
{
    m_glContext = SDL_GL_CreateContext(m_window);
    if (!m_glContext)
    {
        LOG_ERROR(LogApplication, std::format("OpenGL context could not be created! SDL error: {}\n", SDL_GetError()));
        return false;
    }

    // TODO: Make it configurable.
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    m_glContext = SDL_GL_CreateContext(m_window);
    if (!m_glContext)
    {
        LOG_FATAL(LogApplication, std::format("Failed to created OpenGL's context! SDL_Error={}", SDL_GetError()));
        return false;
    }

    if (!gladLoadGLLoader(R_CAST<GLADloadproc>(SDL_GL_GetProcAddress)))
    {
        LOG_FATAL(LogApplication, "Failed to initialize GLAD");
        return false;
    }

    SDL_GL_MakeCurrent(m_window, m_glContext);

    std::stringstream ss;
    ss  << "OpenGL\n"
        << "  Version : " << glGetString(GL_VERSION) << "\n"
        << "  GLSL    : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n"
        << "  Vendor  : " << glGetString(GL_VENDOR) << "\n"
        << "  Renderer: " << glGetString(GL_RENDERER);
    LOG_INFO(LogApplication, ss.str());
    return true;
}

void Application::PollEvents(SDL_Event &e)
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            RequestQuit();
            break;
        }

        if (e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && e.window.windowID == SDL_GetWindowID(m_window))
        {
            RequestQuit();
            break;
        }

        if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE)
        {
            RequestQuit();
            break;
        }

        OnEvent(e);
    }
}
