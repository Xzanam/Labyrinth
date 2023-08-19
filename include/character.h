#ifndef CHARACTER_H
#define CHARACTER_H

#include <models.h>
enum Character_Movement {
    C_FORWARD,
    C_BACKWARD,
    C_LEFT,
    C_RIGHT, 
    C_UP, 
    C_DOWN,
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
        float lastWalkSpeed;
        Character(std::string filepath){
            Position = glm::vec3(0.0f, 0.2f, 0.0f);
            Front = glm::vec3(0.0f, 0.0f, -1.0f);
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
                lastWalkSpeed = velocity;
                rotCounter += 0.4;

                if(direction == C_FORWARD)
                {       
                    rotAxis = glm::vec3(1.0f,0.0f,0.0f);
                    Position += Front * velocity;
                    
                    rotAngle = -abs(rotAngle);
                }
                if(direction == C_UP)
                {
                    Position += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
                }
                if(direction == C_DOWN)
                {
                    Position -= glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
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
                Position.y = 0.2f;

        }

    static bool intersectRaySegmentSphere(glm::vec3 o ,glm::vec3 d, glm::vec3 so, float radius2, glm::vec3 &ip)
    {
                    //we pass in d non-normalized to keep it's length
        //then we use that length later to compare the intersection point to make sure
        //we're within the actual ray segment
        float l = glm::length(d);
        d /= l;

        glm::vec3 m = o - so;
        float b = glm::dot(m, d);
        float c = glm::dot(m, m) - radius2;
        
        // Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
        if(c > 0.0f && b > 0.0f)
            return false;
        float discr = b*b - c;
        
        // A negative discriminant corresponds to ray missing sphere
        if(discr < 0.0f)
            return false;
        
        // Ray now found to intersect sphere, compute smallest t value of intersection
        float t = -b - sqrtf(discr);
        
        // If t is negative, ray started inside sphere so clamp t to zero
        if(t < 0.0f)
            t = 0.0f;
        ip = o + (d * t);
        
        //here's that last segment check I was talking about
        if(t > l)
            return false;
        
        return true;
    }
    void collisionDetection(Model *scene, glm::vec3 * cameraPos)
    {
    // bool insidePlane; 
    // bool insideAnyVerts;
    // bool insideAnyEdges; 
    // bool inside;    

    // inside = (insidePlane && (insideAnyVerts || insideAnyEdges));    
    glm::vec3 collSphereOrigin = Position;  
    const float collSphereRadius = 0.2f;
    const float collSphereRadius2 = collSphereRadius * collSphereRadius;

        glm::vec3 shiftDelta  = glm::vec3(0.0f);
      int numCollision = 0;
    
    //  auto verts1 = &scene->meshes[1].vertices[0].Position;
    // std::cout<<verts1->x<<verts1->y<<verts1->z<<std::endl;
     

    for(auto &sceneobject : scene->meshes)
    {
    const auto &mesh = scene->meshes; 
    auto verts = sceneobject.position;
    auto norms = sceneobject.normals; 
    auto triangleInds = sceneobject.indices;   
    int numTris = triangleInds.size() / 3;  

    glm::uvec3 *triData =   (glm::uvec3*)triangleInds.data();//this could be danger zone
    glm::vec3 *vertsData = (glm::vec3*)verts.data(); 
    glm::vec3 *normsData = (glm::vec3*)norms.data();
    for(int i = 0;i <numTris; i++)
    {
       
        bool outsidePlane = false; 
        bool outsideAllVerts = false; 
        bool outsideAllEdges = false; 
        glm::vec3 v1 = vertsData[triData[i].x];
        glm::vec3 v2 = vertsData[triData[i].y];
        glm::vec3 v3 = vertsData[triData[i].z];     
        // std::cout<<v1->x<<v1->y<<v1->z<<std::endl;
        // std::cout<<v2->x<<v2->y<<v2->z<<std::endl;

        glm::vec4 temp = glm::vec4(glm::normalize(normsData[triData[i].x]), 0.0f);
        glm::vec3 pN = glm::vec3(temp.x, temp.y, temp.z);
      
  

        if(abs(pN.y)>0.1f)
        {
            continue;   
        }
       
        float d = glm::dot(-(v1 + v2 + v3) /3.0f, pN);//try changing - ko position

        float ppd = glm::dot(pN, collSphereOrigin) + d;
        if(ppd > collSphereRadius)
            {
                
                outsidePlane = true; 
                continue;
            }

        bool outsidev1 = (glm::pow(glm::length(v1 - collSphereOrigin), 2) > collSphereRadius2);
        bool outsidev2 = (glm::pow(glm::length(v2 - collSphereOrigin), 2) > collSphereRadius2);
        bool outsidev3 =  (glm::pow(glm::length(v3 - collSphereOrigin),2) > collSphereRadius2);

        if(outsidev1 && outsidev2 && outsidev3)
        {
            outsideAllVerts = true; 
        }
        
        glm::vec3 a = v2 - v1; 
        glm::vec3 b = v3 - v2; 
        glm::vec3 c = v1 - v3; 
        
        glm::vec3 ip;

        if(!intersectRaySegmentSphere(v1, a, collSphereOrigin, collSphereRadius2, ip) &&
            !intersectRaySegmentSphere(v2, b, collSphereOrigin, collSphereRadius2, ip) &&
            !intersectRaySegmentSphere(v3, c, collSphereOrigin, collSphereRadius2, ip))
            {
                outsideAllEdges = true; 
            }
        
        if(outsideAllVerts &&outsideAllEdges)
        {
           // std::cout<<"NoCollisionDetected"<<std::endl;
            continue;
        }
        //std::cout<<"Collisiosn Detected"<<std::endl;

        shiftDelta += pN * (collSphereRadius - ppd);
        numCollision++; 

        if(numCollision != 0)
        {
            shiftDelta /= (float)numCollision;
            if(glm::length(shiftDelta) > lastWalkSpeed)
            {
                shiftDelta   = glm::normalize(shiftDelta);
                shiftDelta  *= lastWalkSpeed * 0.1f;
            }
            Position = Position + shiftDelta;
            *cameraPos = *cameraPos + shiftDelta;


        }

      




    }

    }
    
    }
};




#endif