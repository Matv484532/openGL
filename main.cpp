#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Classes/Shader/shader.h>
#include <stb_image.h>
#include <filesystem.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// ---== Setings ==---
const unsigned int SCR_WIDTH=800;
const unsigned int SCR_HEIGHT=800;


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
    Shader ourShader("Shaders/shader.vs", "Shaders/shader.fs");


    // ---=== Setting up vertices data and buffers ===---

    // Triangle Points Vertices
float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f  // top left 
    };

    unsigned int indices[] = {
        2, 1, 3, // first triangle
        1, 3, 0  // second triangle
    };
    
    unsigned int VAO,VBO,EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // Setting the layout location of the Position Values (layout, number of values, values type, isDataNormalized?, stride=Offset between the first value of a dataset and the next first value, offset from the start of the list)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, 8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);




    // ---=== Loading and creating textures ===---
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    // Set texture wrapping options 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // Loading the texture:
    int width, height, nrChannels;
    unsigned char *data=stbi_load(FileSystem::getPath("Assets/Pictures/Grass.png").c_str(), &width, &height, &nrChannels, 0);
    if (data) {
//                    <Currently Bound 2D Texture>  <MipMap level (default=0 -> Auto)> <Color Format>  <width>  <height>  <Useless legacy thing>  <Color Format of image>  <Store RGB as bytes>   <Value for image data>
        glTexImage2D(GL_TEXTURE_2D,                 0,                                 GL_RGB,         width,   height,    0,                      GL_RGB,                 GL_UNSIGNED_BYTE,       data                 );
        glGenerateMipmap(GL_TEXTURE_2D);
        
    } else {
        std::cout<<"Failed to load texture. Reason: "<<stbi_failure_reason() << std::endl;
    }
    // Free image from memory because texture is done
    stbi_image_free(data);

    

    


    
        

    /*/ Get the max number of vertex attributes in our hardware
    int nrAttibutes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttibutes);
    std::cout<<"Maximum nr of vertex attributes supported: "<<nrAttibutes<<std::endl;
    */
    /*
    std::cout<<"Please enter the offset of the triangle in the form X.Xf \n";
    float choice;
    std::cin>>choice;
    */

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        //ourShader.setFloat("off", choice);
        glBindTexture(GL_TEXTURE_2D, texture);

        ourShader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1, &EBO);

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