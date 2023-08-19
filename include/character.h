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
        glm::vec3 rotAxis;
        float MovementSpeed;
        float rotAngle, rotCounter;
        Character(std::string filepath){
            Position = glm::vec3(0.0f, 0.2f, 0.0f);
            Front = glm::vec3(0.0f, .0f, -1.0f);
            Right = glm::vec3(1.0f, 0.0f, 0.0f);
            MovementSpeed = 2.5f;
            rotAngle = 20.0f;
            rotCounter = 0.0f;
            rotAxis = glm::vec3(1.0f, 0.0f, 1.0f);
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
                rotCounter += 0.4;

                if(direction == C_FORWARD)
                {       
                    rotAxis = glm::vec3(1.0f,0.0f,0.0f);
                    Position += Front * velocity;
                    
                    rotAngle = -abs(rotAngle);
                }


                   
                if(direction == C_BACKWARD)
                {
                    rotAxis = glm::vec3(1.0f,0.0f,0.0f);
                    Position -= Front * velocity; 
                    
                    rotAngle = abs(rotAngle);
                }
            
                if(direction == C_RIGHT)
                {
                    rotAxis = glm::vec3(0.0f,0.0f,1.0f);
                     rotAngle = -abs(rotAngle);
                    Position += Right * velocity; 
                }
                if(direction == C_LEFT){
                    rotAxis = glm::vec3(0.0f,0.0f,1.0f);
                    Position -= Right * velocity;
                      rotAngle = abs(rotAngle);
                }       

        }
};




#endif