#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include <glm/glm.hpp>

class Application
{
public:
    Application(int argc, char* argv[]);
    ~Application();

    int Run();
private:
    void Update();
    void Render();
private:
    bool m_Running;
};

#endif // !APPLICATION_HPP