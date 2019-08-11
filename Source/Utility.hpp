#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <glm/glm.hpp>
#include <string>

class Utility
{
public:
    Utility();
    ~Utility();

    static glm::vec2 GetScreenSize();
    static std::string GetScreenSizeString();
};

#endif // !UTILITY_HPP