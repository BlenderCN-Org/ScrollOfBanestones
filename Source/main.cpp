/* 
    *** READ THIS NOTICE *** READ THIS NOTICE *** READ THIS NOTICE ***

    This code is not "c++" code at the moment, more like C with bits of C++, this is temporary.
    it's only designed to show a proof of concept for the pre-production process.

    Once the pre-production stage is completed...
    ... I'll go about refactering the c++ code to be more in line with real c++.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

// I'm aware that OpenGL is deprecated on macOS, but most rendering code will be behind a wrapper anyway in production.
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#endif

#include <SDL.h>
#include <SDL_opengl.h>

// Rendering
void CreateTriangle();
void RenderTriangle();
GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath);

GLuint vertexArrayID;
GLuint vertexBuffer;
SDL_GLContext m_Context;

// Array of 3 vectors that will represent our triangle.
static const GLfloat g_VertexBufferData[] =
{
    -1.0f, -1.0f, -0.0f,
    1.0f, -1.0f, -0.0f,
    0.0f, 1.0f, -0.0f,
};
// Rendering end

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
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL Init Error: " + std::string(SDL_GetError()) << std::endl;
        return;
    }

    m_Window = SDL_CreateWindow("Scrolls of Banestones", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if(!m_Window)
    {
        std::cerr << "SDL CreateWindow Error: " + std::string(SDL_GetError()) << std::endl;
        return;
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

    m_Context = SDL_GL_CreateContext(m_Window);
    if(!m_Context)
    {
        std::cerr << "SDL GL CreateContext Error: " + std::string(SDL_GetError()) << std::endl;
        return;
    }

    std::cout << "OpenGL Version: " + std::string((char *)glGetString(GL_VERSION)) << std::endl;
    std::cout << "GLSL Version: " + std::string((char *)glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;

    GLuint programID = LoadShaders( "Data/SimpleVertexShader.glsl", "Data/SimpleFragmentShader.glsl" );

    CreateTriangle();

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
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        RenderTriangle();

        SDL_GL_SwapWindow(m_Window);
    }

    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

// Rendering
// Rendering code, very very messy, will clean up once in production.
void CreateTriangle()
{
#ifdef __APPLE__
    // Generate VAO
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
#else
    // Someone with windows/linux can do the non apple variants.
#endif

    // Generate buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_VertexBufferData), g_VertexBufferData, GL_STATIC_DRAW);
}

void RenderTriangle()
{
#ifdef __APPLE__
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
#else
    // Someone with windows/linux can do the non apple variants.
#endif

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath)
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
    if(vertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << vertexShaderStream.rdbuf();
        vertexShaderCode = sstr.str();
        vertexShaderStream.close();
    }
    else
    {
        std::cerr << "Cannot read " + std::string(vertexFilePath) << std::endl;
        return 0;
    }

    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
    if(fragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << fragmentShaderStream.rdbuf();
        fragmentShaderCode = sstr.str();
        fragmentShaderStream.close();
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    // Compile the vertex shader.
    std::cout << "Compiling vertex shader: " + std::string(vertexFilePath) << std::endl;
    char const *vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    // Check the vertex shader
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0)
    {
        std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        std::cerr << "Vertex Shader Error: " + std::string(&vertexShaderErrorMessage[0]) << std::endl;
    }

    std::cout << "Compiling fragment shader: " + std::string(vertexFilePath) << std::endl;
    char const *fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);

    // Check the vertex shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0)
    {
        std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        std::cerr << "Fragment Shader Error: " + std::string(&fragmentShaderErrorMessage[0]) << std::endl;
    }

    // Link shaders
    std::cout << "Linking shaders" << std::endl;
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Check the shaders
    std::cout << "Checking shaders" << std::endl;
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0)
    {
        std::vector<char> programErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
        std::cerr << "Shader Linking Error: " + std::string(&programErrorMessage[0]) << std::endl;
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}
// Rendering end