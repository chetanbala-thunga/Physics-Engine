#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Circle.h"

using namespace std;


vector<Circle> objects;
constexpr float PI = 3.14159265358979323846f;
constexpr float G = 6.67430e-11f;


int main(void)
{
    // Initialize GLFW
    glfwInit();
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
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Load GLAD and specify viewport
    gladLoadGL();
    glViewport(0, 0, 800, 800);
    

    Circle c1(-0.5f, 0.0f, 0.0f, 0.5f, 0.1f, 10, 10000000000.0f);
    Circle c2(0.5f, 0.0f, 0.0f, -0.5f, 0.1f, 10, 10000000000.0f);
    //Circle c3(0.0f, 0.5f, 0.0f, -0.5f, 0.1f, 10, 10000000000.0f);
    objects.push_back(c1);
    objects.push_back(c2);
    //objects.push_back(c3);
    

    Shader shaderProgram("../Resources/Shaders/default.vert", "../Resources/Shaders/default.frag");
    shaderProgram.Activate();

    glUniform4f(glGetUniformLocation(shaderProgram.ID, "uColor"), 0.0f, 1.0f, 0.0f, 1.0f);


    float dt = 0.01f;
    while(!glfwWindowShouldClose(window)){

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for(Circle& circle: objects){
            circle.applyPhysics(dt, objects);
            circle.updateVertices();
        }

        for(Circle& circle: objects) circle.draw(shaderProgram);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for(Circle& circle: objects) circle.cleanup();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}