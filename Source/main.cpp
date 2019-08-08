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

#include "ObjectLoader.hpp"

// Matrix
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Rendering
void CreateTriangle();
void RenderTriangle();
GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath);

GLuint colourID;
GLuint vertexArrayID;
GLuint vertexBuffer;
SDL_GLContext m_Context;

// Array of 3 vectors that will represent our triangle.
static const GLfloat g_VertexBufferData[] =
{
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

static const GLfloat g_Color_Buffer_Data[] =
{
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
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

    int width = 1280;
    int height = 800;
    m_Window = SDL_CreateWindow("Scrolls of Banestones", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
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

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    glm::mat4 viewMatrix = glm::lookAt(
        glm::vec3(4.0f, 3.0f, 3.0f), 
        glm::vec3(0.0f, 0.0f, 0.0f), 
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 modelViewProjection = projectionMatrix * viewMatrix * modelMatrix;

    GLuint matrixID = glGetUniformLocation(programID, "MVP");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    ObjectLoader monkey("Data/Models/Monkey.obj");
    monkey.CreateObject();

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

        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &modelViewProjection[0][0]);

        monkey.RenderObject();

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
    // Generate VAO
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Generate buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_VertexBufferData), g_VertexBufferData, GL_STATIC_DRAW);

    // Generate Colours
    glGenBuffers(1, &colourID);
    glBindBuffer(GL_ARRAY_BUFFER, colourID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_Color_Buffer_Data), g_Color_Buffer_Data, GL_STATIC_DRAW);
}

void RenderTriangle()
{
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Vertex Array
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

    // Colours
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colourID);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glDrawArrays(GL_TRIANGLES, 0, 12*3);
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

    std::cout << "Compiling fragment shader: " + std::string(fragmentFilePath) << std::endl;
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