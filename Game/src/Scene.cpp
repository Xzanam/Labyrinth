#include "Scene.h"


constexpr float BALLRADIUS = 0.2f;

Scene::Scene() {
    maze = std::make_unique<Maze>();
    ball = std::make_unique<Ball>(BALLRADIUS, glm::vec3(0.0f, 10.0f, 0.0f));
    ballController = std::make_unique<BallController>(*ball);

    ball->setColor(Colors::Red);

    maze->PrintMaze();
}

void Scene::OnRender(Core::Shader &shader) const {
    maze->OnRender(shader);
    ball->OnRender(shader);
}

void Scene::OnEvent(Core::Event &event) {
    ballController->OnEvent(event);
}


void Scene::OnUpdate(float deltaTime) {
    ball->OnUpdate(deltaTime, maze->GetWallAABBs());
    ballController->OnUpdate(deltaTime);
}


void Scene::setBallControlToggle(bool value) {
    ballController->setBallControl(value);
}
