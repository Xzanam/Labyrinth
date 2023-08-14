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
        glm::vec3 Up;
        glm::vec3 Right;
        float MovementSpeed;
        Character(std::string filepath){
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

        }
};




#endif