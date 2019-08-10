#ifndef OBJECT_LOADER_HPP
#define OBJECT_LOADER_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    void SetPosition(glm::vec3 position);
    void SetRotiation(glm::vec3 rotation);
    void SetScale(glm::vec3 scale);
private:
    GLuint vertexArrayID;
    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint programID;

    glm::mat4 objectMatrix;
    glm::vec4 objectVector;
};

#endif // OBJECT_LOADER_HPP