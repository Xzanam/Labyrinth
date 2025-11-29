#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "Layer.h"
#include "Shader.h"
#include <memory>


#include "BallController.h"
#include "CameraController.h"
#include "Core/Camera.h"
#include "Scene.h"




class GameLayer  : public Core::Layer{
public:
    GameLayer();

    ~GameLayer() override;


    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnEvent(Core::Event& event) override;

private:
    std::unique_ptr<Core::Shader> gameShader;
    std::unique_ptr<Core::Camera> camera;
    std::unique_ptr<CameraController> camController;
    std::unique_ptr<Scene>  gameScene;

    bool moveCamera = true;
};



#endif //GAMELAYER_H
