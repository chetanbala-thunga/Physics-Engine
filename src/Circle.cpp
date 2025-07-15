#include "Circle.h"

using namespace std;

Circle::Circle(){
    position.push_back(0.0f);
    position.push_back(0.0f);
    radius = 0;
}

Circle::Circle(float x, float y, float r){
    position.push_back(x);
    position.push_back(y);
    radius = r;
}