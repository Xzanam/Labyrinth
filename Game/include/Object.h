#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include "Core/Renderer/Shader.h"
#include "Colors.h"

#include "Renderer/Mesh.h"

namespace Game
{
    class Object
    {
    protected:
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glm::vec3 color =  Colors::Gray;
        Core::Mesh mesh;


    public:
        Object() = default ;
        Object(const glm::mat4 &matrix, const glm::vec3 &col) : modelMatrix(matrix), color(col) {}  

        virtual void OnRender(Core::Shader &shader) const  { 
            shader.use();
            shader.setMat4("model", modelMatrix);
            shader.setVec3("objectColor", color);
            mesh.Draw(); // Danger!!! needs mesh initialized in the derived class contructor
        }

        virtual void OnUpdate(float deltaTime) {
        };
        virtual ~Object() = default;

        void setModelMatrix(const glm::mat4 &matrix)
        {
            modelMatrix = matrix;
        }
        void setColor(const glm::vec3 &col)
        {
            color = col;
        }

        const glm::mat4 &getModelMatrix() const
        {
            return modelMatrix;
        }
        const glm::vec3 &getColor() const
        {
            return color;
        }
    };
}

#endif // OBJECT_H