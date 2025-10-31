
#include "Mesh.h"
#include "glad/gl.h"

#include <iostream>


namespace Core {
    Mesh:: Mesh() : m_VAO(0), m_VBO(0), m_EBO(0) {
        InitGLResources();
    }


    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
        : m_VAO(0), m_VBO(0), m_EBO(0), m_Vertices(std::move(vertices)), m_Indices(std::move(indices)){
        InitGLResources();
        SetupMesh();
    }

    void Mesh::InitGLResources() {
        glCreateVertexArrays(1, &m_VAO);
        glCreateBuffers(1, &m_VBO);
        glCreateBuffers(1, &m_EBO);
    }


    void Mesh::SetData(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
        m_Vertices = std::move(vertices);
        m_Indices = std::move(indices);
        SetupMesh();
    }

    void Mesh::SetupMesh() {
        glNamedBufferData(m_VBO, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);
        glNamedBufferData(m_EBO, m_Indices.size() * sizeof(unsigned int), m_Indices.data(), GL_STATIC_DRAW);

        glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(Vertex));
        glVertexArrayElementBuffer(m_VAO, m_EBO);


        glEnableVertexArrayAttrib(m_VAO, 0);
        glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Position));
        glVertexArrayAttribBinding(m_VAO, 0, 0);

        glEnableVertexArrayAttrib(m_VAO, 1);
        glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Normal));
        glVertexArrayAttribBinding(m_VAO, 1, 0);

        glEnableVertexArrayAttrib(m_VAO, 2);
        glVertexArrayAttribFormat(m_VAO, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex,TexCoords));
        glVertexArrayAttribBinding(m_VAO, 2, 0);

        std::cout<<"AllGood! " <<std::endl;
    }


    void Mesh::Draw() const {
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, nullptr);
    }

    size_t Mesh::GetVertexSize() const {
        return m_Vertices.size();
    }

    void Mesh::PushVertex(const Vertex& vertex) {
        m_Vertices.push_back(vertex);
    }

    void Mesh::PushVertices(const std::vector<Vertex> &vertices) {
       m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());
    }

    void Mesh::PushIndices(const std::vector<unsigned int> &indices) {
        m_Indices.insert(m_Indices.end(), indices.begin(), indices.end());
    }

    void Mesh::PushIndex(unsigned int index) {
       m_Indices.push_back(index);
    }




}
