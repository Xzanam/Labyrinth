//
// Created by Janam Shrestha on 11/29/25.
//

#ifndef BALLCONTROLLER_H
#define BALLCONTROLLER_H


#include <unordered_map>
#include "Event.h"
#include "Core/Camera.h"
#include "Core/Events/KeyBoardEvents.h"
#include "Ball.h"

class BallController {
public:
    explicit BallController(Ball& ball, float moveSpeed = 2.5f);
    void OnEvent(Core::Event& e);
    void OnUpdate(float deltaTime);
    void setBallControl(bool value);
    ~BallController() = default;
private:
    bool OnKeyPressed(Core::KeyPressedEvent& e);
    bool OnKeyReleased(Core::KeyReleasedEvent& e);

    bool ballControlToggled = false;
    Ball& ball;
    float m_moveSpeed;
    std::unordered_map<int, bool> m_Keys;
};





#endif //BALLCONTROLLER_H
