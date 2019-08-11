#include "Renderer.hpp"

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
#ifndef NDEBUG
    std::cout << "OpenGL Version: " + std::string((char *)glGetString(GL_VERSION)) << std::endl;
    std::cout << "GLSL Version: " + std::string((char *)glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapWindow()
{
    SDL_GL_SwapWindow(m_Window);
}

Renderer* Renderer::GetInstance()
{
    if(!s_Instance)
    {
        s_Instance = new Renderer();
    }
    return s_Instance;
}