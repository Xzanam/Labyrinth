//
// Created by Janam Shrestha on 11/29/25.
//

#include "BallController.h"


BallController::BallController(Ball& ball, float moveSpeed)
: ball(ball), m_moveSpeed(moveSpeed) {}

bool BallController::OnKeyPressed(Core::KeyPressedEvent& e) {
    m_Keys[e.GetKeyCode()] = true;
    return false;
}


void BallController::setBallControl(bool value) {
    ballControlToggled = value;
}



bool BallController::OnKeyReleased(Core::KeyReleasedEvent& e) {
    m_Keys[e.GetKeyCode()] = false;
    return true; //Don't propagate this event to other layers.
}



void BallController::OnEvent(Core::Event& e) {
    Core::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<Core::KeyPressedEvent>(
        [this](Core::KeyPressedEvent &e) {
            return OnKeyPressed(e);
        });
    dispatcher.Dispatch<Core::KeyReleasedEvent>(
        [this](Core::KeyReleasedEvent &e) {
            return OnKeyReleased(e);
        });
}


void BallController::OnUpdate(float deltaTime) {
    if (ballControlToggled) {
        if (m_Keys[Core::Keys::KEY_UP]) ball.handleBallMovement(BallMovement::FORWARD, deltaTime);
        if (m_Keys[Core::Keys::KEY_DOWN]) ball.handleBallMovement(BallMovement::BACKWARD, deltaTime);
        if (m_Keys[Core::Keys::KEY_LEFT]) ball.handleBallMovement(BallMovement::LEFT, deltaTime);
        if (m_Keys[Core::Keys::KEY_RIGHT]) ball.handleBallMovement(BallMovement::RIGHT, deltaTime);
    }
}






