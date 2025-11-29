//
// Created by Janam Shrestha on 10/16/25.
//

#ifndef CUBE_H
#define CUBE_H

#include "Core/Renderer/Mesh.h"
#include <memory>
#include "Object.h"
class Cube : public Game::Object
{
private:

public:
    Cube();
    Cube(const glm::mat4 &matrix, const glm::vec3 &col); 

    inline std::pair<std::vector<Core::Vertex>, std::vector<unsigned int>> GenerateCube(float size = 1.0f);

  


    ~Cube();
};

#endif // CUBE_H
