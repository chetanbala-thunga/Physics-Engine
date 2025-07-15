#ifndef Circle_CLASS_H
#define Circle_CLASS_H

#include <vector>

class Circle{
    public:
        std::vector<float> position;
        int radius;

        std::vector<float> vertices;

        Circle(float x, float y, float r, int seg);

};

#endif