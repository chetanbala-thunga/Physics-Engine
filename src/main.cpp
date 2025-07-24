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



glm::vec3 scaleUniform = glm::vec3(1.0f);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    float delta = (float)yoffset * 0.1f;
    glm::vec3 newScale = scaleUniform + glm::vec3(delta);

    if (newScale.x > 0.05f && newScale.y > 0.05f && newScale.z > 0.05f) {
        scaleUniform = newScale;
}

    cout << "Scale: " << scaleUniform.x << ", " << scaleUniform.y << ", " << scaleUniform.z << endl;
}


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

    glfwSetScrollCallback(window, scroll_callback);



    // Load GLAD and specify viewport
    gladLoadGL();
    glViewport(0, 0, 800, 800);
    

    Circle c1(-0.5f, 0.0f, 0.1f, 0.1f, 0.1f, 10,  1000000000.0f);
    Circle c2(0.5f, 0.0f, -0.1f, -0.1f, 0.1f, 10, 1000000000.0f);
    Circle c3(0.0f, 1.0f, 0.0f, -0.5f, 0.1f, 10,  1000000000.0f);
    objects.push_back(c1);
    objects.push_back(c2);
    objects.push_back(c3);
    

    Shader shaderProgram("../Resources/Shaders/default.vert", "../Resources/Shaders/default.frag");
    shaderProgram.Activate();

    

    float dt = 0.01f;
    while(!glfwWindowShouldClose(window)){

        glUniform4fv(glGetUniformLocation(shaderProgram.ID, "scale"), 1, glm::value_ptr(glm::vec4(scaleUniform, 1.0f)));

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for(Circle& circle: objects){
            circle.applyPhysics(dt, objects);
            //circle.updateVertices();
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