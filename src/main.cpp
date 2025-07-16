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


    Circle c1(0.5f, 0.0f, 0.1f, 50);
    Circle c2(-0.5f, 0.0f, 0.1f, 50);
    Circle c3(-0.5f, 0.3f, 0.1f, 50);
    objects.push_back(c1);
    objects.push_back(c2);
    objects.push_back(c3);


    // VAO and VBO
    Shader shaderProgram("../Resources/Shaders/default.vert", "../Resources/Shaders/default.frag");


    GLuint transformLoc = glGetUniformLocation(shaderProgram.ID, "transform");

    //While Loop
    while(!glfwWindowShouldClose(window)){

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();

        float time = glfwGetTime();
        float yOffset = 0.5f - 0.3f * time;
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, yOffset, 0.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        for(Circle& circle: objects) circle.draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for(Circle& circle: objects) circle.cleanup();
    shaderProgram.Delete();

    // Delete Window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}