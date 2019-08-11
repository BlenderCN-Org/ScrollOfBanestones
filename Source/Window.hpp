#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <glm/glm.hpp>
#include <SDL.h>

class Window
{
public:
    Window();
    ~Window();

    bool CreateWindow(std::string title, glm::vec2 windowSize, bool fullScreen);
    void DestroyWindow();
    void ShowWindow();
    void HideWindow();

    void ToggleFullscreen(bool fullscreen);
    static Window* GetInstance();
    SDL_Window* GetWindow();
private:
    void Update();
private:
    static Window* s_Instance;
    SDL_Window* m_Window;
};

#endif // !WINDOW_HPP