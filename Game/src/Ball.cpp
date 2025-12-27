#include "Ball.h"
#include <glm/gtc/constants.hpp>

#include <glm/gtc/matrix_transform.hpp>


constexpr glm::vec3 AlongX {1.0f, 0.0f, 0.0f };
constexpr glm::vec3 AlongZ {0.0f, 0.0f, -1.0f };

Ball::Ball(float r, glm::vec3 pos) : radius(r), position(pos) {
    auto [vertices, indices] = this->GenerateSphere(radius);
    mesh.SetData(vertices, indices);

    velocity = glm::vec3(1.0f, 1.0f, 1.0f);
    UpdateModelMatrix();
}

void Ball::UpdateModelMatrix() {
    modelMatrix = glm::translate(glm::mat4(1.0f), position);
}
void Ball::OnUpdate(float deltaTime, const std::vector<AABB>& walls) {
    if (position.y > 0.4f)
        position.y -=   9.8f * deltaTime;
    for (auto& wall : walls) {
        glm::vec3 normal;
        float penetration;

        if (collidesWithWall(wall, normal, penetration)) {
            // Push the ball out
            position += normal * penetration;

            // Slide: remove component into wall
            float vn = glm::dot(velocity, normal);
            if (vn < 0)
                velocity -= normal * vn;
        }
    }



    UpdateModelMatrix();
}

void Ball::handleBallMovement(BallMovement movement, float deltaTime) {
    float velocity = ballSpeed * deltaTime ;
    switch (movement) {
        case FORWARD:
            position += AlongZ * velocity;
            break;
        case BACKWARD:
            position -= AlongZ * velocity;
            break;
        case LEFT:
            position -= AlongX * velocity;
            break;
        case RIGHT:
            position += AlongX *  velocity;
            break;
        default :
            break;
    }

}

bool Ball::collidesWithWall(const AABB& wall, glm::vec3& outNormal, float& outPenetration) {

    glm::vec3 closestPoint = glm::clamp(position, wall.min, wall.max);
    glm::vec3 diff = position  - closestPoint;
    float distSq  = glm::dot(diff, diff);
    if (distSq > radius * radius) {
        return false;
    }

    float dist = glm::sqrt(distSq);
    if (dist  > 0.00001f) {
        outNormal = glm::normalize(diff);
        outPenetration = radius - dist;
    }
    else {
        glm::vec3 half = (wall.max - wall.min) * 0.5f;
        glm::vec3 centerWall    = (wall.max + wall.min) * 0.5f;
        glm::vec3 d = position - centerWall;
        glm::vec3 absD = glm::abs(d);

        if (absD.x > absD.y && absD.x > absD.z) {
            outNormal = glm::vec3(d.x > 0 ? 1 : -1, 0, 0);
        }
        else if (absD.y > absD.x && absD.y > absD.z) {
            outNormal = glm::vec3(0, d.y > 0 ? 1 : -1,  0);
        }
        else
            outNormal = glm::vec3(0, 0, d.z > 0 ? 1 : -1);

        outPenetration = radius;
    }
    return true;
}




std::pair<std::vector<Core::Vertex>, std::vector<unsigned int>>
Ball::GenerateSphere(float radius, unsigned int stacks , unsigned int slices)
{
    std::vector<Core::Vertex> vertices;
    std::vector<unsigned int> indices;

    vertices.reserve((stacks + 1) * (slices + 1));
    indices.reserve(stacks * slices * 6);

    for (unsigned int i = 0; i <= stacks; ++i)
    {
        float v = float(i) / stacks;                     // 0 → 1
        float phi = v * glm::pi<float>();                // 0 → PI

        float y = cos(phi);
        float r = sin(phi);                              // radius of current latitude ring

        for (unsigned int j = 0; j <= slices; ++j)
        {
            float u = float(j) / slices;                 // 0 → 1
            float theta = u * glm::two_pi<float>();      // 0 → 2PI

            float x = r * cos(theta);
            float z = r * sin(theta);

            glm::vec3 pos = { x * radius, y * radius, z * radius };
            glm::vec3 normal = glm::normalize(glm::vec3{x, y, z});
            glm::vec2 uv = { u, 1.0f - v };              // flip V so textures aren't upside-down

            vertices.push_back({ pos, normal, uv });
        }
    }

    // Generate indices
    for (unsigned int i = 0; i < stacks; ++i)
    {
        for (unsigned int j = 0; j < slices; ++j)
        {
            unsigned int row1 = i * (slices + 1);
            unsigned int row2 = (i + 1) * (slices + 1);

            unsigned int a = row1 + j;
            unsigned int b = row1 + j + 1;
            unsigned int c = row2 + j;
            unsigned int d = row2 + j + 1;

            // First triangle
            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);

            // Second triangle
            indices.push_back(b);
            indices.push_back(d);
            indices.push_back(c);
        }
    }

    return { vertices, indices };
}




