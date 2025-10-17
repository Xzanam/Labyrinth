#include "GameLayer.h"

#include "Events/KeyBoardEvents.h"
#include "glad/gl.h"
#include <iostream>

#include "Core/Application.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Camera.h"

#include <glm/matrix.hpp>


#include "Cube.h"

using Vertex = Core::Vertex;

GameLayer::GameLayer() {
    std::vector<Vertex> vertices = {
        Vertex({0.0f, 0.5f, 0.0f}),
        Vertex({1.0f, 0.0f, 0.0f}),
        Vertex({-1.0f, 0.0f, 0.0f}),
    };

    mesh = std::make_unique<Core::Mesh>(vertices, std::vector<unsigned int>{0,1,2});
    triangleShader = std::make_unique<Core::Shader>("shaders/vertex.glsl", "shaders/fragment.glsl");

    camera = std::make_unique<Core::Camera>();
    cube = std::make_unique<Cube>();


    float height = 720.0f;
    float width = 1280.0f;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), width/height, 0.1f, 100.0f );
    camera->setProjectionMatrix(projection);

}

GameLayer::~GameLayer() {
}
void GameLayer::OnRender() {
    glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    triangleShader->use();
    triangleShader->setMat4("projection", camera->getProjectionMatrix());
    triangleShader->setMat4("view", camera->getViewMatrix());
    cube->OnRender(*triangleShader);;
}


void GameLayer::OnUpdate(float deltaTime) {
}


void GameLayer::OnEvent(Core::Event& event) {
    Core::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Core::KeyPressedEvent>([this](Core::KeyPressedEvent &e) {
        // std::cout << "Key Pressed : "  << e.GetKeyCode() << std::endl;
            switch (e.GetKeyCode()) {
                case Core::Keys::KEY_ESCAPE  : {
                    Core::Application::Get().Stop();
                }
            }
        return true;
    });

    dispatcher.Dispatch<Core::MouseMovedEvent>([this](Core::MouseMovedEvent &e) {
        printf("Mouse Moved : %f , %f\n", e.GetX(), e.GetY());
        camera->handleMouseMovement(e.GetX(),e.GetY());
        return true;
    });
}
