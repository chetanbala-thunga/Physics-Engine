#include <cmath>
#include "Circle.h"


using namespace std;

constexpr float PI = 3.14159265358979323846f;
constexpr float G = 6.67430e-11f;

Circle::Circle(float x, float y, float vx, float vy, float r, int seg, float m){
    position = glm::vec3(x, y, 0.0f);
    velocity = glm::vec3(vx, vy, 0.0f);
    acceleration = glm::vec3(0.0f);

    segments = seg;
    radius = r;
    mass = m;
    
    vertices.push_back(position.x);
    vertices.push_back(position.y);
    vertices.push_back(0.0f);

    for(int i = 0; i <= segments; i++){
        float angle = (2.0f * PI / segments) * i;
        float xpos = position.x + radius * cos(angle);
        float ypos = position.y + radius * sin(angle);

        vertices.push_back(xpos);
        vertices.push_back(ypos);
        vertices.push_back(0.0f);
    }

    VAO1.Bind();
    VBO VBO1 = VBO(vertices.data(), vertices.size() * sizeof(float));
    VAO1.LinkAtrrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    VAO1.Unbind();


}
void Circle::applyPhysics(float dt, vector<Circle>& objects) {
    glm::vec3 g(0.0f);

    for (Circle& obj : objects) {
        if (&obj != this) {
            float r = glm::length(obj.position - position);
            if (r > 0.01f) {
                glm::vec3 direction = glm::normalize(obj.position - position);
                g += G * obj.mass / (r * r) * direction;
            }
        }
    }

    cout << "g: " << g.x << ", " << g.y << ", " << g.z << endl;

    acceleration = g;
    velocity += acceleration * dt;
    position += velocity * dt;

    cout << "Position: " << position.x << ", " << position.y << ", " << position.z << endl;
    cout << "Velocity: " << velocity.x << ", " << velocity.y << ", " << velocity.z << endl;
    cout << "Acceleration: " << acceleration.x << ", " << acceleration.y << ", " << acceleration.z << endl;
    
}


void Circle::applyPhysics2(float dt){
    glm::vec3 g(0.0f, -9.81f, 0.0f);

    acceleration = g;
    velocity += acceleration * dt;
    position += velocity * dt;

}

void Circle::updateVertices(){
    vertices.clear();
    vertices.push_back(position.x);
    vertices.push_back(position.y);
    vertices.push_back(0.0f);

    for(int i = 0; i <= segments; i++){
        float angle = (2.0f * PI / segments) * i;
        float xpos = position.x + radius * cos(angle);
        float ypos = position.y + radius * sin(angle);

        vertices.push_back(xpos);
        vertices.push_back(ypos);
        vertices.push_back(0.0f);
    }

    VAO1.Bind();
    VBO VBO1 = VBO(vertices.data(), vertices.size() * sizeof(float));
    VAO1.LinkAtrrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    VAO1.Unbind();
    

}

void Circle::draw(Shader& shader) {

    VAO1.Bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3);

}

void Circle::cleanup(){
    VAO1.Delete();
    VBO1.Delete();
}