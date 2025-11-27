#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace  Core {
    Shader::Shader(const char *vertexPath, const char *fragmentPath)
    {
        // 1.retrieve the vertex/fragment source code from filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ensure ifstream objects can throw exceptions:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // read file’s buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // close file handlers
            vShaderFile.close();
            fShaderFile.close();
            // convert stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();

        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ:" << vertexPath << fragmentPath << std::endl << e.what() << std::endl;
            exit(EXIT_FAILURE);
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        std::cout << "DEBUG::SHADER::vertex shader id="<< vertex << " for " << vertexPath << std::endl;
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // print compile errors if any
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << vertexPath << infoLog << std::endl;
        };

        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        std::cout << "DEBUG::SHADER::fragment shader id="<< fragment << " for " << fragmentPath << std::endl;
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        // print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << fragmentPath << infoLog << std::endl;
        };

        ID = glCreateProgram();
        std::cout << "DEBUG::SHADER::program id=" << ID << std::endl;
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        // print linking errors if any
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << vertexPath << "and" << fragmentPath << infoLog << std::endl;
            // If linking failed, set ID to 0 so future glUseProgram checks avoid GL_INVALID_OPERATION
            glDeleteProgram(ID);
            ID = 0;
        }
        else {
            std::cout << "INFO::SHADER::PROGRAM::LINKED ID=" << ID << " (" << vertexPath << ", " << fragmentPath << ")" << std::endl;
        }
        // delete shaders; they’re linked into our program and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }


    void Shader::use()
    {
        if (!ID) {
            std::cerr << "WARNING::SHADER::use() called on invalid shader program (not linked)" << std::endl;
            return;
        }
        glUseProgram(ID);
    }

    void Shader::setFloat(const std::string &name, float value) const
    {
        if (!ID) {
            std::cerr << "WARNING::SHADER::setFloat called on invalid program" << std::endl;
            return;
        }
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void Shader::setBool(const std::string &name, bool value) const
    {
        if (!ID) {
            std::cerr << "WARNING::SHADER::setBool called on invalid program" << std::endl;
            return;
        }
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
    {
        if (!ID) {
            std::cerr << "WARNING::SHADER::setVec3 called on invalid program" << std::endl;
            return;
        }
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
    }

    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        if (!ID) {
            std::cerr << "WARNING::SHADER::setMat4 called on invalid program" << std::endl;
            return;
        }
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Shader::setInt(const std::string &name, int value) const
    {
        if (!ID) {
            std::cerr << "WARNING::SHADER::setInt called on invalid program" << std::endl;
            return;
        }
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
}
