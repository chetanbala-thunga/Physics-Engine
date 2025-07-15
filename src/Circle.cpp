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

}