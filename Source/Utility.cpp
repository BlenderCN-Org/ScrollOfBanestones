#include <SDL.h>
#include "Utility.hpp"

Utility::Utility()
{

}

Utility::~Utility()
{

}

glm::vec2 Utility::GetScreenSize()
{
    SDL_DisplayMode displayMode;
    if(SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
    {
        return glm::vec2(0,0);
    }
    return glm::vec2(displayMode.w,displayMode.h);
}

std::string Utility::GetScreenSizeString()
{
    SDL_DisplayMode displayMode;
    if(SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
    {
        return nullptr;
    }
    return std::to_string(displayMode.w) + ", " + std::to_string(displayMode.h);
}
