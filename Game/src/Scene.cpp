#include "Scene.h"


constexpr float BALLRADIUS = 0.2f;

Scene::Scene(Core::Camera& camera) {
    maze = std::make_unique<Maze>(30, 30);
    ball = std::make_unique<Ball>(BALLRADIUS, glm::vec3(0.0f, 10.0f, 0.0f));
    ballController = std::make_unique<BallController>(*ball);
    lightingManager = std::make_unique<Core::LightingManager>();

    this->camera = &camera;

    ball->setColor(Colors::Red);

    maze->PrintMaze();
}

void Scene::OnRender(Core::Shader &shader) const {

    shader.use();
    shader.setVec3("viewPos", camera->getPosition());

    lightingManager->UploadToShader(shader);
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
