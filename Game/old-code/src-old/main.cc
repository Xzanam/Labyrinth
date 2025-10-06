#include <constants.h>
#include <mesh.h>
#include <models.h>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include <character.h>




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Character* character);
void processCameraMovement(GLFWwindow* window);
void processCharacterMovement(GLFWwindow* window, Character* character);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int loadCubemap(vector<std::string> faces);









int main()
{
    glfwInit(); //initialize glfw

    /*Configuring GLFW for OpenGL version 3.3*/
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //creating a window object
    GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Labyrinth", NULL, NULL); 
    if(window == NULL)
    {
        std::cout <<"error creating glfw window"<<std::endl;
        glfwTerminate(); 
        return -1;  
    }
    glfwMakeContextCurrent(window);
    
    //calling the framebufer_size_callback function everytime the user resizes the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //intializing GLAD before calling any OpenGL functions
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<< "Failed to intialize GLAD"<<std::endl;  
        return -1;  
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
   //stbi_set_flip_vertically_on_load(true);
 float vertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,    
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER,skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW);
   
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


  



  

    Shader lightShader("./shaders/light.vs", "./shaders/light.fs");


    Shader thisShader("./shaders/shader.vs", "./shaders/shader.fs");

    Shader ballShader("./shaders/ball.vs", "./shaders/ball.fs");
    Shader skyboxShader("./shaders/skybox.vs", "./shaders/skybox.fs");

    //skybox
    vector<std::string> faces
    {
        "../img/right.jpg",
        "../img/left.jpg",
        "../img/top.jpg",
        "../img/bottom.jpg",
        "../img/front.jpg",
        "../img/back.jpg"
    };
    unsigned int cubemapTexture = loadCubemap(faces);

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);


  

    
 

    Model map("../models/map/map.obj");
    Model lightsource("../models/container/container.obj");
    Character ball("../models/ball/ball1.obj");


    glm::vec3 LIGHTCOLOR(1.0f); 
    glm::vec3 LIGHTPOS(3.0f,3.0f,3.0f);
  



    thisShader.use();
    thisShader.setVec3("objectcolor", 1.0f, 0.5f, 0.31f);
    thisShader.setVec3("lightcolor", LIGHTCOLOR);
    
    //for light 
   
    thisShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    thisShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    thisShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darkened


   
    thisShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    thisShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    thisShader.setInt("material.diffuse", 0);
    thisShader.setVec3("material.specular", 0.2f, 0.2f, 0.2f); 
    thisShader.setFloat("material.shininess", 16.0f);

    ballShader = thisShader;
    lightShader.use(); 
    lightShader.setVec3("lightcolor", LIGHTCOLOR);

  
  bool flag = 1; 


    float angle; 
    
    //THE RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window, &ball); 
        //check for key presses or basically input

        

     
    

        //rendering commands here
        glClearColor(0.0f, 0.4f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)W_WIDTH / (float)W_HEIGHT, 0.1f, 100.0f);

        glm::mat4 view = camera.GetViewMatrix();

    


        
        // view = camera.GetViewMatrix();
        // int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


              // view/projection transformations
    
   


        glm::vec3 diffuseColor = LIGHTCOLOR * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 
    
       
               
       
        thisShader.use();
        thisShader.setVec3("lightPos", LIGHTPOS);      
        thisShader.setVec3("viewPos", camera.Position);
     

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        thisShader.setMat4("model", model);
        thisShader.setMat4("view", view);
        thisShader.setMat4("projection", projection);
        //draw container
        map.Draw(thisShader);

       
        
 


        ballShader.use(); 
        ballShader.setVec3("lightPos", LIGHTPOS);
        ballShader.setVec3("viewPos", camera.Position);
        glm::mat4 model_ball = glm::mat4(1.0f);
        model_ball = glm::translate(model_ball, ball.Position);
        model_ball = glm::scale(model_ball, glm::vec3(0.3f, 0.3f, 0.3f));
        model_ball = glm::rotate(model_ball,ball.rotCounter * glm::radians(ball.rotAngle), ball.rotAxis);
        ballShader.setMat4("model", model_ball); 
        ballShader.setMat4("view", view);
        ballShader.setMat4("projection", projection);
        ball.drawCharacter(ballShader);

        //modelmatrix for light source
        lightShader.use();
        glm::mat4 model_light = glm::mat4(1.0f);
        model_light = glm::translate(model_light,  LIGHTPOS);
        model_light = glm::scale(model_light, glm::vec3(0.1f, 0.1f, 0.1f));
        lightShader.setMat4("model_light", model_light);
        lightShader.setMat4("view", view);
        lightShader.setMat4("projection", projection);
        
        //lightsource.Draw(lightShader);
        // lightShader.use();
        // lightsource.Draw(thisShader);

        camera.ballPos = ball.Position;
        //detectCollision(&ball, &map,model);

                // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default


    
        ball.collisionDetection(&map, &camera.Position);

 
        
        //mouse movement 
       // glfwSetCursorPosCallback(window, mouse_callback);

       if(ball.reachedFinish())
       {
            std::cout<<"congatulations! You've solved the maze"<<std::endl;
            break;

       }
      


        //check and call events and swap the buffers    
        glfwSwapBuffers(window); //swapping the front and back buffers
        glfwPollEvents();   
    }
    

    // //freeing the resourcesx
    // glDeleteVertexArrays(1, &VAO); 
    // glDeleteBuffers(1, &VBO);

    glfwTerminate();  //clear them all mess and free the resources
    
    return 0; 
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);

}
void processInput(GLFWwindow* window, Character* character){
   processCameraMovement(window);
   processCharacterMovement(window, character);
}

void processCameraMovement(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_SPACE ) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        camera.thirdCamera(TPP, deltaTime, 1);
    // else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE)
    //     camera.thirdCamera(TPP, deltaTime,0);

}
void processCharacterMovement(GLFWwindow* window, Character* character)
{
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        character->characterMovement(C_FORWARD, deltaTime);
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        character->characterMovement(C_BACKWARD, deltaTime);
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
       {
        character->characterMovement(C_RIGHT, deltaTime);
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
        character->characterMovement(C_LEFT, deltaTime);
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
      if(glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS)
    {
        character->characterMovement(C_UP, deltaTime);
        camera.ProcessKeyboard(UP, deltaTime);
    }
      if(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
    {
        character->characterMovement(C_DOWN, deltaTime);
        camera.ProcessKeyboard(DOWN, deltaTime);
    }

}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{


    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse) // initially set to true
    {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
    }   

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed: y ranges bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height,
        &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
        width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Cubemap failed to load at path: " << faces[i]
        << std::endl;
        stbi_image_free(data);
    }
    }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,
        GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,
        GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,
        GL_CLAMP_TO_EDGE);
    return textureID;
}