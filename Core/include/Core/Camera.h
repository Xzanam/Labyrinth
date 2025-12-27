#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glad/gl.h"

namespace Core {
    enum CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    // Default camera values

    class Camera {
    protected:
        glm::vec3 _position;
        glm::vec3 _front;
        glm::vec3 _up;
        glm::mat4 _lookAt;


        glm::vec3 _right;
        glm::vec3 _worldUp;

        float _yaw, _pitch;



        float lastX;
        float lastY;
        bool firstMouse;


        float _cameraSpeed = 2.5f;

        glm::mat4 projectionMatrix;

        virtual void updateCameraVectors() ;

    public:


        explicit Camera(glm::vec3 position= glm::vec3(0.0f, 0.0f, 3.0f),
               glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
               float yaw = -90.0f,
               float pitch = 0.0f) ;

        void setProjectionMatrix(glm::mat4 projection) ;

        virtual glm::mat4 getViewMatrix() const ;
        glm::mat4 getProjectionMatrix() const;

        void handleCameraMovement(CameraMovement direction, float deltaTime);
        virtual void handleMouseMovement(float xOffset, float yOffset, GLboolean constraintPitch = true);

        void setPosition(const glm::vec3& position) ;
        void printPosition();

        const glm::vec3&  getPosition() const {
            return _position;
        };


        virtual ~Camera() = default;

    };
}

#endif // CAMERA_H