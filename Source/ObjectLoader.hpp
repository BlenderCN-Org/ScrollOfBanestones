#include <string>
#include <vector>
#include <glm/glm.hpp>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#endif

class ObjectLoader
{
public:
    ObjectLoader(std::string objFile);
    ~ObjectLoader();

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    void CreateObject();
    void RenderObject();
private:
    GLuint vertexArrayID;
    GLuint vertexBuffer;
    GLuint uvBuffer;
};