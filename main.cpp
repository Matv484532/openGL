#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// ---== Setings ==---
const unsigned int SCR_WIDTH=800;
const unsigned int SCR_HEIGHT=600;


int main() {
    // Init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Checking window creation success

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout<<"Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Checking glad initiation success
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD"<<std::endl;
        return -1;
    }

    // Shader creation
    Shader ourShader("shader.vs", "shader.fs");


    // Triangle Points Vertices
    float vertices[] = {
//      <Positions (x,y,z)>   <Colors>
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // top 
    };

    
    unsigned int VAO,VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    

    /*/ Get the max number of vertex attributes in our hardware
    int nrAttibutes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttibutes);
    std::cout<<"Maximum nr of vertex attributes supported: "<<nrAttibutes<<std::endl;
    */

    std::cout<<"Please enter the offset of the triangle in the form X.Xf \n";
    float choice;
    std::cin>>choice;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        ourShader.setFloat("off", choice);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);

    glfwTerminate();
    return 0;

}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0,0,width,height);
}