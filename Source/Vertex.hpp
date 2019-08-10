#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 colour;
    glm::vec3 textcoord;
    glm::vec3 normal;
};

#endif // !VERTEX_H