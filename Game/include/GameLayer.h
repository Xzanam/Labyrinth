#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "Layer.h"
#include "Mesh.h"
#include "Shader.h"
#include <memory>


#include "CameraController.h"
#include "Cube.h"
#include "Core/Camera.h"



class GameLayer  : public Core::Layer{
public:
    GameLayer();

    ~GameLayer() override;


    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnEvent(Core::Event& event) override;

private:
    std::unique_ptr<Core::Shader> triangleShader;
    std::unique_ptr<Core::Mesh> mesh;
    std::unique_ptr<Core::Camera> camera;
    std::unique_ptr<CameraController> camController;
    std::unique_ptr<Cube> cube;
};



#endif //GAMELAYER_H
