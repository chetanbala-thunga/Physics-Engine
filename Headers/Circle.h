#ifndef Circle_CLASS_H
#define Circle_CLASS_H

#include <vector>

class Circle{
    public:
        std::vector<float> position;
        int radius;

        int segments;
        std::vector<float> vertices;

        Circle();
        Circle(float x, float y, float r);

};

#endif