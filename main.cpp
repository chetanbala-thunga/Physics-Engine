#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

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

    // Background color
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clear back buffer and swap back buffer with the front buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    //While Loop
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

    // Delete Window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}