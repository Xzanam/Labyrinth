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
    void collisionDetection(Model *scene)
    {
    // bool insidePlane; 
    // bool insideAnyVerts;
    // bool insideAnyEdges; 
    // bool inside;    

    // inside = (insidePlane && (insideAnyVerts || insideAnyEdges));    
    glm::vec3 collSphereOrigin = Position;  
    const float collSphereRadius = 1.0f;
    const float collSphereRadius2 = collSphereRadius * collSphereRadius;
    
    //  auto verts1 = &scene->meshes[1].vertices[0].Position;
    // std::cout<<verts1->x<<verts1->y<<verts1->z<<std::endl;
     

    for(auto &sceneobject : scene->meshes)
    {
    const auto &mesh = scene->meshes; 
    auto verts = &scene->meshes[i].vertices[i].Position;
    auto norms = scene->meshes[i].vertices[i].Normal;
    auto triangleInds = mesh.indices;   
    int numTris = triangleInds.size() / 3;  
    for(int i = 0;i <numTris; i++)
    {
       
        bool outsidePlane = false; 
        bool outsideAllVerts = false; 
        bool outsideAllEdges = false; 
        glm::vec3* v1 = verts; 
        glm::vec3* v2 = verts + 1; 
        glm::vec3* v3 = verts + 2; 
        // std::cout<<v1->x<<v1->y<<v1->z<<std::endl;
        // std::cout<<v2->x<<v2->y<<v2->z<<std::endl;

        glm::vec4 temp = glm::vec4(glm::normalize(norms), 0.0f);
        glm::vec3 pN = glm::vec3(temp.x, temp.y, temp.z);

        if(fabs(pN.y)>0.1f)
        {
            
            continue;
            
        }
        std::cout<<"hi";
        float d = glm::dot(-(*v1 + *v2 + *v3) /3.0f, pN);

        float ppd = glm::dot(pN, collSphereOrigin) + d;
        if(ppd > collSphereRadius)
            {
                
                outsidePlane = true; 
                continue;
            }

        bool outsidev1 = (glm::length(*v1 - collSphereOrigin) > collSphereRadius2);
        bool outsidev2 = (glm::length(*v2 - collSphereOrigin) > collSphereRadius2);
        bool outsidev3 =   glm::length(*v3 - collSphereOrigin) > collSphereRadius2;

        if(outsidev1 && outsidev2 && outsidev3)
        {
            outsideAllVerts = true; 
        }



    }

    }
    
    }
};




#endif