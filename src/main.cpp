#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

using namespace std;

GLfloat vertices[] = 
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f
};

GLuint indices[] = {
    0,3,5,
    3,2,4,
    5,4,1
};



int main(void)
{
    // Initialize GLFW
    glfwInit();

    // GLFW version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Window
    GLFWwindow* window = glfwCreateWindow(800, 800, "Window", NULL, NULL);
    if(window == NULL){
        cout << "Failed to create window" << endl;
        glfwTerminate();
        return -1;
    }

    // Window in current context
    glfwMakeContextCurrent(window);

    // Load GLAD and specify viewport
    gladLoadGL();
    glViewport(0, 0, 800, 800);


    // VAO and VBO
    Shader shaderProgram("../Resources/Shaders/default.vert", "../Resources/Shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    //While Loop
    while(!glfwWindowShouldClose(window)){

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    // Delete Window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}