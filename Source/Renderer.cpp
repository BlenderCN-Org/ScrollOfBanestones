#include "Renderer.hpp"
#include "Logging.hpp"

Renderer* Renderer::s_Instance = nullptr;

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

bool Renderer::CreateContext(SDL_Window* window)
{
    m_Window = window;
    // Set it to the OpenGL core as we should not be using any deprecated GL calls.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // macOS only supports upto OpenGL 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    m_Context = SDL_GL_CreateContext(m_Window);
    if(!m_Context)
    {
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#ifndef NDEBUG
    Log(LogLevel::Info) << "OpenGL Version: " + std::string((char *)glGetString(GL_VERSION));
    Log(LogLevel::Info) << "GLSL Version: " + std::string((char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif
    return true;
}

void Renderer::DestroyContext()
{
    SDL_GL_DeleteContext(m_Context);
}

void Renderer::Clear()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::SwapWindow()
{
    SDL_GL_SwapWindow(m_Window);
    glFlush();
}

Renderer* Renderer::GetInstance()
{
    if(!s_Instance)
    {
        s_Instance = new Renderer();
    }
    return s_Instance;
}