/* 
    This code is not "c++" code at the moment, more like C than C++, this is temporary.
    it's only designed to show a proof of concept for the pre-production process.

    Once the pre-production stage is completed...
    ... I'll go about refactering the c++ code to be more in line with real c++.
*/

#include <iostream>
#include <SDL.h>

void CreateWindow();

SDL_Window* m_Window;

int main(int argc, char *argv[])
{
    std::cout << "Hello World" << std::endl;
    CreateWindow();
    return 0;
}

void CreateWindow()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL Init Error: " + std::string(SDL_GetError()) << std::endl;
        return;
    }

    m_Window = SDL_CreateWindow("Scrolls of Banestones", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    if(!m_Window)
    {
        std::cerr << "SDL CreateWindow Error: " + std::string(SDL_GetError()) << std::endl;
        return;
    }

    SDL_Event event;
    bool running = true;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}