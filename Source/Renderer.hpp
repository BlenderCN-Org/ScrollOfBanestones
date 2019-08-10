#ifndef RENDERER_H
#define RENDERER_H

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void CreateContext(SDL_Window* window);
    void DestroyContext();
    void SwapWindow();
    void Clear();

    static Renderer* GetInstance();
    SDL_GLContext GetContext();
private:
    static Renderer* m_Instance;
    SDL_GLContext m_Context;
    SDL_Window* m_Window;
};

#endif // RENDERER_H