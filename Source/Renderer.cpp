#include "Renderer.hpp"
#include <iostream>

Renderer* Renderer::m_Instance = nullptr;

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::CreateContext(SDL_Window* window)
{
    // Set it to the OpenGL core as we should not be using any deprecated GL calls.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // macOS only supports upto OpenGL 4.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    m_Window = window;
    m_Context = SDL_GL_CreateContext(window);
    if(!m_Context)
    {
        std::cerr << "SDL GL CreateContext Error: " + std::string(SDL_GetError()) << std::endl;
        return;
    }

#ifndef NDEBUG
    std::cout << "OpenGL Version: " + std::string((char *)glGetString(GL_VERSION)) << std::endl;
    std::cout << "GLSL Version: " + std::string((char *)glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
#endif
}

void Renderer::DestroyContext()
{
    SDL_GL_DeleteContext(m_Context);
}

void Renderer::SwapWindow()
{
    SDL_GL_SwapWindow(m_Window);
}

void Renderer::Clear()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Renderer* Renderer::GetInstance()
{
    if(!m_Instance)
    {
        m_Instance = new Renderer();
    }
    return m_Instance;
}

SDL_GLContext Renderer::GetContext()
{
    return m_Context;
}