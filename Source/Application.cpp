#include "Application.hpp"

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

    // Init Window

    // Init OpenGL Options

    // Init Matrix
    
    // Init Shaders

    // Init Textures

    // Init Materials

    // Init Models

    // Init Lights

    // Init Uniforms

    while(m_Running)
    {
        Update();
        Render();
    }
    return 0;
}