//
// Created by Janam Shrestha on 10/16/25.
//


#include "Cube.h"

#include "Shader.h"


Cube::Cube() {
    auto [vertices, indices] = this->GenerateCube();
    cubeMesh = std::make_unique<Core::Mesh>(vertices, indices);
    modelMatrix = glm::mat4(1.0f);
}

Cube::~Cube() {
}



void Cube::OnRender(Core::Shader& shader) const {
    shader.use();
    shader.setMat4("model", modelMatrix);
    cubeMesh->Draw();
}


std::pair<std::vector<Core::Vertex>, std::vector<unsigned int> > Cube::GenerateCube(float size)   {
        float half = size / 2.0f;

    std::vector<Core::Vertex> vertices = {
        // Front face
        {{-half, -half,  half}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ half, -half,  half}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ half,  half,  half}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-half,  half,  half}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        // Back face
        {{ half, -half, -half}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{-half, -half, -half}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        {{-half,  half, -half}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
        {{ half,  half, -half}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

        // Left face
        {{-half, -half, -half}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-half, -half,  half}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{-half,  half,  half}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-half,  half, -half}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        // Right face
        {{ half, -half,  half}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{ half, -half, -half}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{ half,  half, -half}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{ half,  half,  half}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        // Top face
        {{-half,  half,  half}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ half,  half,  half}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ half,  half, -half}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-half,  half, -half}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

        // Bottom face
        {{-half, -half, -half}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ half, -half, -half}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ half, -half,  half}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-half, -half,  half}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,        // Front
        4, 5, 6, 6, 7, 4,        // Back
        8, 9,10,10,11, 8,        // Left
        12,13,14,14,15,12,       // Right
        16,17,18,18,19,16,       // Top
        20,21,22,22,23,20        // Bottom
    };
    return {vertices, indices};
}

