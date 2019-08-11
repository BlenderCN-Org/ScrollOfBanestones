#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <iostream>
#if __APPLE__
    #include <OpenGL/gl3.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool CreateContext(SDL_Window* window);
    void DestroyContext();
    void Clear();
    void SwapWindow();
    static Renderer* GetInstance();
private:
    SDL_Window* m_Window;
    SDL_GLContext m_Context;
    static Renderer* s_Instance;
};

#endif // !RENDERER_HPP