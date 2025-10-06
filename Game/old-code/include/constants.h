#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <camera.hpp>
#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<cstring>
#include<vector>
#include <shader.h>

const int W_WIDTH = 1280; 
const int W_HEIGHT = 720; 

// camera
Camera camera(glm::vec3(0.0f, 2.0f, 3.0f));
float lastX = W_WIDTH / 2.0f;
float lastY = W_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame   


#endif