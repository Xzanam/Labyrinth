//
// Created by Janam Shrestha on 11/29/25.
//

#include "LightingManager.h"


namespace Core {
    struct SunLight {
        inline static const glm::vec3 Afternoon = glm::normalize(glm::vec3(-0.3f, -1.0f, -0.2f));
        inline static const glm::vec3 Midday = glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f));
        inline static const glm::vec3 Sunset = glm::normalize(glm::vec3(-1.0f, -0.4f, 0.2f));
    };

    LightingManager::LightingManager() : sun( SunLight::Sunset,
                                             glm::vec3(0.2f),glm::vec3(0.6f), glm::vec3(1.0f)) {
    }

    void LightingManager::UploadToShader(Shader &shader) {
        shader.use();
        shader.setVec3("dirLight.direction", sun.direction);
        shader.setVec3("dirLight.ambient", sun.ambient);
        shader.setVec3("dirLight.diffuse", sun.diffuse);
        shader.setVec3("dirLight.specular", sun.specular);
    }
}
