#ifndef Stroke_h
#define Stroke_h
#include "point.h"
#include <vector>
class Stroke{
    public:
        std::vector<Point> arr;
        void addPoint(const Point& p){
            arr.push_back(p);
        }
};

#endif
