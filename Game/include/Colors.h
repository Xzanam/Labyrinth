#ifndef COLORS_H
#define COLORS_H

#include <glm/glm.hpp>
namespace Colors { 
    inline constexpr glm::vec3 Red     = glm::vec3(1.0f, 0.0f, 0.0f);
    inline constexpr glm::vec3 Green   = glm::vec3(0.0f, 1.0f, 0.0f);
    inline constexpr glm::vec3 Blue    = glm::vec3(0.0f, 0.0f, 1.0f);
    inline constexpr glm::vec3 Gray    = glm::vec3(0.5f, 0.5f, 0.5f);
    inline constexpr glm::vec3 Black   = glm::vec3(0.0f, 0.0f, 0.0f);
}

#endif //COLORS_H