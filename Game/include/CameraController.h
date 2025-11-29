//
// Created by Janam Shrestha on 10/18/25.
//

#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H


#include <unordered_map>

#include "Event.h"
#include "MouseEvents.h"
#include "Core/Camera.h"
#include "Core/Events/KeyBoardEvents.h"

class CameraController {
public:
    explicit CameraController(Core::Camera& camera, float moveSpeed = 2.5f);
    void OnEvent(Core::Event& e);
    void OnUpdate(float deltaTime);
    void setCamerToggle(bool value) ;
    ~CameraController() = default;
private:
    bool OnKeyPressed(Core::KeyPressedEvent& e);
    bool OnKeyReleased(Core::KeyReleasedEvent& e);
    bool OnMouseMoved(Core::MouseMovedEvent& e);


    bool cameraToggled = true;
    Core::Camera& m_camera;
    float m_moveSpeed;
    std::unordered_map<int, bool> m_Keys;
    float m_VirtualMouseX = 400.0f;
    float m_VirtualMouseY = 300.0f;
    float keyBoardLookUpSpeed = 3.0f;
};



#endif //CAMERACONTROLLER_H
