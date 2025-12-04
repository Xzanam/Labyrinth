#ifndef SCENE_H
#define SCENE_H


#include <memory>

#include "Maze.h"
#include "Cube.h"
#include "Ball.h"
#include "BallController.h"
#include "Core/Renderer/Shader.h"
#include "Core/Renderer/LightingManager.h"


class Scene { 
public:
    Scene(Core::Camera& camera);
    ~Scene() = default;
    void OnRender(Core::Shader& shader) const;
    void OnUpdate(float deltaTime);
    void OnEvent(Core::Event& event);

    void setBallControlToggle(bool value);

private: 
    std::unique_ptr<Maze> maze;
    std::unique_ptr<Ball> ball;
    std::unique_ptr<BallController> ballController;
    std::unique_ptr<Core::LightingManager> lightingManager;

    Core::Camera* camera;

};

#endif //SCENE_H
