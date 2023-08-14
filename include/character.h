#ifndef CHARACTER_H
#define CHARACTER_H

#include <models.h>
enum Character_Movement {
    C_FORWARD,
    C_BACKWARD,
    C_LEFT,
    C_RIGHT, 
};


class Character{
   
    std::string path;
    Model* characterObj;

   
    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Right;
        float MovementSpeed;
        Character(std::string filepath){
            Position = glm::vec3(0.0f, 2.0f, 0.0f);
            Front = glm::vec3(0.0f, 0.0f, -1.0f);
            Right = glm::vec3(1.0f, 0.0f, 0.0f);
            MovementSpeed = 2.5f;
            path = filepath;
            loadCharacter();
        }
        void loadCharacter()
        {
            characterObj = new Model(path);
        }
        void drawCharacter(Shader &shader)
        {
            characterObj->Draw(shader);
           
        }
        void characterMovement(Character_Movement direction, float deltaTime){
                float velocity = MovementSpeed * deltaTime;
                if(direction == C_FORWARD)
                    Position += Front * velocity;
                if(direction == C_BACKWARD)
                    Position -= Front * velocity; 
                if(direction == C_RIGHT)
                    Position += Right * velocity; 
                if(direction == C_LEFT)
                    Position -= Right * velocity;

        }
};




#endif