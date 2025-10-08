#include "GameLayer.h"

#include "Events/KeyBoardEvents.h"
#include "glad/gl.h"
#include <iostream>

#include "MouseEvents.h"


GameLayer::GameLayer() {
}

GameLayer::~GameLayer() {
}
void GameLayer::OnRender() {
    glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
}


void GameLayer::OnUpdate(float deltaTime) {

}


void GameLayer::OnEvent(Core::Event& event) {
    Core::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Core::KeyPressedEvent>([this](Core::KeyPressedEvent &e) {
        // std::cout << "Key Pressed : "  << e.GetKeyCode() << std::endl;
            printf("Key Pressed : %c \n" , e.GetKeyCode());
        return true;
    });

    dispatcher.Dispatch<Core::MouseMovedEvent>([this](Core::MouseMovedEvent &e) {
        printf("Mouse Moved : %f , %f\n", e.GetX(), e.GetY());
        return true;
    });
}
