#include "GameLayer.h"
#include "glad/gl.h"


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

}
