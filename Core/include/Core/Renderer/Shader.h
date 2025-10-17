//
// Created by Janam Shrestha on 10/2/25.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glm/glm.hpp>


namespace Core {
    class Shader
    {
    public:
        unsigned int ID;
        Shader(const char *vertexPath, const char *fragmentPath);
        // Shader(const char *vertexPath, const char *includePath, const char *fragmentPath);

        void use();

        void setBool(const std::string &name, bool value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
        void setInt(const std::string &name, int value) const;
    };
}


#endif //SHADER_H
