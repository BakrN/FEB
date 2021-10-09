#pragma once
#include <string> 
#define M_PI 3.14159265358979323846
#include <math.h>
// PROVIDED STRUCTS THAT I NEEDED TO USE
struct Point2{
    double x,y; 
    uint32_t index; 
    Point2() = default; 
    Point2(double _x, double _y, uint32_t i) { x = _x; y = _y; index = i;  }
    bool Dist(const Point2& point, double max_dist) { //returns true if distance is more than max
        if (sqrt((float)((point.x-x)*(point.x -x) + (point.y - y)* (point.y-y)))  > max_dist) {
            return true; 
        }
        return false;   
    }
    void print(){
        printf("x : %s, y : %s, index : %s\n", std::to_string(x).c_str(), std::to_string(y).c_str(), std::to_string(index).c_str());
    }
}; 
struct Pose2{
    double x, y, theta;
    Pose2() = default;
    Pose2(double _x, double _y, double th) { x = _x; y = _y; theta = th; }
    void print(){
        printf("x : %s, y : %s, theta : %s\n", std::to_string(x).c_str(), std::to_string(y).c_str(), std::to_string(theta).c_str());
    }
};

