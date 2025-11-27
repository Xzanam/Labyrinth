//
// Created by Janam Shrestha on 10/16/25.
//

#ifndef CUBE_H
#define CUBE_H

#include "Core/Renderer/Mesh.h"
#include <memory>

#include "Core/Renderer/Shader.h"

class Cube {

private:
    std::unique_ptr<Core::Mesh> cubeMesh;
    glm::mat4 modelMatrix;

public :
    Cube();
    inline std::pair<std::vector<Core::Vertex>, std::vector<unsigned int>>GenerateCube(float = 1.0f);
    void OnRender(Core::Shader& shader) const;
    ~Cube();





};



#endif //CUBE_H
