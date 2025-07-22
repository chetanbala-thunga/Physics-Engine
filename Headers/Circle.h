#ifndef Circle_CLASS_H
#define Circle_CLASS_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "shaderClass.h"

class Circle{
    public:
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 acceleration;

        glm::vec3 g = glm::vec3(0.0f, 0.0f, 0.0f);

        float segments;
        float radius;
        float mass;

        std::vector<float> vertices;

        VAO VAO1;
        VBO VBO1;

        Circle(float x, float y, float vx, float vy, float r, int seg, float m);
        
        void applyPhysics(float time, vector<Circle>& objects);
        void applyPhysics2(float dt);
        void updateVertices();
        void draw(Shader& shader);
        void cleanup();

};

#endif