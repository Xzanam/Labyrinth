#include "GameLayer.h"

#include "Events/KeyPressedEvent.h"
#include "glad/gl.h"
#include <iostream>


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
}
