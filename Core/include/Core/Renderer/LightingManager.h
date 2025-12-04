//
// Created by Janam Shrestha on 11/29/25.
//

#ifndef LIGHTINGMANAGER_H
#define LIGHTINGMANAGER_H


#include <glm/glm.hpp>

#include "Shader.h"

struct DirectionalLight {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};



namespace Core {
    class LightingManager {
    private:
        DirectionalLight sun;

    public:
        LightingManager();
        void UploadToShader(Shader& shader);
    };
}



#endif //LIGHTINGMANAGER_H
