#include "ObjectLoader.hpp"

#include <iostream>

// We're using c std lib temporarily.
#include <stdio.h>
#include <stdlib.h>

ObjectLoader::ObjectLoader(std::string objFile)
{
    std::vector<unsigned int> vertexIndices;
    std::vector<unsigned int> uvIndices;
    std::vector<unsigned int> normalIndices;

    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempUvs;
    std::vector<glm::vec3> tempNormals;

    FILE* file = fopen(objFile.c_str(), "r");
    if(file != NULL)
    {
        // In future, we'll use Assimp which can do a much better job at reading a myriad of mesh formats, for now this toy method will do.
        while(true)
        {
            char lineHeader[128];
            int result = fscanf(file, "%s", lineHeader);
            if(result == EOF)
            {
                break;
            }
            else
            {
                if(strcmp(lineHeader, "v") == 0)
                {
                    glm::vec3 vertex;
                    fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                    tempVertices.push_back(vertex);
                }
                else if(strcmp(lineHeader, "vt") == 0)
                {
                    glm::vec2 uv;
                    fscanf(file, "%f %f\n", &uv.x, &uv.y);
                    tempUvs.push_back(uv);
                }
                else if(strcmp(lineHeader, "vn") == 0)
                {
                    glm::vec3 normal;
                    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                    tempNormals.push_back(normal);
                }
                else if(strcmp(lineHeader, "f") == 0)
                {
                    std::string vertex1, vertex2, vertex3;
                    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                        &vertexIndex[0],
                        &uvIndex[0],
                        &normalIndex[0],
                        &vertexIndex[1],
                        &uvIndex[1],
                        &normalIndex[1],
                        &vertexIndex[2],
                        &uvIndex[2],
                        &normalIndex[2]
                    );

                    if(matches == 9)
                    {
                        vertexIndices.push_back(vertexIndex[0]);
                        vertexIndices.push_back(vertexIndex[1]);
                        vertexIndices.push_back(vertexIndex[2]);
                        uvIndices.push_back(uvIndex[0]);
                        uvIndices.push_back(uvIndex[1]);
                        uvIndices.push_back(uvIndex[2]);
                        normalIndices.push_back(normalIndex[0]);
                        normalIndices.push_back(normalIndex[1]);
                        normalIndices.push_back(normalIndex[2]);
                    }
                    else
                    {
                        std::cerr << "File (" + objFile + ") can't be read by our simple parser." << std::endl;
                        break;
                    }
                }
            }
        }

        for(unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            unsigned int vertexIndex = vertexIndices[i];
            unsigned int uvIndex = uvIndices[i];
            unsigned int normalIndex = normalIndices[i];

            glm::vec3 vertex = tempVertices[vertexIndex - 1];
            glm::vec2 uv = tempUvs[uvIndex - 1];
            glm::vec3 normal = tempNormals[normalIndex - 1];

            vertices.push_back(vertex);
            uvs.push_back(uv);
            normals.push_back(normal);
        }
        fclose(file);
    }
    else
    {
        std::cerr << "Cannot read object (" + objFile + ") file." << std::endl;
    }
}

ObjectLoader::~ObjectLoader()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &uvBuffer);
    glDeleteVertexArrays(1, &vertexArrayID);
}

void ObjectLoader::CreateObject()
{
    // Generate VAO
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Generate buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    // Generate buffer
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec3), &uvs[0], GL_STATIC_DRAW);
}

void ObjectLoader::RenderObject()
{
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

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void ObjectLoader::SetPosition(glm::vec3 position)
{
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);

    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP", 1, GL_FALSE, glm::value_ptr(modelMatrix)));
}