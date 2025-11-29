#ifndef BALL_H
#define BALL_H


#include "Object.h"
#include "CollisionElements.h"


enum BallMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

class Ball : public Game::Object { 
private:
    float radius;
    glm::vec3 position;
    glm::vec3 velocity;
    float ballSpeed = 5.0f;
public :
    Ball() = default;
    Ball(float r, glm::vec3 pos);

    void UpdateModelMatrix();
    inline std::pair<std::vector<Core::Vertex>, std::vector<unsigned int>> 
    GenerateSphere(float radius,unsigned int stacks= 32,unsigned int slices = 32);

    bool collidesWithWall(const AABB& wall, glm::vec3& outNormal, float& outPenetration);

    void OnUpdate(float deltaTime, const std::vector<AABB>& walls);

    void handleBallMovement(BallMovement movement, float deltaTime);


};
#endif //BALL_H 