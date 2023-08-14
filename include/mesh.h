#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> 
#include<vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <shader.h>

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal; 
    glm::vec2 TexCoords; 
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};
struct Texture{ 
    unsigned int id; 
    std::string type; 
    std::string path; 

};
class Mesh{
    public:
        std::vector<Vertex> vertices; 
        std::vector<unsigned int> indices; 
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures); 
        void draw(Shader &shader);

    private: 
        unsigned int VAO, VBO, EBO; 
        void setupMesh(); 


};



#endif