
#include <game.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);

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

void processInput(GLFWwindow* window){
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


int Game::intialize(){

    //creating a window object
    window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Lighting", NULL, NULL); 
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
    stbi_set_flip_vertically_on_load(true);


    lightShader = new Shader("./shaders/light.vs", "./shaders/light.fs");
    thisShader = new Shader("./shaders/shader.vs", "./shaders/shader.fs");
    ballShader = new Shader("./shaders/ball.vs", "./shaders/ball.fs");

    

    map = new Model("../models/maze1/maze1.obj");
    lightSource = new Model("../models/moon/scene.gltf");    
    ball = new Character("../models/ball/ball.obj");


   

    thisShader->use();
    thisShader->setVec3("objectcolor", 1.0f, 0.5f, 0.31f);
    thisShader->setVec3("lightcolor", LIGHTCOLOR);
    
    //for light 
   
    thisShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    thisShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    thisShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darkened


   
    thisShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    thisShader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    thisShader->setInt("material.diffuse", 0);
    thisShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f); 
    thisShader->setFloat("material.shininess", 32.0f);


    lightShader->use(); 
    lightShader->setVec3("lightcolor", LIGHTCOLOR);
    return 0;
}

void Game::update(){

}


void Game::render(){

    
 
        
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //check for key presses or basically input
        processInput(window); 

        //rendering commands here
        glClearColor(0.0f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::vec3 LIGHTPOS(5 * (float) sin(glfwGetTime()), 2.0f, 5* (float) cos(glfwGetTime()));
        // view = camera.GetViewMatrix();
        // int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


              // view/projection transformations
    
         // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)W_WIDTH / (float)W_HEIGHT, 0.1f, 100.0f);

        glm::mat4 view = camera.GetViewMatrix();


        glm::vec3 diffuseColor = LIGHTCOLOR * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); 
    
       



       

    
        thisShader->use();
        thisShader->setVec3("lightPos", LIGHTPOS);      
        thisShader->setVec3("viewPos", camera.Position);
     

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        thisShader->setMat4("model", model);
        thisShader->setMat4("view", view);

       
        thisShader->setMat4("projection", projection);


        //draw container
        map->Draw(*thisShader);
        ball->drawCharacter(*lightShader);

        //modelmatrix for light source
        lightShader->use();
        glm::mat4 model_light = glm::mat4(1.0f);
        model_light = glm::translate(model_light,  LIGHTPOS);
        model_light = glm::scale(model_light, glm::vec3(0.01f, 0.01f, 0.01f));
        lightShader->setMat4("model_light", model_light);
        lightShader->setMat4("view", view);
        lightShader->setMat4("projection", projection);
        
        lightSource->Draw(*lightShader);
        // lightShader->use();
        // lightsource.Draw(thisShader);

    

 
     
        //mouse movement 
        glfwSetCursorPosCallback(window, mouse_callback);
      


        //check and call events and swap the buffers    
        glfwSwapBuffers(window); //swapping the front and back buffers
        glfwPollEvents();   
 

    // //freeing the resources
    // glDeleteVertexArrays(1, &VAO); 
    // glDeleteBuffers(1, &VBO);
 //clear them all mess and free the resources
}

void Game::run(){
    intialize();
    while(!glfwWindowShouldClose(window)){
        update();
        render();
    }
}

void Game::updateCOllisionDetection(){
 
}