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
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,      0.0f, 0.0f, 0.0f,
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,       0.0f, 0.0f, 0.0f,
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    0.0f, 0.0f, 0.0f
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

    VAO1.LinkAtrrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAtrrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    //While Loop
    while(!glfwWindowShouldClose(window)){

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniID, 0.5f);

        VAO1.Bind();

        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    shaderProgram.Delete();

    // Delete Window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}