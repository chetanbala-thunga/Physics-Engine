#include <cmath>
#include "Circle.h"


using namespace std;

constexpr float PI = 3.14159265358979323846f;

Circle::Circle(float x, float y, float r, int seg){
    position.push_back(x);
    position.push_back(y);
    radius = r;
    
    vertices.push_back(x);
    vertices.push_back(y);
    for (int j = 0; j < 4; j++) vertices.push_back(0.0f);

    for(int i = 0; i <= seg; i++){
        float angle = (2.0f * PI / seg) * i;
        float xpos = x + r * cos(angle);
        float ypos = y + r * sin(angle);

        vertices.push_back(xpos);
        vertices.push_back(ypos);
        for (int j = 0; j < 4; j++) vertices.push_back(0.0f);
        vertices.push_back(xpos);
        vertices.push_back(ypos);
        for (int j = 0; j < 4; j++) vertices.push_back(0.0f);
    }

    VAO1.Bind();

    VBO VBO1 = VBO(vertices.data(), vertices.size() * sizeof(float));

    VAO1.LinkAtrrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAtrrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.Unbind();

}

/*
void Circle::update(float deltaTime){
    position[0] += velocity.x * deltaTime;
    position[1] += velocity.y * deltaTime;

    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(position[0], position[1], 0.0f));
}
    */

void Circle::draw(){

    //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    VAO1.Bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 6);

}

void Circle::cleanup(){
    VAO1.Delete();
    VBO1.Delete();
}