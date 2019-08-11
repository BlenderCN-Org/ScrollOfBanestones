#include "Application.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Logging.hpp"
#include "Utility.hpp"
#include <SDL.h>
#include <iostream>
#include <chrono>
#include <thread>

Application::Application(int argc, char* argv[])
    : m_Running(true)
{
    
}

Application::~Application()
{

}

int Application::Run()
{
    // Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Cannot init SDL: " + std::string(SDL_GetError()) << std::endl;
        return 1;
    }

    // Init Window
    Log(LogLevel::Info) << "Screen Size: " + Utility::GetScreenSizeString();
    if(Window::GetInstance()->CreateWindow("Scrolls of Banestones", glm::vec2(Utility::GetScreenSize()), false) != true)
    {
        std::cerr << "Cannot create window: " + std::string(SDL_GetError()) << std::endl;
        return 1;
    }

    // Init OpenGL Options
    if(Renderer::GetInstance()->CreateContext(Window::GetInstance()->GetWindow()) != true)
    {
        std::cerr << "Cannot create renderer: " + std::string(SDL_GetError()) << std::endl;
        return 1;
    }

    // Init Matrix
    
    // Init Shaders

    // Init Textures

    // Init Materials

    // Init Models

    // Init Lights

    // Init Uniforms

    Window::GetInstance()->ShowWindow();
    while(m_Running)
    {
        Update();
        Render();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}

void Application::Update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                m_Running = false;
                break;
        }
    }
    Renderer::GetInstance()->Clear();
}

void Application::Render()
{
    Renderer::GetInstance()->SwapWindow();
}