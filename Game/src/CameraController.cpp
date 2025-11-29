#include "CameraController.h"
CameraController::CameraController(Core::Camera &camera, float moveSpeed)
: m_camera(camera), m_moveSpeed(moveSpeed) {}

bool CameraController::OnKeyPressed(Core::KeyPressedEvent& e) {
    m_Keys[e.GetKeyCode()] = true;
    return false;
}


bool CameraController::OnKeyReleased(Core::KeyReleasedEvent& e) {
    m_Keys[e.GetKeyCode()] = false;
    return true; //Don't propagate this event to other layers.
}


bool CameraController::OnMouseMoved(Core::MouseMovedEvent& e) {
    m_camera.handleMouseMovement(e.GetX(), e.GetY());
    return false;
}


void CameraController::OnEvent(Core::Event& e) {
    Core::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<Core::KeyPressedEvent>(
        [this](Core::KeyPressedEvent &e) {
            return OnKeyPressed(e);
        });
    dispatcher.Dispatch<Core::KeyReleasedEvent>(
        [this](Core::KeyReleasedEvent &e) {
            return OnKeyReleased(e);
        });
    dispatcher.Dispatch<Core::MouseMovedEvent>(
        [this](Core::MouseMovedEvent &e) {
            return OnMouseMoved(e);
        });
}

void CameraController::setCamerToggle(bool value) {
    cameraToggled = value;
}


void CameraController::OnUpdate(float deltaTime) {
    if (m_Keys[Core::Keys::KEY_W]) m_camera.handleCameraMovement(Core::CameraMovement::FORWARD, deltaTime);
    if (m_Keys[Core::Keys::KEY_S]) m_camera.handleCameraMovement(Core::CameraMovement::BACKWARD, deltaTime);
    if (m_Keys[Core::Keys::KEY_A]) m_camera.handleCameraMovement(Core::CameraMovement::LEFT, deltaTime);
    if (m_Keys[Core::Keys::KEY_D]) m_camera.handleCameraMovement(Core::CameraMovement::RIGHT, deltaTime);
    if (m_Keys[Core::Keys::KEY_SPACE]) m_camera.handleCameraMovement(Core::CameraMovement::UP, deltaTime);
    if (m_Keys[Core::Keys::KEY_LEFT_SHIFT]) m_camera.handleCameraMovement(Core::CameraMovement::DOWN, deltaTime);

    if (cameraToggled) {
        if(m_Keys[Core::Keys::KEY_UP]) m_VirtualMouseY -=  keyBoardLookUpSpeed * deltaTime * 500.0f;
        if(m_Keys[Core::Keys::KEY_DOWN]) m_VirtualMouseY += keyBoardLookUpSpeed * deltaTime * 500.0f;
        if(m_Keys[Core::Keys::KEY_LEFT]) m_VirtualMouseX -= keyBoardLookUpSpeed * deltaTime * 500.0f;
        if(m_Keys[Core::Keys::KEY_RIGHT]) m_VirtualMouseX += keyBoardLookUpSpeed * deltaTime * 500.0f;

        m_camera.handleMouseMovement(m_VirtualMouseX, m_VirtualMouseY);
    }

}



