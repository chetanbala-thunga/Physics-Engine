#ifndef Circle_CLASS_H
#define Circle_CLASS_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

class Circle{
    public:
        std::vector<float> position;
        int radius;
        std::vector<float> vertices;

        VAO VAO1;
        VBO VBO1;

        float mass;

        Circle(float x, float y, float r, int seg);
        
        void update(float deltaTime);
        void draw();
        void cleanup();

};

#endif