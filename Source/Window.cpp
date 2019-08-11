#include "Window.hpp"

Window* Window::s_Instance = nullptr;

Window::Window()
{

}

Window::~Window()
{

}

bool Window::CreateWindow(std::string title, glm::vec2 windowSize, bool fullScreen)
{
    Uint32 flags = SDL_WINDOW_OPENGL|SDL_WINDOW_HIDDEN;
    m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y, flags);
    if(!m_Window)
    {
        return false;
    }
    return true;
}

void Window::DestroyWindow()
{
    if(m_Window)
    {
        SDL_DestroyWindow(m_Window);
    }
}

void Window::ShowWindow()
{
    SDL_ShowWindow(m_Window);
}

void Window::HideWindow()
{
    SDL_HideWindow(m_Window);
}

void Window::ToggleFullscreen(bool fullscreen)
{
    if(fullscreen)
    {
        SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    else
    {
        SDL_SetWindowFullscreen(m_Window, 0);
    }
}

Window* Window::GetInstance()
{
    if(!s_Instance)
    {
        s_Instance = new Window();
    }
    return s_Instance;
}

void Window::Update()
{

}