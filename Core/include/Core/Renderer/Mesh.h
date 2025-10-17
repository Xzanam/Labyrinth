//
// Created by Janam Shrestha on 10/8/25.
//

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
namespace Core {
    struct Vertex {
        glm::vec3 Position ;
        glm::vec3 Normal ;
        glm::vec2 TexCoords;
    public:
        Vertex() = default;
        explicit Vertex(const glm::vec3& pos) : Position(pos) ,  Normal(glm::vec3(0.0f, 0.0f, 0.0f)) , TexCoords( { 0.0f, 0.0f }) {}
        Vertex(const glm::vec3& pos, const glm::vec3& norm, const glm::vec2& tex) : Position(pos), Normal(norm), TexCoords(tex) {} ;
    };

    class Mesh {
    private:
        unsigned int m_VAO, m_VBO, m_EBO;
        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indices;

        void SetupMesh();

        void InitGLResources();

    public:

        Mesh()  ;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

        void SetData(std::vector<Vertex> vertices, std::vector<unsigned int> indices) ;
        void Draw() const;
    };

}

#endif //MESH_H
